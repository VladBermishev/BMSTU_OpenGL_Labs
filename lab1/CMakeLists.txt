project(lab1)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw GLLib)