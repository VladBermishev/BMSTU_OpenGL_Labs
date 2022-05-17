project(lab6)
add_executable(${PROJECT_NAME} main.cpp stb_image.h)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLM_LIBRARIES} glfw GLLib)