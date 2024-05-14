
add_executable(${PROJECT_NAME} "main.cpp" "../Modules/Graphics/Source/glad.c")

target_link_libraries(${PROJECT_NAME} PRIVATE Logger Networking Graphics)
