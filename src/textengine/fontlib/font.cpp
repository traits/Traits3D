#include "traits3d/fonts/stdfonts.h"
#include "traits3d/fonts/font.h"

namespace traits3d
{

Font::Repository &Font::repository()
{
    static Repository *repo = nullptr;

    if (repo == nullptr)
    {
        repo = new Repository();
        StandardFonts::append_to_repository();
    }

    return *repo;
}

void Font::appendFont(const Font *val)
{
    if (!val)
        return;

    repository().map_[val->name] = val;
}

} // ns