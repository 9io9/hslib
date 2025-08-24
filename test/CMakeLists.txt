add_executable(hst hst.c)

target_include_directories(hst PRIVATE ../include)
target_link_libraries(hst hslib)

add_test(NAME hst COMMAND hst)