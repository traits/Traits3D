import os

hdir = 'include' + os.sep + 'traits3d' + os.sep + 'fonts'
hprefix = 'traits3d/fonts'

hfile = open(os.path.join(hdir, "stdfonts.h"),'w')

s = '''#pragma once

// generated private class - don't touch

#include "traits3d/fonts/font.h"

namespace Traits3D
{
  class Font::StandardFonts  
  {
  private:
'''

hfile.write(s)

cfile = open('stdfonts.cpp','w')
cfile.write('// generated private class - don\'t touch\n\n#include "' + hprefix + "/" + 'stdfonts.h"\n\nnamespace\n{\n')

basenames = []
caption = []
anonsuffix = '_anon__'
sizesuffix = 'size__'

for root, dirs, files in os.walk('fonts'):
  for fname in files:
    ifile = os.path.join(root, fname)     
    basename = os.path.splitext(os.path.basename(ifile))[0]
    caption.append(basename.replace("-"," "))  
    basename = basename.replace("-","_")
    basenames.append(basename)    
    
    hfile.write('    static const Font ' + basename + ';\n')
    
    cfile.write('  static const unsigned char ' + basename + anonsuffix + '[] = {')
    with open(ifile, mode='rb') as file:
        byte = file.read(1)
        while(byte):
            #cfile.write('0x{0:02x}'.format(ord(byte)))
            cfile.write(str(ord(byte)))
            byte = file.read(1)   
            if byte:
                cfile.write(',')
                
    cfile.write('};\n')
    cfile.write('  const size_t ' + basename + sizesuffix + 
                ' = sizeof(' + basename + anonsuffix + ');\n')

cfile.write('} // private\n\n' )           

s = '''
  public:
    static void append_to_repository()
    {
'''
hfile.write(s)

for i in range(len(basenames)):
    hfile.write('      Font::appendFont(&' + basenames[i] + ');\n')
    cfile.write('const Traits3D::Font Traits3D::Font::StandardFonts::' + basenames[i] + 
    ' = Traits3D::Font((const unsigned char*)' + basenames[i] + anonsuffix + ', ' + 
    basenames[i] + sizesuffix + ', "' + caption[i] + '");\n')        

s = '''    }
  };
} // ns  
'''    
hfile.write(s)
hfile.close()  
cfile.close()    
