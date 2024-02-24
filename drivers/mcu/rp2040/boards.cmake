include(${CMAKE_SOURCE_DIR}/cmake/map.cmake)

# Map board name to required boot2
microjava_map_insert(rp2040_board_boot2 pico w25q080.S)