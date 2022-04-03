#pragma once
#include "Types/Vector2i.h"
#include <string>
namespace GLGraphics{
    class WindowInitParams{
        const std::string _title;
        const Vector2i _size;
    public:
        WindowInitParams() = default;
        WindowInitParams(const std::string& title, const Vector2i& size): _title(title), _size(size){}

        std::string getTitle() const noexcept{return _title;}
        Vector2i getSize() const noexcept{return _size;}
        void GLinit() const noexcept{}
    };
}