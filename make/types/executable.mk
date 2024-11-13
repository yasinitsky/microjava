ifndef OUTPUT
$(error OUTPUT variable is not defined)
endif

SOURCE_FILES_ABSOLUTE = $(call GET_ABSOLUTE_PATH,$(SOURCE_FILES))
INCLUDE_PATH_ABSOLUTE = $(call GET_ABSOLUTE_PATH,$(INCLUDE_PATH))
LINKER_SCRIPT_ABSOLUTE = $(call GET_ABSOLUTE_PATH,$(LINKER_SCRIPT))

SOURCE_FILES_REPO_RELATIVE = $(call GET_REPO_RELATIVE_PATH,$(SOURCE_FILES))
OBJ_FILES = $(foreach file,$(SOURCE_FILES_REPO_RELATIVE),$(OBJ_FOLDER)/$(basename $(file)).o)

OUTPUT := $(EXEC_FOLDER)/$(OUTPUT)

DEPENDENCIES_HEADERS = $(foreach dependency,$(DEPENDENCIES),$(shell $(call MAKE_MODULE,$(dependency),get-headers)))
ALL_INCLUDES_WITH_FLAGS := $(foreach path,$(INCLUDE_PATH_ABSOLUTE),-I$(path))

$(OBJ_FOLDER)/%.o: $(REPO_ROOT)/%.c
	@echo $(call LOG_INFO,CC,$@)
	@mkdir -p $(dir $@)
	@$(CC) $< -o $@ $(CFLAGS) -c $(ALL_INCLUDES_WITH_FLAGS) $(CPU_FLAG)

$(OBJ_FOLDER)/%.o: $(REPO_ROOT)/%.S
	@echo $(call LOG_INFO,ASM,$@)
	@mkdir -p $(dir $@)
	@$(CC) $< -o $@ $(ASMFLAGS) -c $(ALL_INCLUDES_WITH_FLAGS) $(CPU_FLAG)

$(OBJ_FOLDER)/%.o: $(REPO_ROOT)/%.cpp
	@echo $(call LOG_INFO,CXX,$@)
	@mkdir -p $(dir $@)
	@$(CXX) $< -o $@ $(CXXFLAGS) -c $(ALL_INCLUDES_WITH_FLAGS) $(CPU_FLAG)

build: $(DEPENDENCIES) $(OUTPUT)

$(OUTPUT): $(OBJ_FILES)
	@echo $(call LOG_INFO,EXECUTABLE,$(OUTPUT))
	@mkdir -p $(dir $@)
	$(LD) -o $@ $^ -L$(LIB_FOLDER) --whole-archive $(foreach lib,$(STATIC_LIBS),-l:$(lib)) $(if $(LINKER_SCRIPT_ABSOLUTE),-T$(LINKER_SCRIPT_ABSOLUTE),)