#pragma once
#include "traits3d/fonts/font.h"

namespace Traits3D
{
  class StandardFont  
  {
  public:
    static const FontMap fontMap;
  
  private:
    static const Font OpenSans_Italic;
    static const Font OpenSans_Regular;

    static FontMap create_map()
    {
      FontMap m;
      
      m[OpenSans_Italic.name] = &OpenSans_Italic;
      m[OpenSans_Regular.name] = &OpenSans_Regular;

      return m;
    }
  };
} // ns  
