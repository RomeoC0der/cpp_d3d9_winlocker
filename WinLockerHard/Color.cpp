#include "Color.hpp"

D3DCOLOR Color::convert()
{
    return  ((D3DCOLOR)((((static_cast<int>(this->a * 255.0f)) & 0xff) << 24) | (((static_cast<int>(this->r * 255.0f)) & 0xff) << 16) | (((static_cast<int>(this->g * 255.0f)) & 0xff) << 8) | ((static_cast<int>(this->b * 255.0f)) & 0xff)));
}
