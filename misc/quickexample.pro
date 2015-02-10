QT += qml quick widgets
QMAKE_CXXFLAGS += -std=c++1y

DEFINES += PROTEAN3D_GL_IS_OPENGL_ES
#todo!
DEFINES += QT_OPENGL_ES_3 GL_ES_VERSION_3_0
LIBS += -lGLESv3

INCLUDEPATH += \
    ../src/3rdparty \
    ../src/glbase/include \
    ../src/protean3d/include \
    ../src/textengine/include \
    ../src/textengine/fontlib\include \
    ../examples/qt/_common

SOURCES += \
    ../examples/qt/_common/qtwidgetbase.cpp \
    ../examples/qt/quickexample/logorenderer.cpp \
    ../examples/qt/quickexample/fboinsgrenderer.cpp \
    ../examples/qt/quickexample/main.cpp \
    ../src/3rdparty/glm/detail/dummy.cpp \
    ../src/3rdparty/glm/detail/glm.cpp \
    ../src/glbase/glhelper.cpp \
    ../src/glbase/ibo.cpp \
    ../src/glbase/indexmaker.cpp \
    ../src/glbase/shader.cpp \
    ../src/glbase/shader_std.cpp \
    ../src/glbase/vao.cpp \
    ../src/glbase/vbo.cpp \
    ../src/protean3d/autoscaler.cpp \
    ../src/protean3d/axis.cpp \
    ../src/protean3d/axisobject.cpp \
    ../src/protean3d/colortable.cpp \
    ../src/protean3d/coordinates.cpp \
    ../src/protean3d/data.cpp \
    ../src/protean3d/dataobject.cpp \
    ../src/protean3d/extglwidget.cpp \
    ../src/protean3d/globject.cpp \
    ../src/protean3d/helper.cpp \
    ../src/protean3d/plot3d.cpp \
    ../src/protean3d/scale.cpp \
    ../src/protean3d/surfaceplot.cpp \
    ../src/protean3d/transformation.cpp \
    ../src/protean3d/types.cpp \
    ../src/textengine/fontlib/stdfonts.cpp \
    ../src/textengine/textengine.cpp \
    ../src/textengine/textengine_std.cpp \
    ../src/3rdparty/glloadgen/GL_3_3/gl_core_3_3.c


HEADERS  += \
    ../examples/qt/quickexample/fboinsgrenderer.h \
    ../examples/qt/quickexample/logorenderer.h \
    ../examples/qt/_common/global.h \
    ../examples/qt/_common/inputdevice.h \
    ../examples/qt/_common/qtwidget.hh \
    ../examples/qt/_common/qtwidgetbase.h \
    ../src/3rdparty/glloadgen/GL_3_3/gl_core_3_3.h \
    ../src/3rdparty/glm/detail/_features.hpp \
    ../src/3rdparty/glm/detail/_fixes.hpp \
    ../src/3rdparty/glm/detail/_noise.hpp \
    ../src/3rdparty/glm/detail/_swizzle.hpp \
    ../src/3rdparty/glm/detail/_swizzle_func.hpp \
    ../src/3rdparty/glm/detail/_vectorize.hpp \
    ../src/3rdparty/glm/detail/func_common.hpp \
    ../src/3rdparty/glm/detail/func_exponential.hpp \
    ../src/3rdparty/glm/detail/func_geometric.hpp \
    ../src/3rdparty/glm/detail/func_integer.hpp \
    ../src/3rdparty/glm/detail/func_matrix.hpp \
    ../src/3rdparty/glm/detail/func_noise.hpp \
    ../src/3rdparty/glm/detail/func_packing.hpp \
    ../src/3rdparty/glm/detail/func_trigonometric.hpp \
    ../src/3rdparty/glm/detail/func_vector_relational.hpp \
    ../src/3rdparty/glm/detail/intrinsic_common.hpp \
    ../src/3rdparty/glm/detail/intrinsic_exponential.hpp \
    ../src/3rdparty/glm/detail/intrinsic_geometric.hpp \
    ../src/3rdparty/glm/detail/intrinsic_integer.hpp \
    ../src/3rdparty/glm/detail/intrinsic_matrix.hpp \
    ../src/3rdparty/glm/detail/intrinsic_trigonometric.hpp \
    ../src/3rdparty/glm/detail/intrinsic_vector_relational.hpp \
    ../src/3rdparty/glm/detail/precision.hpp \
    ../src/3rdparty/glm/detail/setup.hpp \
    ../src/3rdparty/glm/detail/type_float.hpp \
    ../src/3rdparty/glm/detail/type_gentype.hpp \
    ../src/3rdparty/glm/detail/type_half.hpp \
    ../src/3rdparty/glm/detail/type_int.hpp \
    ../src/3rdparty/glm/detail/type_mat.hpp \
    ../src/3rdparty/glm/detail/type_mat2x2.hpp \
    ../src/3rdparty/glm/detail/type_mat2x3.hpp \
    ../src/3rdparty/glm/detail/type_mat2x4.hpp \
    ../src/3rdparty/glm/detail/type_mat3x2.hpp \
    ../src/3rdparty/glm/detail/type_mat3x3.hpp \
    ../src/3rdparty/glm/detail/type_mat3x4.hpp \
    ../src/3rdparty/glm/detail/type_mat4x2.hpp \
    ../src/3rdparty/glm/detail/type_mat4x3.hpp \
    ../src/3rdparty/glm/detail/type_mat4x4.hpp \
    ../src/3rdparty/glm/detail/type_vec.hpp \
    ../src/3rdparty/glm/detail/type_vec1.hpp \
    ../src/3rdparty/glm/detail/type_vec2.hpp \
    ../src/3rdparty/glm/detail/type_vec3.hpp \
    ../src/3rdparty/glm/detail/type_vec4.hpp \
    ../src/3rdparty/glm/gtc/bitfield.hpp \
    ../src/3rdparty/glm/gtc/constants.hpp \
    ../src/3rdparty/glm/gtc/epsilon.hpp \
    ../src/3rdparty/glm/gtc/integer.hpp \
    ../src/3rdparty/glm/gtc/matrix_access.hpp \
    ../src/3rdparty/glm/gtc/matrix_integer.hpp \
    ../src/3rdparty/glm/gtc/matrix_inverse.hpp \
    ../src/3rdparty/glm/gtc/matrix_transform.hpp \
    ../src/3rdparty/glm/gtc/noise.hpp \
    ../src/3rdparty/glm/gtc/packing.hpp \
    ../src/3rdparty/glm/gtc/quaternion.hpp \
    ../src/3rdparty/glm/gtc/random.hpp \
    ../src/3rdparty/glm/gtc/reciprocal.hpp \
    ../src/3rdparty/glm/gtc/round.hpp \
    ../src/3rdparty/glm/gtc/type_precision.hpp \
    ../src/3rdparty/glm/gtc/type_ptr.hpp \
    ../src/3rdparty/glm/gtc/ulp.hpp \
    ../src/3rdparty/glm/gtc/vec1.hpp \
    ../src/3rdparty/glm/gtx/associated_min_max.hpp \
    ../src/3rdparty/glm/gtx/bit.hpp \
    ../src/3rdparty/glm/gtx/closest_point.hpp \
    ../src/3rdparty/glm/gtx/color_space.hpp \
    ../src/3rdparty/glm/gtx/color_space_YCoCg.hpp \
    ../src/3rdparty/glm/gtx/common.hpp \
    ../src/3rdparty/glm/gtx/compatibility.hpp \
    ../src/3rdparty/glm/gtx/component_wise.hpp \
    ../src/3rdparty/glm/gtx/dual_quaternion.hpp \
    ../src/3rdparty/glm/gtx/euler_angles.hpp \
    ../src/3rdparty/glm/gtx/extend.hpp \
    ../src/3rdparty/glm/gtx/extented_min_max.hpp \
    ../src/3rdparty/glm/gtx/fast_exponential.hpp \
    ../src/3rdparty/glm/gtx/fast_square_root.hpp \
    ../src/3rdparty/glm/gtx/fast_trigonometry.hpp \
    ../src/3rdparty/glm/gtx/gradient_paint.hpp \
    ../src/3rdparty/glm/gtx/handed_coordinate_space.hpp \
    ../src/3rdparty/glm/gtx/integer.hpp \
    ../src/3rdparty/glm/gtx/intersect.hpp \
    ../src/3rdparty/glm/gtx/io.hpp \
    ../src/3rdparty/glm/gtx/log_base.hpp \
    ../src/3rdparty/glm/gtx/matrix_cross_product.hpp \
    ../src/3rdparty/glm/gtx/matrix_decompose.hpp \
    ../src/3rdparty/glm/gtx/matrix_interpolation.hpp \
    ../src/3rdparty/glm/gtx/matrix_major_storage.hpp \
    ../src/3rdparty/glm/gtx/matrix_operation.hpp \
    ../src/3rdparty/glm/gtx/matrix_query.hpp \
    ../src/3rdparty/glm/gtx/matrix_transform_2d.hpp \
    ../src/3rdparty/glm/gtx/mixed_product.hpp \
    ../src/3rdparty/glm/gtx/multiple.hpp \
    ../src/3rdparty/glm/gtx/norm.hpp \
    ../src/3rdparty/glm/gtx/normal.hpp \
    ../src/3rdparty/glm/gtx/normalize_dot.hpp \
    ../src/3rdparty/glm/gtx/number_precision.hpp \
    ../src/3rdparty/glm/gtx/optimum_pow.hpp \
    ../src/3rdparty/glm/gtx/orthonormalize.hpp \
    ../src/3rdparty/glm/gtx/perpendicular.hpp \
    ../src/3rdparty/glm/gtx/polar_coordinates.hpp \
    ../src/3rdparty/glm/gtx/projection.hpp \
    ../src/3rdparty/glm/gtx/quaternion.hpp \
    ../src/3rdparty/glm/gtx/range.hpp \
    ../src/3rdparty/glm/gtx/raw_data.hpp \
    ../src/3rdparty/glm/gtx/rotate_normalized_axis.hpp \
    ../src/3rdparty/glm/gtx/rotate_vector.hpp \
    ../src/3rdparty/glm/gtx/scalar_multiplication.hpp \
    ../src/3rdparty/glm/gtx/scalar_relational.hpp \
    ../src/3rdparty/glm/gtx/simd_mat4.hpp \
    ../src/3rdparty/glm/gtx/simd_quat.hpp \
    ../src/3rdparty/glm/gtx/simd_vec4.hpp \
    ../src/3rdparty/glm/gtx/spline.hpp \
    ../src/3rdparty/glm/gtx/std_based_type.hpp \
    ../src/3rdparty/glm/gtx/string_cast.hpp \
    ../src/3rdparty/glm/gtx/transform.hpp \
    ../src/3rdparty/glm/gtx/transform2.hpp \
    ../src/3rdparty/glm/gtx/type_aligned.hpp \
    ../src/3rdparty/glm/gtx/vector_angle.hpp \
    ../src/3rdparty/glm/gtx/vector_query.hpp \
    ../src/3rdparty/glm/gtx/wrap.hpp \
    ../src/3rdparty/glm/common.hpp \
    ../src/3rdparty/glm/exponential.hpp \
    ../src/3rdparty/glm/ext.hpp \
    ../src/3rdparty/glm/fwd.hpp \
    ../src/3rdparty/glm/geometric.hpp \
    ../src/3rdparty/glm/glm.hpp \
    ../src/3rdparty/glm/integer.hpp \
    ../src/3rdparty/glm/mat2x2.hpp \
    ../src/3rdparty/glm/mat2x3.hpp \
    ../src/3rdparty/glm/mat2x4.hpp \
    ../src/3rdparty/glm/mat3x2.hpp \
    ../src/3rdparty/glm/mat3x3.hpp \
    ../src/3rdparty/glm/mat3x4.hpp \
    ../src/3rdparty/glm/mat4x2.hpp \
    ../src/3rdparty/glm/mat4x3.hpp \
    ../src/3rdparty/glm/mat4x4.hpp \
    ../src/3rdparty/glm/matrix.hpp \
    ../src/3rdparty/glm/packing.hpp \
    ../src/3rdparty/glm/trigonometric.hpp \
    ../src/3rdparty/glm/vec2.hpp \
    ../src/3rdparty/glm/vec3.hpp \
    ../src/3rdparty/glm/vec4.hpp \
    ../src/3rdparty/glm/vector_relational.hpp \
    ../src/glbase/include/protean3d/glbase/glhelper.h \
    ../src/glbase/include/protean3d/glbase/ibo.h \
    ../src/glbase/include/protean3d/glbase/indexmaker.h \
    ../src/glbase/include/protean3d/glbase/shader.h \
    ../src/glbase/include/protean3d/glbase/shader_std.h \
    ../src/glbase/include/protean3d/glbase/vao.h \
    ../src/glbase/include/protean3d/glbase/vbo.h \
    ../src/protean3d/include/protean3d/autoscaler.h \
    ../src/protean3d/include/protean3d/axis.h \
    ../src/protean3d/include/protean3d/axisobject.h \
    ../src/protean3d/include/protean3d/colortable.h \
    ../src/protean3d/include/protean3d/coordinates.h \
    ../src/protean3d/include/protean3d/data.h \
    ../src/protean3d/include/protean3d/dataobject.h \
    ../src/protean3d/include/protean3d/extglwidget.h \
    ../src/protean3d/include/protean3d/global.h \
    ../src/protean3d/include/protean3d/globject.h \
    ../src/protean3d/include/protean3d/helper.h \
    ../src/protean3d/include/protean3d/plot3d.h \
    ../src/protean3d/include/protean3d/scale.h \
    ../src/protean3d/include/protean3d/surfaceplot.h \
    ../src/protean3d/include/protean3d/transformation.h \
    ../src/protean3d/include/protean3d/types.h \
    ../src/textengine/fontlib/include/protean3d/fonts/stdfonts.h \
    ../src/textengine/include/protean3d/textengine/stb_truetype.h \
    ../src/textengine/include/protean3d/textengine/textengine.h \
    ../src/textengine/include/protean3d/textengine/textengine_std.h

SOURCES -= ../src/3rdparty/glloadgen/GL_3_3/gl_core_3_3.c \
           ../src/3rdparty/glm/detail/dummy.cpp
           
HEADERS -= ../src/3rdparty/glloadgen/GL_3_3/gl_core_3_3.h
            
RESOURCES += ../examples/qt/quickexample/textureinsgnode.qrc

OTHER_FILES += \
    ../examples/qt/quickexample/main.qml
 
CONFIG += mobility
MOBILITY = 

