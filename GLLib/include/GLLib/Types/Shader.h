#pragma once
namespace GLGraphics{
    class Shader {
    public:
        unsigned int ID;
        Shader() {}
        void Init(const char *vertexShaderCode, const char *fragmentShaderCode, const char *geometryShaderCode = nullptr){
            unsigned int vertex, fragment;
            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vertexShaderCode, NULL);
            glCompileShader(vertex);
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
            glCompileShader(fragment);
            unsigned int geometry;
            if (geometryShaderCode != nullptr) {
                geometry = glCreateShader(GL_GEOMETRY_SHADER);
                glShaderSource(geometry, 1, &geometryShaderCode, NULL);
                glCompileShader(geometry);
            }
            ID = glCreateProgram();
            glAttachShader(ID, vertex);
            glAttachShader(ID, fragment);
            if (geometryShaderCode != nullptr)
                glAttachShader(ID, geometry);
            glLinkProgram(ID);
            glDeleteShader(vertex);
            glDeleteShader(fragment);
            if (geometryShaderCode != nullptr)
                glDeleteShader(geometry);
        }
        inline void use() const { glUseProgram(ID); }
    };
}