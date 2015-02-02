import os

hdir = 'include' + os.sep + 'protean3d' + os.sep + 'fonts'
hprefix = 'protean3d/fonts'

hfile = open(os.path.join(hdir, "stdfonts.h"),'w')
hfile.write('#pragma once\n\nnamespace Protean3D\n{\nstruct StandardFont\n{\n')
cfile = open('stdfonts.cpp','w')
cfile.write('#include "' + hprefix + "/" + 'stdfonts.h"\n\n')

for root, dirs, files in os.walk('fonts'):
  for fname in files:
    ifile = os.path.join(root, fname)     
    basename = os.path.splitext(os.path.basename(ifile))[0]    
    basename = basename.replace("-","_")
        
    hfile.write('  static const unsigned char ' + basename + '[];\n')
    hfile.write('  static const size_t ' + basename + '_size;\n')
    
    cfile.write('const unsigned char Protean3D::StandardFont::' + basename + '[] = {')
    with open(ifile, mode='rb') as file:
        byte = file.read(1)
        while(byte):
            cfile.write('0x{0:02x}'.format(ord(byte)))
            byte = file.read(1)   
            if byte:
                cfile.write(',')
                
    cfile.write('};\n')
    cfile.write('const size_t Protean3D::StandardFont::' + basename + '_size = sizeof(' + basename + ');\n')
           
hfile.write('};\n} // ns\n')
hfile.close()

cfile.close()    
