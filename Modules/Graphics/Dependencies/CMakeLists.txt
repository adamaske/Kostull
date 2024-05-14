add_library(GraphicsDeps INTERFACE)

add_subdirectory(GLM)
add_subdirectory(GLFW)
add_subdirectory(GLAD)
add_subdirectory(ImGUI)
add_subdirectory(GLEW)

target_link_libraries(GraphicsDeps INTERFACE
    GLM
    GLFW
    GLAD
    GLEW
    ImGUI
)