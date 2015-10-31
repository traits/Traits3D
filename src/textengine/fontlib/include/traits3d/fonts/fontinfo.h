#pragma once

#include <string>

namespace traits3d
{
class FontInfo
{
public:
    explicit FontInfo(std::string const &f_name = std::string(), size_t f_height = 0)
        : font_name(f_name), font_height(f_height)
    {}

    std::string font_name;
    size_t font_height;
};

inline bool operator==(FontInfo const &a, FontInfo const &b)
{
    return a.font_height == b.font_height && a.font_name == b.font_name;
}

inline bool operator!=(FontInfo const &a, FontInfo const &b)
{
    return !operator==(a, b);
}
} // ns
