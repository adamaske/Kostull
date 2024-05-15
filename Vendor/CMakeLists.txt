add_library(Vendor INTERFACE)

add_subdirectory(JSON)
add_subdirectory(Eigen)

target_link_libraries(Vendor INTERFACE 
JSON
Eigen
)