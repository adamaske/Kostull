file(GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp")
file(GLOB INCS "${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h")

add_library(Networking STATIC ${SRCS})

target_include_directories(Networking PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Include")

target_link_libraries(Networking PRIVATE Logger)