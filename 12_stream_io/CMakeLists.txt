add_executable(mode_string mode_string.c)
add_executable(stream_type stream_type.c)
FILE(COPY ap_data.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
FILE(COPY ro_data.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
