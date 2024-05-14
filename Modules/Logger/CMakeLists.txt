add_library(Logger STATIC "Source/Logger.cpp")

target_include_directories(Logger PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Include")

#===SPDLOG===
find_package(spdlog)
if(spdlog_FOUND)
    target_compile_definitions(Logger PUBLIC "USE_SPDLOG")
    target_link_libraries(Logger PUBLIC spdlog::spdlog $<$<BOOL:${MINGW}>:ws2_32>)
endif()
