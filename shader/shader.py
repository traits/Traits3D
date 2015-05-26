import os
from string import Template

# config section

namespace = ['Traits3D', 'GL', 'ShaderCode']


#the key is used as variable (e.g. $proj_matrix) in input shader templates
#and will be transformed to value in ouput files (C++ or shader) 

shader_variables = { 
  'proj_matrix'   : 'proj_matrix',
  'mv_matrix'     : 'mv_matrix',
  'v_in_color'    : 'v_in_color', 
  'v_coordinates' : 'v_coordinates',
  'v_normals'     : 'v_normals',  
  'v_out_color'   : 'v_out_color',  
  }

#def decorate(variables):
#  surround = lambda word : '$' + word 
#  return dict(zip(map(surround, variables.keys()), variables.values()))

#shader_variables = decorate(shader_variables)

version_gl = {
  'es'      : '#version 300 es',
  'desktop' : '#version 330',
  }

cpp_version_selector = \
'''
#ifdef GL_ES_VERSION_3_0
  "#version 300 es\\n"
#else
  "#version 330\\n"
#endif
'''

vertex_class = 'Vertex'
fragment_class = 'Fragment'


hout = 'output' + os.sep + 'include'
cppout = 'output' + os.sep + 'include'
h_rel_path = 'traits3d/shaders'

hfile = open(os.path.join(hout, "shader_std.h"),'w')
cppfile = open(os.path.join(cppout, "shader_std.cpp"),'w')

warning = '// generated file - don\'t touch\n\n'

h_preamble = \
  '#pragma once\n\n' \
  + warning \
  +'#include <string>\n\n'

# end config

insert = ''
def intend() :
  global insert
  insert += 2 * ' '

def unintend() :
  global insert
  insert = insert.replace(' ', '', 2)

hfile.write(h_preamble)

for n in namespace:
  hfile.write(insert + 'namespace ' + n + '\n' + insert + '{\n')
  intend()

hfile.write(insert + 'class ' + vertex_class + '\n' + insert + '{\n')
hfile.write(insert + 'public:\n')
intend()
hfile.write(insert + '// shader variables\n')
for v in shader_variables:
  hfile.write(insert + 'static const std::string ' + v + ';\n')
hfile.write('\n')
#unintend()

cppfile.write(warning + '#include "' + h_rel_path + "/" + 'shader_std.h"\n\n')

basenames = []
caption = []

for root, dirs, files in os.walk('input'):
  for fname in files:
    ifile = os.path.join(root, fname)     
    basename = os.path.splitext(os.path.basename(ifile))[0]
    
    hfile.write(insert + 'static const std::string ' + basename + ';\n')
    
    cppfile.write('\n\n// ' + fname + '\n\n') 
    cppfile.write('const char* ' + '::'.join(namespace) + '::' + basename + ' = \n{')
    cppfile.write(cpp_version_selector)
    with open(ifile, mode='rb') as file:      
      for line in file:
        #eols = line.count('\n')
        line = line.rstrip('\r\n')
        line = Template(line).substitute(shader_variables)
        if line and not line.isspace():
          if line.startswith('//'):
            cppfile.write(line + '\n')
          else:
            cppfile.write('"' + line + '\\n"' + '\n')


#s = '''    }
#  };
#} // ns  
#'''    
#hfile.write(s)

insert = insert.replace(' ', '', 2)
for n in namespace:
  hfile.write(insert + '} \\\\ ' + n + '\n')
  unintend()

hfile.close()  
cppfile.close()    
