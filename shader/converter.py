import os
from string import Template

# config section

namespace = ['Traits3D', 'GL', 'ShaderCode']


# The key is used as a variable (e.g. $proj_matrix) in input shader templates
# and will be transformed to value in ouput files (C++ or shader). 
# The key should remain consistent with the input shader content

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

variables_struct = 'Var'
vertex_class = 'Vertex'
fragment_class = 'Fragment'
function_class = 'Function'


vertex_input_dir = 'input' + os.sep + 'vshader'
fragment_input_dir = 'input' + os.sep + 'fshader'
function_input_dir = 'input' + os.sep + 'functions'
hout = '..' + os.sep + 'src' + os.sep + 'glbase' + os.sep + 'include'  + os.sep + 'traits3d' + os.sep + 'glbase'
cppout = '..' + os.sep + 'src' + os.sep + 'glbase'
h_rel_path = 'traits3d/glbase'

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

hfile.write(insert + '// shader variables\n')
hfile.write(insert + 'struct ' + variables_struct + '\n' + insert + '{\n')
intend()
for v in sorted(shader_variables.itervalues()):
  hfile.write(insert + 'static const std::string ' + v + ';\n')
unintend()
hfile.write(insert + '};\n\n')

cppfile.write(warning + '#include "' + h_rel_path + "/" + 'shader_std.h"\n\n')
for v in sorted(shader_variables.itervalues()):
  cppfile.write('const std::string ' + '::'.join(namespace) + '::' + variables_struct + '::' + v + ' = "' + v + '";\n')

basenames = []
caption = []


def processFiles(dir, type):
  ret = {}
  for root, dirs, files in os.walk(dir):
    for fname in sorted(files):
      ifile = os.path.join(root, fname)     
      basename = os.path.splitext(os.path.basename(ifile))[0]
    
      with open(ifile, mode='rb') as file:     
        text = [] 
        for line in file:
          #eols = line.count('\n')
          line = line.rstrip('\r\n')
          line = Template(line).substitute(shader_variables)
          text.append(line)
      ret[basename] = [fname, type, text]   
  return ret

def writeOutput(comment, artifact_class, artifact_input_dir):
  a_info = processFiles(artifact_input_dir, artifact_class)
  hfile.write(insert + comment + '\n')
  hfile.write(insert + 'class ' + artifact_class + '\n' + insert + '{\n')
  hfile.write(insert + 'public:\n')
  intend()
  cppfile.write('\n\n' + comment + '\n')
  for k, v in sorted(a_info.iteritems()):
    hfile.write(insert + 'static const char* ' + k + ';\n')
    cppfile.write('\n\n// ' + v[0] + '\n') 
    cppfile.write('const char* ' + '::'.join(namespace) + '::' + artifact_class + '::' + k + ' = \n{')
    cppfile.write(cpp_version_selector)
    for line in v[2]:
      if line and not line.isspace():
        #if line.startswith('//'):
        #  cppfile.write(line + '\n')
        #else:
        cppfile.write('  "' + line + '\\n"' + '\n')
    cppfile.write('};\n\n')
  unintend()
  hfile.write(insert + '};\n\n')
  return

writeOutput(r'// Vertex shader', vertex_class, vertex_input_dir)
writeOutput(r'// Fragment shader', fragment_class, fragment_input_dir)
#writeOutput(r'// Functions', function_class, function_input_dir)


#s = '''    }
#  };
#} // ns  
#'''    
#hfile.write(s)

insert = insert.replace(' ', '', 2)
for n in reversed(namespace):
  hfile.write(insert + '} // ' + n + '\n')
  unintend()

hfile.close()  
cppfile.close()    
