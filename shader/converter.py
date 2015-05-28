import os
from string import Template

class Converter(object):
  """Converts template shader files into C++ sources"""

  def __init__(self):
    self.__vertex_input_dir = 'input' + os.sep + 'vshader'
    self.__fragment_input_dir = 'input' + os.sep + 'fshader'
    self.__function_input_dir = 'input' + os.sep + 'functions'
    self.__hout = '..' + os.sep + 'src' + os.sep + 'glbase' + os.sep + 'include'  + os.sep + 'traits3d' + os.sep + 'glbase'
    self.__cppout = '..' + os.sep + 'src' + os.sep + 'glbase'
    self.__shout = 'generated_glsl'
    self.__insert = ''

  def __openFiles(self):
    self.__hfile = open(os.path.join(self.__hout, 'shader_std.h'),'w')
    self.__cppfile = open(os.path.join(self.__cppout, 'shader_std.cpp'),'w')
  
  def __closeFiles(self):
    self.__hfile.close()
    self.__cppfile .close()


  # static config section

  __touch_warning = '// generated file - don\'t touch\n\n'
  __namespace = ['Traits3D', 'GL', 'ShaderCode']


  # The key is used as a variable (e.g. $proj_matrix) in input shader templates
  # and will be transformed to value in ouput files (C++ or shader). 
  # The key should remain consistent with the input shader content

  __shader_variables = { 
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

  #__shader_variables = decorate(__shader_variables)

  __cpp_version_selector = \
'''
#ifdef GL_ES_VERSION_3_0
  "#version 300 es\\n"
#else
  "#version 330\\n"
#endif
'''

  __variables_struct = 'Var'
  __vertex_class = 'Vertex'
  __fragment_class = 'Fragment'
  __function_class = 'Function'

  __h_rel_path = 'traits3d/glbase'
  __h_preamble = \
    '#pragma once\n\n' \
    + __touch_warning \
    +'#include <string>\n\n'

  # end config

  def _intend(self) :
    self.__insert += 2 * ' '

  def _unintend(self) :
    self.__insert = self.__insert.replace(' ', '', 2)

  @staticmethod
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
            line = Template(line).substitute(Converter.__shader_variables)
            text.append(line)
        ret[basename] = [fname, type, text]   
    return ret

  def writeOutput(self, comment, artifact_class, artifact_input_dir, output_shader, glsl_variant):
    a_info = Converter.processFiles(artifact_input_dir, artifact_class)
    self.__hfile.write(self.__insert + comment + '\n')
    self.__hfile.write(self.__insert + 'class ' + artifact_class + '\n' + self.__insert + '{\n')
    self.__hfile.write(self.__insert + 'public:\n')
    self._intend()
    self.__cppfile.write('\n\n' + comment + '\n')
    for k, v in sorted(a_info.iteritems()):
      self.__hfile.write(self.__insert + 'static const char* ' + k + ';\n')
      self.__cppfile.write('\n\n// ' + v[0] + '\n') 
      self.__cppfile.write('const char* ' + '::'.join(Converter.__namespace) + '::' + artifact_class + '::' + k + ' = \n{')
      self.__cppfile.write(Converter.__cpp_version_selector)
      for line in v[2]:
        if line and not line.isspace():
          #if line.startswith('//'):
          #  self.__cppfile.write(line + '\n')
          #else:
          self.__cppfile.write('  "' + line + '\\n"' + '\n')
      self.__cppfile.write('};\n\n')
    self._unintend()
    self.__hfile.write(self.__insert + '};\n\n')

    if output_shader:
      for k, v in sorted(a_info.iteritems()):
        suffix = '.glsl'
        if artifact_class == Converter.__vertex_class:
          suffix = '.vert'
        elif artifact_class == Converter.__fragment_class:
          suffix = '.frag'
        elif artifact_class == Converter.__function_class:
          suffix = '.func'
        try:
          os.mkdir(self.__shout)
        except OSError:
          pass 
        self.__shfile = open(os.path.join(self.__shout, k + suffix),'w')
        if glsl_variant=='desktop':
          self.__shfile.write('#version 330\n\n')
        else:
          self.__shfile.write('#version 300 es\n\n')
        for line in v[2]:
          self.__shfile.write(line + '\n')
        self.__shfile.close()

    return

  def run(self, output_shader=False, glsl_variant='desktop'):
    self.__openFiles()
    self.__hfile.write(Converter.__h_preamble)

    for n in Converter.__namespace:
      self.__hfile.write(self.__insert + 'namespace ' + n + '\n' + self.__insert + '{\n')
      self._intend()

    self.__hfile.write(self.__insert + '// shader variables\n')
    self.__hfile.write(self.__insert + 'struct ' + Converter.__variables_struct + '\n' + self.__insert + '{\n')
    self._intend()
    for v in sorted(Converter.__shader_variables.itervalues()):
      self.__hfile.write(self.__insert + 'static const std::string ' + v + ';\n')
    self._unintend()
    self.__hfile.write(self.__insert + '};\n\n')

    self.__cppfile.write(Converter.__touch_warning + '#include "' + Converter.__h_rel_path + "/" + 'shader_std.h"\n\n')
    for v in sorted(Converter.__shader_variables.itervalues()):
      self.__cppfile.write('const std::string ' + '::'.join(Converter.__namespace) + '::' + Converter.__variables_struct + '::' + v + ' = "' + v + '";\n')

    self.writeOutput(r'// Vertex shader', Converter.__vertex_class, self.__vertex_input_dir, output_shader, glsl_variant)
    self.writeOutput(r'// Fragment shader', Converter.__fragment_class, self.__fragment_input_dir, output_shader, glsl_variant)
    #self.writeOutput(r'// Functions', Converter.__function_class, self.__function_input_dir, output_shader, glsl_variant)

    self.__insert = self.__insert.replace(' ', '', 2)
    for n in reversed(Converter.__namespace):
      self.__hfile.write(self.__insert + '} // ' + n + '\n')
      self._unintend()

    self.__closeFiles()
    return
