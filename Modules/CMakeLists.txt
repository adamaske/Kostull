add_library(Modules INTERFACE)

add_subdirectory(Logger)
add_subdirectory(Networking)
add_subdirectory(Graphics)

target_link_libraries(Modules INTERFACE 
Graphics
Logger
Networking
)

