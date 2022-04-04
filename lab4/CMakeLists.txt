project(lab4)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLM_LIBRARIES} glfw Freetype::Freetype GLLib glad ${CMAKE_DL_LIBS})