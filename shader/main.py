from converter import Converter

conv = Converter()
conv.run(output_shader=False, glsl_variant='desktop') # for output_shader==True set glsl_variant to 'desktop' (default) or 'es'
