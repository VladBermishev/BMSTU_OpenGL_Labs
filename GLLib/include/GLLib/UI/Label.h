#pragma once
#include <string>
#include "GL/gl.h"
#include "GLLib/Types/Vector2.h"
#include "GLLib/Types/Vector3.h"
#include "GLLib/Primitives/Object.h"
#include "GLLib/Utils/TextRenderer.h"
namespace GLGraphics{
    class Label: public Object{
        std::string _text;
        Vector2f _pos;
        GLfloat _scale;
        Vector3f _color;
    public:
        Label() = default;
        explicit Label(const std::string& text, const Vector2f& pos, const GLfloat scale, const Vector3f& color){
            _text = text;
            _pos = pos;
            _scale = scale;
            _color = color;
        }
        inline const std::string& text() const noexcept{return _text;}
        inline std::string& text() noexcept{return _text;}
        inline const Vector2f& pos() const noexcept{return _pos;}
        inline Vector2f& pos() noexcept{return _pos;}
        inline const GLfloat& scale() const noexcept{return _scale;}
        inline GLfloat& scale() noexcept{return _scale;}
        inline const Vector3f& color() const noexcept{return _color;}
        inline Vector3f& color() noexcept{return _color;}
        void SetVertex() final{
            __textRenderer.RenderText(_text, _pos.x(), _pos.y(), _scale, _color);
        }
    };
}