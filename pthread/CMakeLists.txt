add_executable(base base.c)
target_link_libraries(base PRIVATE Threads::Threads)