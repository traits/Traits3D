from converter import Converter

conv = Converter()
conv.run(output_shader=True, glsl_variant='desktop') # for output_shader==True set glsl_variant to 'desktop' (default) or 'es'
