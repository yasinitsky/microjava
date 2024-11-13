HEADERS_ABSOLUTE = $(call GET_ABSOLUTE_PATH,$(HEADERS))

DEPENDENCIES_HEADERS = $(foreach dependency,$(DEPENDENCIES),$(shell $(call MAKE_MODULE,$(dependency),get-headers)))
ALL_INCLUDES_WITH_FLAGS := $(foreach path,$(DEPENDENCIES_HEADERS),-I$(path)) $(foreach path,$(HEADERS_ABSOLUTE),-I$(path))

get-headers:
	@echo $(DEPENDENCIES_HEADERS) $(HEADERS_ABSOLUTE)

build: $(DEPENDENCIES)