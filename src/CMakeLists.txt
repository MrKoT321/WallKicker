add_executable(src main.cpp)

target_include_directories(src PRIVATE ${SFML_INCLUDE_DIR})
target_compile_definitions(src PRIVATE SFML_STATIC)

target_link_libraries(src ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})