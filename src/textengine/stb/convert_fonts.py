import os

hdir = 'include' + os.sep + 'protean3d' + os.sep + 'fonts'
hprefix = 'protean3d/fonts'

hfile = open(os.path.join(hdir, "stdfonts.h"),'w')
hfile.write('#pragma once\n\n')
hfile.write('#include <string>\n#include <vector>\n\n')
hfile.write('namespace Protean3D\n{\n')
hfile.write('  struct Font\n  {\n')
hfile.write('    Font(const unsigned char* buffer = 0, size_t buflen = 0, std::string fname = std::string())\n')
hfile.write('    :data(buffer, buffer + buflen), name(fname)\n    {}\n')
hfile.write('    const std::vector<unsigned char> data;\n')
hfile.write('    const std::string name;\n  };\n\n')
hfile.write('  struct StandardFont\n  {\n')

cfile = open('stdfonts.cpp','w')
cfile.write('#include "' + hprefix + "/" + 'stdfonts.h"\n\nnamespace\n{\n')

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
            cfile.write('0x{0:02x}'.format(ord(byte)))
            byte = file.read(1)   
            if byte:
                cfile.write(',')
                
    cfile.write('};\n')
    cfile.write('  const size_t ' + basename + sizesuffix + 
                ' = sizeof(' + basename + anonsuffix + ');\n')

cfile.write('} // private\n\n' )           
hfile.write('  };\n} // ns\n')
hfile.close()

for i in range(len(basenames)):
    cfile.write('const Protean3D::Font Protean3D::StandardFont::' + basenames[i] + 
    ' = Protean3D::Font((const unsigned char*)' + basenames[i] + anonsuffix + ', ' + 
    basenames[i] + sizesuffix + ', "' + caption[i] + '");\n')    
    
cfile.close()    
