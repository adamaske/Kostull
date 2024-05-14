file(GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.c")
file(GLOB INCS "${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h")

add_library(Graphics STATIC ${SRCS})

add_subdirectory("Dependencies")

target_include_directories(Graphics PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(Graphics PRIVATE Logger)
target_link_libraries(Graphics PUBLIC GraphicsDeps)

