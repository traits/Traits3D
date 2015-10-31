#pragma once

// generated private class - don't touch

#include "traits3d/fonts/font.h"

namespace traits3d
{
  class Font::StandardFonts  
  {
  private:
    static const Font OpenSans_Italic;
    static const Font OpenSans_Regular;

  public:
    static void append_to_repository()
    {
      Font::appendFont(&OpenSans_Italic);
      Font::appendFont(&OpenSans_Regular);
    }
  };
} // ns  
