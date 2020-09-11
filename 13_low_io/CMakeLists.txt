add_executable(scatter-gather scatter-gather.c)
add_executable(mysterious_copy_file mysterious_copy_file.c)

FILE(COPY inc.bin DESTINATION ${CMAKE_CURRENT_BINARY_DIR})