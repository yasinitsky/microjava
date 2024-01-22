# Functions to work with associative arrays

function(microjava_map_insert map_name key value)
    set(MICROJAVA_${map_name}_map_${key} ${value} CACHE INTERNAL "")
endfunction()

function(microjava_map_find map_name destination key)
    set(${destination} ${MICROJAVA_${map_name}_map_${key}} CACHE INTERNAL "")
endfunction()