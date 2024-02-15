include(${CMAKE_SOURCE_DIR}/cmake/map.cmake)

function(board_mcu_map_insert board mcu)
    microjava_map_insert(board_mcu ${board} ${mcu})
endfunction()

function(board_mcu_map_find destination board)
    microjava_map_find(board_mcu ${destination} ${board})
endfunction()

board_mcu_map_insert(pico rp2040)

# special pseudo-board for unit testing
board_mcu_map_insert(mock mock)