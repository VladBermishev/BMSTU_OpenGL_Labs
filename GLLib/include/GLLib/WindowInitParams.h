#pragma once
#include "GLLib/Types/Vector2.h"
#include <string>
namespace GLGraphics{
    class WindowInitParams{
        const std::string _title;
        const Vector2ui _size;
    public:
        WindowInitParams() = default;
        WindowInitParams(const std::string& title, const Vector2ui& size): _title(title), _size(size){}

        std::string getTitle() const noexcept{return _title;}
        Vector2ui getSize() const noexcept{return _size;}
        void GLinit() const noexcept{}
    };
}