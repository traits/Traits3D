import os
from string import Template

class Converter(object):
  """Converts template shader files into C++ sources"""

  def __init__(self):
    self.__input_dir = 'input'
    self.__hout = '..' + os.sep + 'src' + os.sep + 'glbase' + os.sep + 'include'  + os.sep + 'glb'
    self.__cppout = '..' + os.sep + 'src' + os.sep + 'glbase'
    self.__shout = 'generated_glsl'
    self.__insert = ''

  def __openFiles(self):
    self.__hfile = open(os.path.join(self.__hout, 'shader_std.h'),'w')
    self.__cppfile = open(os.path.join(self.__cppout, 'shader_std.cpp'),'w')
  
  def __closeFiles(self):
    self.__hfile.close()
    self.__cppfile .close()

  def __skipComments(self, file):
    for line in file:
      if not line.strip().startswith('//'):
        yield line

  # static config section

  __touch_warning = '// generated file - don\'t touch\n\n'
  __namespace = ['glb', 'shadercode']


  # The key is used as a variable (e.g. $proj_matrix) in input shader templates
  # and will be transformed to value in output files (C++ or shader). 
  # The key must match shader template variable names exactly, changing value names
  # is allowed and will create respective C++ sources

  __shader_variables = { 
    'proj_matrix'   : 'proj_matrix',
    'mv_matrix'     : 'mv_matrix',
    'normal_matrix' : 'normal_matrix',
    'v_in_color'    : 'v_in_color', 
    'v_coordinates' : 'v_coordinates',
    'v_normals'     : 'v_normals',  
    'v_out_color'   : 'v_out_color',  
    'f_out_color'   : 'f_out_color',  
    'light_position': 'light_position', # might be a direction for some cases 
    'light_position2': 'light_position2', 
    }

  # filename suffix indicates shader type 
  __shader_type = { 
    'Vertex'     : {'tsuffix' :'.vert_t', 'osuffix' :'.vert'},
    'Fragment'   : {'tsuffix' :'.frag_t', 'osuffix' :'.frag'},
    'Subroutine' : {'tsuffix' :'.geom_t', 'osuffix' :'.geom'},
  }
  __variables_struct = 'Var'


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

  __h_rel_path = 'glb'
  __h_preamble = \
    '#pragma once\n\n' \
    + __touch_warning \
    +'#include <string>\n\n'

  # end config

  def _intend(self) :
    self.__insert += 2 * ' '

  def _unintend(self) :
    self.__insert = self.__insert.replace(' ', '', 2)

  #@staticmethod
  def processFiles(self, dir):
    ret = {}
    for k in self.__shader_type:
      ret[k] = []

    for root, dirs, files in os.walk(dir):
      for fname in sorted(files):
        ifile = os.path.join(root, fname)     
        basename = os.path.splitext(os.path.basename(ifile))[0]
        suffix = os.path.splitext(os.path.basename(ifile))[1] # suffix including '.'
    
        with open(ifile, mode='rb') as file:     
          text = [] 
          for line in self.__skipComments(file):
            #eols = line.count('\n')
            line = line.rstrip('\r\n')
            line = Template(line).substitute(Converter.__shader_variables)
            text.append(line)
        
        # look up suffix key
        lsuffix = [k for k,v in self.__shader_type.iteritems() if v['tsuffix'] == suffix]
        if lsuffix:
          ret[lsuffix[0]].append([fname, basename, text])   
    return ret

  def writeOutput(self, artifact_input_dir, output_shader, glsl_variant):
    a_info = self.processFiles(artifact_input_dir)
    for k, v in sorted(a_info.iteritems()):
      self.__hfile.write(self.__insert + '// ' + k + ' shader \n')
      self.__hfile.write(self.__insert + 'class ' + k + '\n' + self.__insert + '{\n')
      self.__hfile.write(self.__insert + 'public:\n')
      self._intend()
      self.__cppfile.write('\n\n' + '// ' + k + ' shader\n')
      for lv in v:
        self.__hfile.write(self.__insert + 'static const char* ' + lv[1] + ';\n')
        self.__cppfile.write('\n\n// ' + lv[0] + '\n') 
        self.__cppfile.write('const char* ' + k + '::' + lv[1] + ' = \n{')
        self.__cppfile.write(Converter.__cpp_version_selector)
        for line in lv[2]:
          if line and not line.isspace():
            #if line.startswith('//'):
            #  self.__cppfile.write(line + '\n')
            #else:
            self.__cppfile.write('  "' + line + '\\n"' + '\n')
              
        if output_shader:        
          suffix = self.__shader_type[k]['osuffix']
          try:
            os.mkdir(self.__shout)
          except OSError:
            pass 
          self.__shfile = open(os.path.join(self.__shout, lv[1] + suffix),'w')
          if glsl_variant=='desktop':
            self.__shfile.write('#version 330\n\n')
          else:
            self.__shfile.write('#version 300 es\n\n')
          for line in lv[2]:
            self.__shfile.write(line + '\n')
          self.__shfile.close()

        self.__cppfile.write('};\n\n')
      self._unintend()
      self.__hfile.write(self.__insert + '};\n\n')
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
    for n in Converter.__namespace:
      self.__cppfile.write('namespace ' + n + '\n' + '{\n')
    self.__cppfile.write('\n')
    for v in sorted(Converter.__shader_variables.itervalues()):
      self.__cppfile.write('const std::string ' + Converter.__variables_struct + '::' + v + ' = "' + v + '";\n')

    self.writeOutput(self.__input_dir, output_shader, glsl_variant)

    self.__insert = self.__insert.replace(' ', '', 2)
    for n in reversed(Converter.__namespace):
      self.__hfile.write(self.__insert + '} // ' + n + '\n')
      self._unintend()
    for n in reversed(Converter.__namespace):
      self.__cppfile.write('} // ' + n + '\n')

    self.__closeFiles()
    return
