add_executable(mode_string mode_string.c)
add_executable(stream_type stream_type.c)
FILE(COPY ap_data.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
FILE(COPY ro_data.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
FILE(COPY rw_keep.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(fseek fseek.c)
add_executable(FILE_dissection FILE_dissection.c)
add_executable(wide_oriented wide_oriented.c)

add_executable(stream_lock stream_lock.c)
target_link_libraries(stream_lock PRIVATE Threads::Threads)

add_executable(nolock_stream nolock_stream.c)
add_executable(print_wide print_wide.c)
add_executable(asprintf asprintf.c)
add_executable(vprint vprint.c)
add_executable(positioning positioning.c)