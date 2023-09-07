
project(foobar)
cmake_minimum_required(VERSION 3.27)

add_library(cudadevrt STATIC src/empty.c)
add_library(cudart_static STATIC src/empty.c)
add_library(rt STATIC src/empty.c)


target_link_directories(rt PUBLIC /tmp/chipstar-install/lib/)
target_link_libraries(rt PUBLIC CHIP)
target_include_directories(rt PUBLIC /tmp/chipstar-install/include)

install(TARGETS rt)
install(TARGETS cudadevrt)
install(TARGETS cudart_static)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/root/bin DESTINATION . PATTERN "*" PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/root/include DESTINATION .)
