#pragma once

#include <map>
#include <string>
#include <glad/glad.h>
#include <GLLib/Types/Mat.h>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace GLGraphics {
    class TextRenderer {
        static constexpr char vshader[] = "#version 330 core\n"
                                          "layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>\n"
                                          "out vec2 TexCoords;\n"
                                          "\n"
                                          "uniform mat4 projection;\n"
                                          "\n"
                                          "void main()\n"
                                          "{\n"
                                          "    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);\n"
                                          "    TexCoords = vertex.zw;\n"
                                          "}";
        static constexpr char fshader[] = "#version 330 core\n"
                                          "in vec2 TexCoords;\n"
                                          "out vec4 color;\n"
                                          "\n"
                                          "uniform sampler2D text;\n"
                                          "uniform vec3 textColor;\n"
                                          "\n"
                                          "void main()\n"
                                          "{    \n"
                                          "    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);\n"
                                          "    color = vec4(textColor, 1.0) * sampled;\n"
                                          "}";
        struct Character {
            std::uint32_t TextureID;
            GLGraphics::Vector2i Size, Bearing;
            std::uint32_t Advance;
        };
        std::map<GLchar, Character> Characters;
        Shader shader;
        unsigned int VAO, VBO;
    public:
        TextRenderer() {}

        void Init(const Vector2ui &window_size) {
            shader.Init(vshader, fshader);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            GLGraphics::Mat4 _projection = GLGraphics::Ortho(0.0f, static_cast<float>(window_size.x()),
                                                             0.0f,static_cast<float>(window_size.y()));
            shader.use();
            glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, _projection.data());
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            Init_Characters();
        }

        void Init_Characters(const std::string &font = "/usr/share/fonts/truetype/hack/Hack-Regular.ttf") {
            FT_Library ft;
            if (FT_Init_FreeType(&ft)) {
                //LOG SMTH
                return;
            }
            FT_Face face;
            if (FT_New_Face(ft, font.c_str(), 0, &face)) {
                //LOG SMTH
                return;
            } else {
                FT_Set_Pixel_Sizes(face, 0, 48);
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                for (unsigned char c = 0; c < 128; c++) {
                    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                        //LOG SMTH
                        continue;
                    }
                    unsigned int texture;
                    glGenTextures(1, &texture);
                    glBindTexture(GL_TEXTURE_2D, texture);
                    glTexImage2D(
                            GL_TEXTURE_2D,
                            0,
                            GL_RED,
                            face->glyph->bitmap.width,
                            face->glyph->bitmap.rows,
                            0,
                            GL_RED,
                            GL_UNSIGNED_BYTE,
                            face->glyph->bitmap.buffer
                    );
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    Character character = {
                            texture,
                            GLGraphics::Vector2i(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                            GLGraphics::Vector2i(face->glyph->bitmap_left, face->glyph->bitmap_top),
                            static_cast<unsigned int>(face->glyph->advance.x)
                    };
                    Characters.insert(std::pair<char, Character>(c, character));
                }
                glBindTexture(GL_TEXTURE_2D, 0);
            }
            FT_Done_Face(face);
            FT_Done_FreeType(ft);
        }

        void RenderText(const std::string &text, float x, const float y, const float scale,
                        const GLGraphics::Vector3f &color) {
            glEnable(GL_BLEND);
            shader.use();
            glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x(), color.y(), color.z());
            glActiveTexture(GL_TEXTURE0);
            glBindVertexArray(VAO);
            std::string::const_iterator c;
            for (c = text.begin(); c != text.end(); c++) {
                Character ch = Characters[*c];
                float xpos = x + ch.Bearing.x() * scale;
                float ypos = y - (ch.Size.y() - ch.Bearing.y()) * scale;
                float w = ch.Size.x() * scale;
                float h = ch.Size.y() * scale;
                float vertices[6][4] = {
                        {xpos,     ypos + h, 0.0f, 0.0f},
                        {xpos,     ypos,     0.0f, 1.0f},
                        {xpos + w, ypos,     1.0f, 1.0f},

                        {xpos,     ypos + h, 0.0f, 0.0f},
                        {xpos + w, ypos,     1.0f, 1.0f},
                        {xpos + w, ypos + h, 1.0f, 0.0f}
                };
                glBindTexture(GL_TEXTURE_2D, ch.TextureID);
                glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glDrawArrays(GL_TRIANGLES, 0, 6);
                x += (ch.Advance >> 6) * scale;
            }
            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_BLEND);
        }
    };

    TextRenderer __textRenderer;
}