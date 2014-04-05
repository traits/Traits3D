#ifndef OPENGL_NOLOAD_STYLE_H
#define OPENGL_NOLOAD_STYLE_H

#if defined(__glew_h__) || defined(__GLEW_H__)
#error Attempt to include auto-generated header after including glew.h
#endif
#if defined(__gl_h_) || defined(__GL_H__)
#error Attempt to include auto-generated header after including gl.h
#endif
#if defined(__glext_h_) || defined(__GLEXT_H_)
#error Attempt to include auto-generated header after including glext.h
#endif
#if defined(__gltypes_h_)
#error Attempt to include auto-generated header after gltypes.h
#endif
#if defined(__gl_ATI_h_)
#error Attempt to include auto-generated header after including glATI.h
#endif

#define __glew_h__
#define __GLEW_H__
#define __gl_h_
#define __GL_H__
#define __glext_h_
#define __GLEXT_H_
#define __gltypes_h_
#define __gl_ATI_h_

#ifndef APIENTRY
	#if defined(__MINGW32__)
		#ifndef WIN32_LEAN_AND_MEAN
			#define WIN32_LEAN_AND_MEAN 1
		#endif
		#ifndef NOMINMAX
			#define NOMINMAX
		#endif
		#include <windows.h>
	#elif (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__)
		#ifndef WIN32_LEAN_AND_MEAN
			#define WIN32_LEAN_AND_MEAN 1
		#endif
		#ifndef NOMINMAX
			#define NOMINMAX
		#endif
		#include <windows.h>
	#else
		#define APIENTRY
	#endif
#endif /*APIENTRY*/

#ifndef CODEGEN_FUNCPTR
	#define CODEGEN_REMOVE_FUNCPTR
	#if defined(_WIN32)
		#define CODEGEN_FUNCPTR APIENTRY
	#else
		#define CODEGEN_FUNCPTR
	#endif
#endif /*CODEGEN_FUNCPTR*/

#ifndef GLAPI
	#define GLAPI extern
#endif


#ifndef GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS
#define GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS


#endif /*GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS*/

#include <stddef.h>
#ifndef GLEXT_64_TYPES_DEFINED
/* This code block is duplicated in glxext.h, so must be protected */
#define GLEXT_64_TYPES_DEFINED
/* Define int32_t, int64_t, and uint64_t types for UST/MSC */
/* (as used in the GL_EXT_timer_query extension). */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#elif defined(__sun__) || defined(__digital__)
#include <inttypes.h>
#if defined(__STDC__)
#if defined(__arch64__) || defined(_LP64)
typedef long int int64_t;
typedef unsigned long int uint64_t;
#else
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#endif /* __arch64__ */
#endif /* __STDC__ */
#elif defined( __VMS ) || defined(__sgi)
#include <inttypes.h>
#elif defined(__SCO__) || defined(__USLC__)
#include <stdint.h>
#elif defined(__UNIXOS2__) || defined(__SOL64__)
typedef long int int32_t;
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#elif defined(_WIN32) && defined(__GNUC__)
#include <stdint.h>
#elif defined(_WIN32)
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
/* Fallback if nothing above works */
#include <inttypes.h>
#endif
#endif
	typedef unsigned int GLenum;
	typedef unsigned char GLboolean;
	typedef unsigned int GLbitfield;
	typedef void GLvoid;
	typedef signed char GLbyte;
	typedef short GLshort;
	typedef int GLint;
	typedef unsigned char GLubyte;
	typedef unsigned short GLushort;
	typedef unsigned int GLuint;
	typedef int GLsizei;
	typedef float GLfloat;
	typedef float GLclampf;
	typedef double GLdouble;
	typedef double GLclampd;
	typedef char GLchar;
	typedef char GLcharARB;
	#ifdef __APPLE__
typedef void *GLhandleARB;
#else
typedef unsigned int GLhandleARB;
#endif
		typedef unsigned short GLhalfARB;
		typedef unsigned short GLhalf;
		typedef GLint GLfixed;
		typedef ptrdiff_t GLintptr;
		typedef ptrdiff_t GLsizeiptr;
		typedef int64_t GLint64;
		typedef uint64_t GLuint64;
		typedef ptrdiff_t GLintptrARB;
		typedef ptrdiff_t GLsizeiptrARB;
		typedef int64_t GLint64EXT;
		typedef uint64_t GLuint64EXT;
		typedef struct __GLsync *GLsync;
		struct _cl_context;
		struct _cl_event;
		typedef void (APIENTRY *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
		typedef void (APIENTRY *GLDEBUGPROCARB)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
		typedef void (APIENTRY *GLDEBUGPROCAMD)(GLuint id,GLenum category,GLenum severity,GLsizei length,const GLchar *message,void *userParam);
		typedef unsigned short GLhalfNV;
		typedef GLintptr GLvdpauSurfaceNV;
		
		#ifdef __cplusplus
		extern "C" {
		#endif /*__cplusplus*/
		
		/////////////////////////
		// Extension Variables
		
		
		// Version: 1.1
		#define GL_2D                            0x0600
		#define GL_2_BYTES                       0x1407
		#define GL_3D                            0x0601
		#define GL_3D_COLOR                      0x0602
		#define GL_3D_COLOR_TEXTURE              0x0603
		#define GL_3_BYTES                       0x1408
		#define GL_4D_COLOR_TEXTURE              0x0604
		#define GL_4_BYTES                       0x1409
		#define GL_ACCUM                         0x0100
		#define GL_ACCUM_ALPHA_BITS              0x0D5B
		#define GL_ACCUM_BLUE_BITS               0x0D5A
		#define GL_ACCUM_BUFFER_BIT              0x00000200
		#define GL_ACCUM_CLEAR_VALUE             0x0B80
		#define GL_ACCUM_GREEN_BITS              0x0D59
		#define GL_ACCUM_RED_BITS                0x0D58
		#define GL_ADD                           0x0104
		#define GL_ALL_ATTRIB_BITS               0xFFFFFFFF
		#define GL_ALPHA                         0x1906
		#define GL_ALPHA12                       0x803D
		#define GL_ALPHA16                       0x803E
		#define GL_ALPHA4                        0x803B
		#define GL_ALPHA8                        0x803C
		#define GL_ALPHA_BIAS                    0x0D1D
		#define GL_ALPHA_BITS                    0x0D55
		#define GL_ALPHA_SCALE                   0x0D1C
		#define GL_ALPHA_TEST                    0x0BC0
		#define GL_ALPHA_TEST_FUNC               0x0BC1
		#define GL_ALPHA_TEST_REF                0x0BC2
		#define GL_ALWAYS                        0x0207
		#define GL_AMBIENT                       0x1200
		#define GL_AMBIENT_AND_DIFFUSE           0x1602
		#define GL_AND                           0x1501
		#define GL_AND_INVERTED                  0x1504
		#define GL_AND_REVERSE                   0x1502
		#define GL_ATTRIB_STACK_DEPTH            0x0BB0
		#define GL_AUTO_NORMAL                   0x0D80
		#define GL_AUX0                          0x0409
		#define GL_AUX1                          0x040A
		#define GL_AUX2                          0x040B
		#define GL_AUX3                          0x040C
		#define GL_AUX_BUFFERS                   0x0C00
		#define GL_BACK                          0x0405
		#define GL_BACK_LEFT                     0x0402
		#define GL_BACK_RIGHT                    0x0403
		#define GL_BITMAP                        0x1A00
		#define GL_BITMAP_TOKEN                  0x0704
		#define GL_BLEND                         0x0BE2
		#define GL_BLEND_DST                     0x0BE0
		#define GL_BLEND_SRC                     0x0BE1
		#define GL_BLUE                          0x1905
		#define GL_BLUE_BIAS                     0x0D1B
		#define GL_BLUE_BITS                     0x0D54
		#define GL_BLUE_SCALE                    0x0D1A
		#define GL_BYTE                          0x1400
		#define GL_C3F_V3F                       0x2A24
		#define GL_C4F_N3F_V3F                   0x2A26
		#define GL_C4UB_V2F                      0x2A22
		#define GL_C4UB_V3F                      0x2A23
		#define GL_CCW                           0x0901
		#define GL_CLAMP                         0x2900
		#define GL_CLEAR                         0x1500
		#define GL_CLIENT_ALL_ATTRIB_BITS        0xFFFFFFFF
		#define GL_CLIENT_ATTRIB_STACK_DEPTH     0x0BB1
		#define GL_CLIENT_PIXEL_STORE_BIT        0x00000001
		#define GL_CLIENT_VERTEX_ARRAY_BIT       0x00000002
		#define GL_CLIP_PLANE0                   0x3000
		#define GL_CLIP_PLANE1                   0x3001
		#define GL_CLIP_PLANE2                   0x3002
		#define GL_CLIP_PLANE3                   0x3003
		#define GL_CLIP_PLANE4                   0x3004
		#define GL_CLIP_PLANE5                   0x3005
		#define GL_COEFF                         0x0A00
		#define GL_COLOR                         0x1800
		#define GL_COLOR_ARRAY                   0x8076
		#define GL_COLOR_ARRAY_POINTER           0x8090
		#define GL_COLOR_ARRAY_SIZE              0x8081
		#define GL_COLOR_ARRAY_STRIDE            0x8083
		#define GL_COLOR_ARRAY_TYPE              0x8082
		#define GL_COLOR_BUFFER_BIT              0x00004000
		#define GL_COLOR_CLEAR_VALUE             0x0C22
		#define GL_COLOR_INDEX                   0x1900
		#define GL_COLOR_INDEXES                 0x1603
		#define GL_COLOR_LOGIC_OP                0x0BF2
		#define GL_COLOR_MATERIAL                0x0B57
		#define GL_COLOR_MATERIAL_FACE           0x0B55
		#define GL_COLOR_MATERIAL_PARAMETER      0x0B56
		#define GL_COLOR_WRITEMASK               0x0C23
		#define GL_COMPILE                       0x1300
		#define GL_COMPILE_AND_EXECUTE           0x1301
		#define GL_CONSTANT_ATTENUATION          0x1207
		#define GL_COPY                          0x1503
		#define GL_COPY_INVERTED                 0x150C
		#define GL_COPY_PIXEL_TOKEN              0x0706
		#define GL_CULL_FACE                     0x0B44
		#define GL_CULL_FACE_MODE                0x0B45
		#define GL_CURRENT_BIT                   0x00000001
		#define GL_CURRENT_COLOR                 0x0B00
		#define GL_CURRENT_INDEX                 0x0B01
		#define GL_CURRENT_NORMAL                0x0B02
		#define GL_CURRENT_RASTER_COLOR          0x0B04
		#define GL_CURRENT_RASTER_DISTANCE       0x0B09
		#define GL_CURRENT_RASTER_INDEX          0x0B05
		#define GL_CURRENT_RASTER_POSITION       0x0B07
		#define GL_CURRENT_RASTER_POSITION_VALID 0x0B08
		#define GL_CURRENT_RASTER_TEXTURE_COORDS 0x0B06
		#define GL_CURRENT_TEXTURE_COORDS        0x0B03
		#define GL_CW                            0x0900
		#define GL_DECAL                         0x2101
		#define GL_DECR                          0x1E03
		#define GL_DEPTH                         0x1801
		#define GL_DEPTH_BIAS                    0x0D1F
		#define GL_DEPTH_BITS                    0x0D56
		#define GL_DEPTH_BUFFER_BIT              0x00000100
		#define GL_DEPTH_CLEAR_VALUE             0x0B73
		#define GL_DEPTH_COMPONENT               0x1902
		#define GL_DEPTH_FUNC                    0x0B74
		#define GL_DEPTH_RANGE                   0x0B70
		#define GL_DEPTH_SCALE                   0x0D1E
		#define GL_DEPTH_TEST                    0x0B71
		#define GL_DEPTH_WRITEMASK               0x0B72
		#define GL_DIFFUSE                       0x1201
		#define GL_DITHER                        0x0BD0
		#define GL_DOMAIN                        0x0A02
		#define GL_DONT_CARE                     0x1100
		#define GL_DOUBLE                        0x140A
		#define GL_DOUBLEBUFFER                  0x0C32
		#define GL_DRAW_BUFFER                   0x0C01
		#define GL_DRAW_PIXEL_TOKEN              0x0705
		#define GL_DST_ALPHA                     0x0304
		#define GL_DST_COLOR                     0x0306
		#define GL_EDGE_FLAG                     0x0B43
		#define GL_EDGE_FLAG_ARRAY               0x8079
		#define GL_EDGE_FLAG_ARRAY_POINTER       0x8093
		#define GL_EDGE_FLAG_ARRAY_STRIDE        0x808C
		#define GL_EMISSION                      0x1600
		#define GL_ENABLE_BIT                    0x00002000
		#define GL_EQUAL                         0x0202
		#define GL_EQUIV                         0x1509
		#define GL_EVAL_BIT                      0x00010000
		#define GL_EXP                           0x0800
		#define GL_EXP2                          0x0801
		#define GL_EXTENSIONS                    0x1F03
		#define GL_EYE_LINEAR                    0x2400
		#define GL_EYE_PLANE                     0x2502
		#define GL_FALSE                         0
		#define GL_FASTEST                       0x1101
		#define GL_FEEDBACK                      0x1C01
		#define GL_FEEDBACK_BUFFER_POINTER       0x0DF0
		#define GL_FEEDBACK_BUFFER_SIZE          0x0DF1
		#define GL_FEEDBACK_BUFFER_TYPE          0x0DF2
		#define GL_FILL                          0x1B02
		#define GL_FLAT                          0x1D00
		#define GL_FLOAT                         0x1406
		#define GL_FOG                           0x0B60
		#define GL_FOG_BIT                       0x00000080
		#define GL_FOG_COLOR                     0x0B66
		#define GL_FOG_DENSITY                   0x0B62
		#define GL_FOG_END                       0x0B64
		#define GL_FOG_HINT                      0x0C54
		#define GL_FOG_INDEX                     0x0B61
		#define GL_FOG_MODE                      0x0B65
		#define GL_FOG_START                     0x0B63
		#define GL_FRONT                         0x0404
		#define GL_FRONT_AND_BACK                0x0408
		#define GL_FRONT_FACE                    0x0B46
		#define GL_FRONT_LEFT                    0x0400
		#define GL_FRONT_RIGHT                   0x0401
		#define GL_GEQUAL                        0x0206
		#define GL_GREATER                       0x0204
		#define GL_GREEN                         0x1904
		#define GL_GREEN_BIAS                    0x0D19
		#define GL_GREEN_BITS                    0x0D53
		#define GL_GREEN_SCALE                   0x0D18
		#define GL_HINT_BIT                      0x00008000
		#define GL_INCR                          0x1E02
		#define GL_INDEX_ARRAY                   0x8077
		#define GL_INDEX_ARRAY_POINTER           0x8091
		#define GL_INDEX_ARRAY_STRIDE            0x8086
		#define GL_INDEX_ARRAY_TYPE              0x8085
		#define GL_INDEX_BITS                    0x0D51
		#define GL_INDEX_CLEAR_VALUE             0x0C20
		#define GL_INDEX_LOGIC_OP                0x0BF1
		#define GL_INDEX_MODE                    0x0C30
		#define GL_INDEX_OFFSET                  0x0D13
		#define GL_INDEX_SHIFT                   0x0D12
		#define GL_INDEX_WRITEMASK               0x0C21
		#define GL_INT                           0x1404
		#define GL_INTENSITY                     0x8049
		#define GL_INTENSITY12                   0x804C
		#define GL_INTENSITY16                   0x804D
		#define GL_INTENSITY4                    0x804A
		#define GL_INTENSITY8                    0x804B
		#define GL_INVALID_ENUM                  0x0500
		#define GL_INVALID_OPERATION             0x0502
		#define GL_INVALID_VALUE                 0x0501
		#define GL_INVERT                        0x150A
		#define GL_KEEP                          0x1E00
		#define GL_LEFT                          0x0406
		#define GL_LEQUAL                        0x0203
		#define GL_LESS                          0x0201
		#define GL_LIGHT0                        0x4000
		#define GL_LIGHT1                        0x4001
		#define GL_LIGHT2                        0x4002
		#define GL_LIGHT3                        0x4003
		#define GL_LIGHT4                        0x4004
		#define GL_LIGHT5                        0x4005
		#define GL_LIGHT6                        0x4006
		#define GL_LIGHT7                        0x4007
		#define GL_LIGHTING                      0x0B50
		#define GL_LIGHTING_BIT                  0x00000040
		#define GL_LIGHT_MODEL_AMBIENT           0x0B53
		#define GL_LIGHT_MODEL_LOCAL_VIEWER      0x0B51
		#define GL_LIGHT_MODEL_TWO_SIDE          0x0B52
		#define GL_LINE                          0x1B01
		#define GL_LINEAR                        0x2601
		#define GL_LINEAR_ATTENUATION            0x1208
		#define GL_LINEAR_MIPMAP_LINEAR          0x2703
		#define GL_LINEAR_MIPMAP_NEAREST         0x2701
		#define GL_LINES                         0x0001
		#define GL_LINE_BIT                      0x00000004
		#define GL_LINE_LOOP                     0x0002
		#define GL_LINE_RESET_TOKEN              0x0707
		#define GL_LINE_SMOOTH                   0x0B20
		#define GL_LINE_SMOOTH_HINT              0x0C52
		#define GL_LINE_STIPPLE                  0x0B24
		#define GL_LINE_STIPPLE_PATTERN          0x0B25
		#define GL_LINE_STIPPLE_REPEAT           0x0B26
		#define GL_LINE_STRIP                    0x0003
		#define GL_LINE_TOKEN                    0x0702
		#define GL_LINE_WIDTH                    0x0B21
		#define GL_LINE_WIDTH_GRANULARITY        0x0B23
		#define GL_LINE_WIDTH_RANGE              0x0B22
		#define GL_LIST_BASE                     0x0B32
		#define GL_LIST_BIT                      0x00020000
		#define GL_LIST_INDEX                    0x0B33
		#define GL_LIST_MODE                     0x0B30
		#define GL_LOAD                          0x0101
		#define GL_LOGIC_OP                      0x0BF1
		#define GL_LOGIC_OP_MODE                 0x0BF0
		#define GL_LUMINANCE                     0x1909
		#define GL_LUMINANCE12                   0x8041
		#define GL_LUMINANCE12_ALPHA12           0x8047
		#define GL_LUMINANCE12_ALPHA4            0x8046
		#define GL_LUMINANCE16                   0x8042
		#define GL_LUMINANCE16_ALPHA16           0x8048
		#define GL_LUMINANCE4                    0x803F
		#define GL_LUMINANCE4_ALPHA4             0x8043
		#define GL_LUMINANCE6_ALPHA2             0x8044
		#define GL_LUMINANCE8                    0x8040
		#define GL_LUMINANCE8_ALPHA8             0x8045
		#define GL_LUMINANCE_ALPHA               0x190A
		#define GL_MAP1_COLOR_4                  0x0D90
		#define GL_MAP1_GRID_DOMAIN              0x0DD0
		#define GL_MAP1_GRID_SEGMENTS            0x0DD1
		#define GL_MAP1_INDEX                    0x0D91
		#define GL_MAP1_NORMAL                   0x0D92
		#define GL_MAP1_TEXTURE_COORD_1          0x0D93
		#define GL_MAP1_TEXTURE_COORD_2          0x0D94
		#define GL_MAP1_TEXTURE_COORD_3          0x0D95
		#define GL_MAP1_TEXTURE_COORD_4          0x0D96
		#define GL_MAP1_VERTEX_3                 0x0D97
		#define GL_MAP1_VERTEX_4                 0x0D98
		#define GL_MAP2_COLOR_4                  0x0DB0
		#define GL_MAP2_GRID_DOMAIN              0x0DD2
		#define GL_MAP2_GRID_SEGMENTS            0x0DD3
		#define GL_MAP2_INDEX                    0x0DB1
		#define GL_MAP2_NORMAL                   0x0DB2
		#define GL_MAP2_TEXTURE_COORD_1          0x0DB3
		#define GL_MAP2_TEXTURE_COORD_2          0x0DB4
		#define GL_MAP2_TEXTURE_COORD_3          0x0DB5
		#define GL_MAP2_TEXTURE_COORD_4          0x0DB6
		#define GL_MAP2_VERTEX_3                 0x0DB7
		#define GL_MAP2_VERTEX_4                 0x0DB8
		#define GL_MAP_COLOR                     0x0D10
		#define GL_MAP_STENCIL                   0x0D11
		#define GL_MATRIX_MODE                   0x0BA0
		#define GL_MAX_ATTRIB_STACK_DEPTH        0x0D35
		#define GL_MAX_CLIENT_ATTRIB_STACK_DEPTH 0x0D3B
		#define GL_MAX_CLIP_PLANES               0x0D32
		#define GL_MAX_EVAL_ORDER                0x0D30
		#define GL_MAX_LIGHTS                    0x0D31
		#define GL_MAX_LIST_NESTING              0x0B31
		#define GL_MAX_MODELVIEW_STACK_DEPTH     0x0D36
		#define GL_MAX_NAME_STACK_DEPTH          0x0D37
		#define GL_MAX_PIXEL_MAP_TABLE           0x0D34
		#define GL_MAX_PROJECTION_STACK_DEPTH    0x0D38
		#define GL_MAX_TEXTURE_SIZE              0x0D33
		#define GL_MAX_TEXTURE_STACK_DEPTH       0x0D39
		#define GL_MAX_VIEWPORT_DIMS             0x0D3A
		#define GL_MODELVIEW                     0x1700
		#define GL_MODELVIEW_MATRIX              0x0BA6
		#define GL_MODELVIEW_STACK_DEPTH         0x0BA3
		#define GL_MODULATE                      0x2100
		#define GL_MULT                          0x0103
		#define GL_N3F_V3F                       0x2A25
		#define GL_NAME_STACK_DEPTH              0x0D70
		#define GL_NAND                          0x150E
		#define GL_NEAREST                       0x2600
		#define GL_NEAREST_MIPMAP_LINEAR         0x2702
		#define GL_NEAREST_MIPMAP_NEAREST        0x2700
		#define GL_NEVER                         0x0200
		#define GL_NICEST                        0x1102
		#define GL_NONE                          0
		#define GL_NOOP                          0x1505
		#define GL_NOR                           0x1508
		#define GL_NORMALIZE                     0x0BA1
		#define GL_NORMAL_ARRAY                  0x8075
		#define GL_NORMAL_ARRAY_POINTER          0x808F
		#define GL_NORMAL_ARRAY_STRIDE           0x807F
		#define GL_NORMAL_ARRAY_TYPE             0x807E
		#define GL_NOTEQUAL                      0x0205
		#define GL_NO_ERROR                      0
		#define GL_OBJECT_LINEAR                 0x2401
		#define GL_OBJECT_PLANE                  0x2501
		#define GL_ONE                           1
		#define GL_ONE_MINUS_DST_ALPHA           0x0305
		#define GL_ONE_MINUS_DST_COLOR           0x0307
		#define GL_ONE_MINUS_SRC_ALPHA           0x0303
		#define GL_ONE_MINUS_SRC_COLOR           0x0301
		#define GL_OR                            0x1507
		#define GL_ORDER                         0x0A01
		#define GL_OR_INVERTED                   0x150D
		#define GL_OR_REVERSE                    0x150B
		#define GL_OUT_OF_MEMORY                 0x0505
		#define GL_PACK_ALIGNMENT                0x0D05
		#define GL_PACK_LSB_FIRST                0x0D01
		#define GL_PACK_ROW_LENGTH               0x0D02
		#define GL_PACK_SKIP_PIXELS              0x0D04
		#define GL_PACK_SKIP_ROWS                0x0D03
		#define GL_PACK_SWAP_BYTES               0x0D00
		#define GL_PASS_THROUGH_TOKEN            0x0700
		#define GL_PERSPECTIVE_CORRECTION_HINT   0x0C50
		#define GL_PIXEL_MAP_A_TO_A              0x0C79
		#define GL_PIXEL_MAP_A_TO_A_SIZE         0x0CB9
		#define GL_PIXEL_MAP_B_TO_B              0x0C78
		#define GL_PIXEL_MAP_B_TO_B_SIZE         0x0CB8
		#define GL_PIXEL_MAP_G_TO_G              0x0C77
		#define GL_PIXEL_MAP_G_TO_G_SIZE         0x0CB7
		#define GL_PIXEL_MAP_I_TO_A              0x0C75
		#define GL_PIXEL_MAP_I_TO_A_SIZE         0x0CB5
		#define GL_PIXEL_MAP_I_TO_B              0x0C74
		#define GL_PIXEL_MAP_I_TO_B_SIZE         0x0CB4
		#define GL_PIXEL_MAP_I_TO_G              0x0C73
		#define GL_PIXEL_MAP_I_TO_G_SIZE         0x0CB3
		#define GL_PIXEL_MAP_I_TO_I              0x0C70
		#define GL_PIXEL_MAP_I_TO_I_SIZE         0x0CB0
		#define GL_PIXEL_MAP_I_TO_R              0x0C72
		#define GL_PIXEL_MAP_I_TO_R_SIZE         0x0CB2
		#define GL_PIXEL_MAP_R_TO_R              0x0C76
		#define GL_PIXEL_MAP_R_TO_R_SIZE         0x0CB6
		#define GL_PIXEL_MAP_S_TO_S              0x0C71
		#define GL_PIXEL_MAP_S_TO_S_SIZE         0x0CB1
		#define GL_PIXEL_MODE_BIT                0x00000020
		#define GL_POINT                         0x1B00
		#define GL_POINTS                        0x0000
		#define GL_POINT_BIT                     0x00000002
		#define GL_POINT_SIZE                    0x0B11
		#define GL_POINT_SIZE_GRANULARITY        0x0B13
		#define GL_POINT_SIZE_RANGE              0x0B12
		#define GL_POINT_SMOOTH                  0x0B10
		#define GL_POINT_SMOOTH_HINT             0x0C51
		#define GL_POINT_TOKEN                   0x0701
		#define GL_POLYGON                       0x0009
		#define GL_POLYGON_BIT                   0x00000008
		#define GL_POLYGON_MODE                  0x0B40
		#define GL_POLYGON_OFFSET_FACTOR         0x8038
		#define GL_POLYGON_OFFSET_FILL           0x8037
		#define GL_POLYGON_OFFSET_LINE           0x2A02
		#define GL_POLYGON_OFFSET_POINT          0x2A01
		#define GL_POLYGON_OFFSET_UNITS          0x2A00
		#define GL_POLYGON_SMOOTH                0x0B41
		#define GL_POLYGON_SMOOTH_HINT           0x0C53
		#define GL_POLYGON_STIPPLE               0x0B42
		#define GL_POLYGON_STIPPLE_BIT           0x00000010
		#define GL_POLYGON_TOKEN                 0x0703
		#define GL_POSITION                      0x1203
		#define GL_PROJECTION                    0x1701
		#define GL_PROJECTION_MATRIX             0x0BA7
		#define GL_PROJECTION_STACK_DEPTH        0x0BA4
		#define GL_PROXY_TEXTURE_1D              0x8063
		#define GL_PROXY_TEXTURE_2D              0x8064
		#define GL_Q                             0x2003
		#define GL_QUADRATIC_ATTENUATION         0x1209
		#define GL_QUADS                         0x0007
		#define GL_QUAD_STRIP                    0x0008
		#define GL_R                             0x2002
		#define GL_R3_G3_B2                      0x2A10
		#define GL_READ_BUFFER                   0x0C02
		#define GL_RED                           0x1903
		#define GL_RED_BIAS                      0x0D15
		#define GL_RED_BITS                      0x0D52
		#define GL_RED_SCALE                     0x0D14
		#define GL_RENDER                        0x1C00
		#define GL_RENDERER                      0x1F01
		#define GL_RENDER_MODE                   0x0C40
		#define GL_REPEAT                        0x2901
		#define GL_REPLACE                       0x1E01
		#define GL_RETURN                        0x0102
		#define GL_RGB                           0x1907
		#define GL_RGB10                         0x8052
		#define GL_RGB10_A2                      0x8059
		#define GL_RGB12                         0x8053
		#define GL_RGB16                         0x8054
		#define GL_RGB4                          0x804F
		#define GL_RGB5                          0x8050
		#define GL_RGB5_A1                       0x8057
		#define GL_RGB8                          0x8051
		#define GL_RGBA                          0x1908
		#define GL_RGBA12                        0x805A
		#define GL_RGBA16                        0x805B
		#define GL_RGBA2                         0x8055
		#define GL_RGBA4                         0x8056
		#define GL_RGBA8                         0x8058
		#define GL_RGBA_MODE                     0x0C31
		#define GL_RIGHT                         0x0407
		#define GL_S                             0x2000
		#define GL_SCISSOR_BIT                   0x00080000
		#define GL_SCISSOR_BOX                   0x0C10
		#define GL_SCISSOR_TEST                  0x0C11
		#define GL_SELECT                        0x1C02
		#define GL_SELECTION_BUFFER_POINTER      0x0DF3
		#define GL_SELECTION_BUFFER_SIZE         0x0DF4
		#define GL_SET                           0x150F
		#define GL_SHADE_MODEL                   0x0B54
		#define GL_SHININESS                     0x1601
		#define GL_SHORT                         0x1402
		#define GL_SMOOTH                        0x1D01
		#define GL_SPECULAR                      0x1202
		#define GL_SPHERE_MAP                    0x2402
		#define GL_SPOT_CUTOFF                   0x1206
		#define GL_SPOT_DIRECTION                0x1204
		#define GL_SPOT_EXPONENT                 0x1205
		#define GL_SRC_ALPHA                     0x0302
		#define GL_SRC_ALPHA_SATURATE            0x0308
		#define GL_SRC_COLOR                     0x0300
		#define GL_STACK_OVERFLOW                0x0503
		#define GL_STACK_UNDERFLOW               0x0504
		#define GL_STENCIL                       0x1802
		#define GL_STENCIL_BITS                  0x0D57
		#define GL_STENCIL_BUFFER_BIT            0x00000400
		#define GL_STENCIL_CLEAR_VALUE           0x0B91
		#define GL_STENCIL_FAIL                  0x0B94
		#define GL_STENCIL_FUNC                  0x0B92
		#define GL_STENCIL_INDEX                 0x1901
		#define GL_STENCIL_PASS_DEPTH_FAIL       0x0B95
		#define GL_STENCIL_PASS_DEPTH_PASS       0x0B96
		#define GL_STENCIL_REF                   0x0B97
		#define GL_STENCIL_TEST                  0x0B90
		#define GL_STENCIL_VALUE_MASK            0x0B93
		#define GL_STENCIL_WRITEMASK             0x0B98
		#define GL_STEREO                        0x0C33
		#define GL_SUBPIXEL_BITS                 0x0D50
		#define GL_T                             0x2001
		#define GL_T2F_C3F_V3F                   0x2A2A
		#define GL_T2F_C4F_N3F_V3F               0x2A2C
		#define GL_T2F_C4UB_V3F                  0x2A29
		#define GL_T2F_N3F_V3F                   0x2A2B
		#define GL_T2F_V3F                       0x2A27
		#define GL_T4F_C4F_N3F_V4F               0x2A2D
		#define GL_T4F_V4F                       0x2A28
		#define GL_TEXTURE                       0x1702
		#define GL_TEXTURE_1D                    0x0DE0
		#define GL_TEXTURE_2D                    0x0DE1
		#define GL_TEXTURE_ALPHA_SIZE            0x805F
		#define GL_TEXTURE_BINDING_1D            0x8068
		#define GL_TEXTURE_BINDING_2D            0x8069
		#define GL_TEXTURE_BIT                   0x00040000
		#define GL_TEXTURE_BLUE_SIZE             0x805E
		#define GL_TEXTURE_BORDER                0x1005
		#define GL_TEXTURE_BORDER_COLOR          0x1004
		#define GL_TEXTURE_COMPONENTS            0x1003
		#define GL_TEXTURE_COORD_ARRAY           0x8078
		#define GL_TEXTURE_COORD_ARRAY_POINTER   0x8092
		#define GL_TEXTURE_COORD_ARRAY_SIZE      0x8088
		#define GL_TEXTURE_COORD_ARRAY_STRIDE    0x808A
		#define GL_TEXTURE_COORD_ARRAY_TYPE      0x8089
		#define GL_TEXTURE_ENV                   0x2300
		#define GL_TEXTURE_ENV_COLOR             0x2201
		#define GL_TEXTURE_ENV_MODE              0x2200
		#define GL_TEXTURE_GEN_MODE              0x2500
		#define GL_TEXTURE_GEN_Q                 0x0C63
		#define GL_TEXTURE_GEN_R                 0x0C62
		#define GL_TEXTURE_GEN_S                 0x0C60
		#define GL_TEXTURE_GEN_T                 0x0C61
		#define GL_TEXTURE_GREEN_SIZE            0x805D
		#define GL_TEXTURE_HEIGHT                0x1001
		#define GL_TEXTURE_INTENSITY_SIZE        0x8061
		#define GL_TEXTURE_INTERNAL_FORMAT       0x1003
		#define GL_TEXTURE_LUMINANCE_SIZE        0x8060
		#define GL_TEXTURE_MAG_FILTER            0x2800
		#define GL_TEXTURE_MATRIX                0x0BA8
		#define GL_TEXTURE_MIN_FILTER            0x2801
		#define GL_TEXTURE_PRIORITY              0x8066
		#define GL_TEXTURE_RED_SIZE              0x805C
		#define GL_TEXTURE_RESIDENT              0x8067
		#define GL_TEXTURE_STACK_DEPTH           0x0BA5
		#define GL_TEXTURE_WIDTH                 0x1000
		#define GL_TEXTURE_WRAP_S                0x2802
		#define GL_TEXTURE_WRAP_T                0x2803
		#define GL_TRANSFORM_BIT                 0x00001000
		#define GL_TRIANGLES                     0x0004
		#define GL_TRIANGLE_FAN                  0x0006
		#define GL_TRIANGLE_STRIP                0x0005
		#define GL_TRUE                          1
		#define GL_UNPACK_ALIGNMENT              0x0CF5
		#define GL_UNPACK_LSB_FIRST              0x0CF1
		#define GL_UNPACK_ROW_LENGTH             0x0CF2
		#define GL_UNPACK_SKIP_PIXELS            0x0CF4
		#define GL_UNPACK_SKIP_ROWS              0x0CF3
		#define GL_UNPACK_SWAP_BYTES             0x0CF0
		#define GL_UNSIGNED_BYTE                 0x1401
		#define GL_UNSIGNED_INT                  0x1405
		#define GL_UNSIGNED_SHORT                0x1403
		#define GL_V2F                           0x2A20
		#define GL_V3F                           0x2A21
		#define GL_VENDOR                        0x1F00
		#define GL_VERSION                       0x1F02
		#define GL_VERTEX_ARRAY                  0x8074
		#define GL_VERTEX_ARRAY_POINTER          0x808E
		#define GL_VERTEX_ARRAY_SIZE             0x807A
		#define GL_VERTEX_ARRAY_STRIDE           0x807C
		#define GL_VERTEX_ARRAY_TYPE             0x807B
		#define GL_VIEWPORT                      0x0BA2
		#define GL_VIEWPORT_BIT                  0x00000800
		#define GL_XOR                           0x1506
		#define GL_ZERO                          0
		#define GL_ZOOM_X                        0x0D16
		#define GL_ZOOM_Y                        0x0D17
		
		// Version: 1.2
		#define GL_ALIASED_LINE_WIDTH_RANGE      0x846E
		#define GL_ALIASED_POINT_SIZE_RANGE      0x846D
		#define GL_BGR                           0x80E0
		#define GL_BGRA                          0x80E1
		#define GL_CLAMP_TO_EDGE                 0x812F
		#define GL_LIGHT_MODEL_COLOR_CONTROL     0x81F8
		#define GL_MAX_3D_TEXTURE_SIZE           0x8073
		#define GL_MAX_ELEMENTS_INDICES          0x80E9
		#define GL_MAX_ELEMENTS_VERTICES         0x80E8
		#define GL_PACK_IMAGE_HEIGHT             0x806C
		#define GL_PACK_SKIP_IMAGES              0x806B
		#define GL_PROXY_TEXTURE_3D              0x8070
		#define GL_RESCALE_NORMAL                0x803A
		#define GL_SEPARATE_SPECULAR_COLOR       0x81FA
		#define GL_SINGLE_COLOR                  0x81F9
		#define GL_SMOOTH_LINE_WIDTH_GRANULARITY 0x0B23
		#define GL_SMOOTH_LINE_WIDTH_RANGE       0x0B22
		#define GL_SMOOTH_POINT_SIZE_GRANULARITY 0x0B13
		#define GL_SMOOTH_POINT_SIZE_RANGE       0x0B12
		#define GL_TEXTURE_3D                    0x806F
		#define GL_TEXTURE_BASE_LEVEL            0x813C
		#define GL_TEXTURE_BINDING_3D            0x806A
		#define GL_TEXTURE_DEPTH                 0x8071
		#define GL_TEXTURE_MAX_LEVEL             0x813D
		#define GL_TEXTURE_MAX_LOD               0x813B
		#define GL_TEXTURE_MIN_LOD               0x813A
		#define GL_TEXTURE_WRAP_R                0x8072
		#define GL_UNPACK_IMAGE_HEIGHT           0x806E
		#define GL_UNPACK_SKIP_IMAGES            0x806D
		#define GL_UNSIGNED_BYTE_2_3_3_REV       0x8362
		#define GL_UNSIGNED_BYTE_3_3_2           0x8032
		#define GL_UNSIGNED_INT_10_10_10_2       0x8036
		#define GL_UNSIGNED_INT_2_10_10_10_REV   0x8368
		#define GL_UNSIGNED_INT_8_8_8_8          0x8035
		#define GL_UNSIGNED_INT_8_8_8_8_REV      0x8367
		#define GL_UNSIGNED_SHORT_1_5_5_5_REV    0x8366
		#define GL_UNSIGNED_SHORT_4_4_4_4        0x8033
		#define GL_UNSIGNED_SHORT_4_4_4_4_REV    0x8365
		#define GL_UNSIGNED_SHORT_5_5_5_1        0x8034
		#define GL_UNSIGNED_SHORT_5_6_5          0x8363
		#define GL_UNSIGNED_SHORT_5_6_5_REV      0x8364
		
		// Version: 1.3
		#define GL_ACTIVE_TEXTURE                0x84E0
		#define GL_ADD_SIGNED                    0x8574
		#define GL_CLAMP_TO_BORDER               0x812D
		#define GL_CLIENT_ACTIVE_TEXTURE         0x84E1
		#define GL_COMBINE                       0x8570
		#define GL_COMBINE_ALPHA                 0x8572
		#define GL_COMBINE_RGB                   0x8571
		#define GL_COMPRESSED_ALPHA              0x84E9
		#define GL_COMPRESSED_INTENSITY          0x84EC
		#define GL_COMPRESSED_LUMINANCE          0x84EA
		#define GL_COMPRESSED_LUMINANCE_ALPHA    0x84EB
		#define GL_COMPRESSED_RGB                0x84ED
		#define GL_COMPRESSED_RGBA               0x84EE
		#define GL_COMPRESSED_TEXTURE_FORMATS    0x86A3
		#define GL_CONSTANT                      0x8576
		#define GL_DOT3_RGB                      0x86AE
		#define GL_DOT3_RGBA                     0x86AF
		#define GL_INTERPOLATE                   0x8575
		#define GL_MAX_CUBE_MAP_TEXTURE_SIZE     0x851C
		#define GL_MAX_TEXTURE_UNITS             0x84E2
		#define GL_MULTISAMPLE                   0x809D
		#define GL_MULTISAMPLE_BIT               0x20000000
		#define GL_NORMAL_MAP                    0x8511
		#define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
		#define GL_OPERAND0_ALPHA                0x8598
		#define GL_OPERAND0_RGB                  0x8590
		#define GL_OPERAND1_ALPHA                0x8599
		#define GL_OPERAND1_RGB                  0x8591
		#define GL_OPERAND2_ALPHA                0x859A
		#define GL_OPERAND2_RGB                  0x8592
		#define GL_PREVIOUS                      0x8578
		#define GL_PRIMARY_COLOR                 0x8577
		#define GL_PROXY_TEXTURE_CUBE_MAP        0x851B
		#define GL_REFLECTION_MAP                0x8512
		#define GL_RGB_SCALE                     0x8573
		#define GL_SAMPLES                       0x80A9
		#define GL_SAMPLE_ALPHA_TO_COVERAGE      0x809E
		#define GL_SAMPLE_ALPHA_TO_ONE           0x809F
		#define GL_SAMPLE_BUFFERS                0x80A8
		#define GL_SAMPLE_COVERAGE               0x80A0
		#define GL_SAMPLE_COVERAGE_INVERT        0x80AB
		#define GL_SAMPLE_COVERAGE_VALUE         0x80AA
		#define GL_SOURCE0_ALPHA                 0x8588
		#define GL_SOURCE0_RGB                   0x8580
		#define GL_SOURCE1_ALPHA                 0x8589
		#define GL_SOURCE1_RGB                   0x8581
		#define GL_SOURCE2_ALPHA                 0x858A
		#define GL_SOURCE2_RGB                   0x8582
		#define GL_SUBTRACT                      0x84E7
		#define GL_TEXTURE0                      0x84C0
		#define GL_TEXTURE1                      0x84C1
		#define GL_TEXTURE10                     0x84CA
		#define GL_TEXTURE11                     0x84CB
		#define GL_TEXTURE12                     0x84CC
		#define GL_TEXTURE13                     0x84CD
		#define GL_TEXTURE14                     0x84CE
		#define GL_TEXTURE15                     0x84CF
		#define GL_TEXTURE16                     0x84D0
		#define GL_TEXTURE17                     0x84D1
		#define GL_TEXTURE18                     0x84D2
		#define GL_TEXTURE19                     0x84D3
		#define GL_TEXTURE2                      0x84C2
		#define GL_TEXTURE20                     0x84D4
		#define GL_TEXTURE21                     0x84D5
		#define GL_TEXTURE22                     0x84D6
		#define GL_TEXTURE23                     0x84D7
		#define GL_TEXTURE24                     0x84D8
		#define GL_TEXTURE25                     0x84D9
		#define GL_TEXTURE26                     0x84DA
		#define GL_TEXTURE27                     0x84DB
		#define GL_TEXTURE28                     0x84DC
		#define GL_TEXTURE29                     0x84DD
		#define GL_TEXTURE3                      0x84C3
		#define GL_TEXTURE30                     0x84DE
		#define GL_TEXTURE31                     0x84DF
		#define GL_TEXTURE4                      0x84C4
		#define GL_TEXTURE5                      0x84C5
		#define GL_TEXTURE6                      0x84C6
		#define GL_TEXTURE7                      0x84C7
		#define GL_TEXTURE8                      0x84C8
		#define GL_TEXTURE9                      0x84C9
		#define GL_TEXTURE_BINDING_CUBE_MAP      0x8514
		#define GL_TEXTURE_COMPRESSED            0x86A1
		#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE 0x86A0
		#define GL_TEXTURE_COMPRESSION_HINT      0x84EF
		#define GL_TEXTURE_CUBE_MAP              0x8513
		#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X   0x8516
		#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y   0x8518
		#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z   0x851A
		#define GL_TEXTURE_CUBE_MAP_POSITIVE_X   0x8515
		#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y   0x8517
		#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z   0x8519
		#define GL_TRANSPOSE_COLOR_MATRIX        0x84E6
		#define GL_TRANSPOSE_MODELVIEW_MATRIX    0x84E3
		#define GL_TRANSPOSE_PROJECTION_MATRIX   0x84E4
		#define GL_TRANSPOSE_TEXTURE_MATRIX      0x84E5
		
		// Version: 1.4
		#define GL_BLEND_COLOR                   0x8005
		#define GL_BLEND_DST_ALPHA               0x80CA
		#define GL_BLEND_DST_RGB                 0x80C8
		#define GL_BLEND_EQUATION                0x8009
		#define GL_BLEND_SRC_ALPHA               0x80CB
		#define GL_BLEND_SRC_RGB                 0x80C9
		#define GL_COLOR_SUM                     0x8458
		#define GL_COMPARE_R_TO_TEXTURE          0x884E
		#define GL_CONSTANT_ALPHA                0x8003
		#define GL_CONSTANT_COLOR                0x8001
		#define GL_CURRENT_FOG_COORDINATE        0x8453
		#define GL_CURRENT_SECONDARY_COLOR       0x8459
		#define GL_DECR_WRAP                     0x8508
		#define GL_DEPTH_COMPONENT16             0x81A5
		#define GL_DEPTH_COMPONENT24             0x81A6
		#define GL_DEPTH_COMPONENT32             0x81A7
		#define GL_DEPTH_TEXTURE_MODE            0x884B
		#define GL_FOG_COORDINATE                0x8451
		#define GL_FOG_COORDINATE_ARRAY          0x8457
		#define GL_FOG_COORDINATE_ARRAY_POINTER  0x8456
		#define GL_FOG_COORDINATE_ARRAY_STRIDE   0x8455
		#define GL_FOG_COORDINATE_ARRAY_TYPE     0x8454
		#define GL_FOG_COORDINATE_SOURCE         0x8450
		#define GL_FRAGMENT_DEPTH                0x8452
		#define GL_FUNC_ADD                      0x8006
		#define GL_FUNC_REVERSE_SUBTRACT         0x800B
		#define GL_FUNC_SUBTRACT                 0x800A
		#define GL_GENERATE_MIPMAP               0x8191
		#define GL_GENERATE_MIPMAP_HINT          0x8192
		#define GL_INCR_WRAP                     0x8507
		#define GL_MAX                           0x8008
		#define GL_MAX_TEXTURE_LOD_BIAS          0x84FD
		#define GL_MIN                           0x8007
		#define GL_MIRRORED_REPEAT               0x8370
		#define GL_ONE_MINUS_CONSTANT_ALPHA      0x8004
		#define GL_ONE_MINUS_CONSTANT_COLOR      0x8002
		#define GL_POINT_DISTANCE_ATTENUATION    0x8129
		#define GL_POINT_FADE_THRESHOLD_SIZE     0x8128
		#define GL_POINT_SIZE_MAX                0x8127
		#define GL_POINT_SIZE_MIN                0x8126
		#define GL_SECONDARY_COLOR_ARRAY         0x845E
		#define GL_SECONDARY_COLOR_ARRAY_POINTER 0x845D
		#define GL_SECONDARY_COLOR_ARRAY_SIZE    0x845A
		#define GL_SECONDARY_COLOR_ARRAY_STRIDE  0x845C
		#define GL_SECONDARY_COLOR_ARRAY_TYPE    0x845B
		#define GL_TEXTURE_COMPARE_FUNC          0x884D
		#define GL_TEXTURE_COMPARE_MODE          0x884C
		#define GL_TEXTURE_DEPTH_SIZE            0x884A
		#define GL_TEXTURE_FILTER_CONTROL        0x8500
		#define GL_TEXTURE_LOD_BIAS              0x8501
		
		// Version: 1.5
		#define GL_ARRAY_BUFFER                  0x8892
		#define GL_ARRAY_BUFFER_BINDING          0x8894
		#define GL_BUFFER_ACCESS                 0x88BB
		#define GL_BUFFER_MAPPED                 0x88BC
		#define GL_BUFFER_MAP_POINTER            0x88BD
		#define GL_BUFFER_SIZE                   0x8764
		#define GL_BUFFER_USAGE                  0x8765
		#define GL_COLOR_ARRAY_BUFFER_BINDING    0x8898
		#define GL_CURRENT_FOG_COORD             0x8453
		#define GL_CURRENT_QUERY                 0x8865
		#define GL_DYNAMIC_COPY                  0x88EA
		#define GL_DYNAMIC_DRAW                  0x88E8
		#define GL_DYNAMIC_READ                  0x88E9
		#define GL_EDGE_FLAG_ARRAY_BUFFER_BINDING 0x889B
		#define GL_ELEMENT_ARRAY_BUFFER          0x8893
		#define GL_ELEMENT_ARRAY_BUFFER_BINDING  0x8895
		#define GL_FOG_COORD                     0x8451
		#define GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING 0x889D
		#define GL_FOG_COORD_ARRAY               0x8457
		#define GL_FOG_COORD_ARRAY_BUFFER_BINDING 0x889D
		#define GL_FOG_COORD_ARRAY_POINTER       0x8456
		#define GL_FOG_COORD_ARRAY_STRIDE        0x8455
		#define GL_FOG_COORD_ARRAY_TYPE          0x8454
		#define GL_FOG_COORD_SRC                 0x8450
		#define GL_INDEX_ARRAY_BUFFER_BINDING    0x8899
		#define GL_NORMAL_ARRAY_BUFFER_BINDING   0x8897
		#define GL_QUERY_COUNTER_BITS            0x8864
		#define GL_QUERY_RESULT                  0x8866
		#define GL_QUERY_RESULT_AVAILABLE        0x8867
		#define GL_READ_ONLY                     0x88B8
		#define GL_READ_WRITE                    0x88BA
		#define GL_SAMPLES_PASSED                0x8914
		#define GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING 0x889C
		#define GL_SRC0_ALPHA                    0x8588
		#define GL_SRC0_RGB                      0x8580
		#define GL_SRC1_ALPHA                    0x8589
		#define GL_SRC1_RGB                      0x8581
		#define GL_SRC2_ALPHA                    0x858A
		#define GL_SRC2_RGB                      0x8582
		#define GL_STATIC_COPY                   0x88E6
		#define GL_STATIC_DRAW                   0x88E4
		#define GL_STATIC_READ                   0x88E5
		#define GL_STREAM_COPY                   0x88E2
		#define GL_STREAM_DRAW                   0x88E0
		#define GL_STREAM_READ                   0x88E1
		#define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING 0x889A
		#define GL_VERTEX_ARRAY_BUFFER_BINDING   0x8896
		#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 0x889F
		#define GL_WEIGHT_ARRAY_BUFFER_BINDING   0x889E
		#define GL_WRITE_ONLY                    0x88B9
		
		// Version: 2.0
		#define GL_ACTIVE_ATTRIBUTES             0x8B89
		#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH   0x8B8A
		#define GL_ACTIVE_UNIFORMS               0x8B86
		#define GL_ACTIVE_UNIFORM_MAX_LENGTH     0x8B87
		#define GL_ATTACHED_SHADERS              0x8B85
		#define GL_BLEND_EQUATION_ALPHA          0x883D
		#define GL_BLEND_EQUATION_RGB            0x8009
		#define GL_BOOL                          0x8B56
		#define GL_BOOL_VEC2                     0x8B57
		#define GL_BOOL_VEC3                     0x8B58
		#define GL_BOOL_VEC4                     0x8B59
		#define GL_COMPILE_STATUS                0x8B81
		#define GL_COORD_REPLACE                 0x8862
		#define GL_CURRENT_PROGRAM               0x8B8D
		#define GL_CURRENT_VERTEX_ATTRIB         0x8626
		#define GL_DELETE_STATUS                 0x8B80
		#define GL_DRAW_BUFFER0                  0x8825
		#define GL_DRAW_BUFFER1                  0x8826
		#define GL_DRAW_BUFFER10                 0x882F
		#define GL_DRAW_BUFFER11                 0x8830
		#define GL_DRAW_BUFFER12                 0x8831
		#define GL_DRAW_BUFFER13                 0x8832
		#define GL_DRAW_BUFFER14                 0x8833
		#define GL_DRAW_BUFFER15                 0x8834
		#define GL_DRAW_BUFFER2                  0x8827
		#define GL_DRAW_BUFFER3                  0x8828
		#define GL_DRAW_BUFFER4                  0x8829
		#define GL_DRAW_BUFFER5                  0x882A
		#define GL_DRAW_BUFFER6                  0x882B
		#define GL_DRAW_BUFFER7                  0x882C
		#define GL_DRAW_BUFFER8                  0x882D
		#define GL_DRAW_BUFFER9                  0x882E
		#define GL_FLOAT_MAT2                    0x8B5A
		#define GL_FLOAT_MAT3                    0x8B5B
		#define GL_FLOAT_MAT4                    0x8B5C
		#define GL_FLOAT_VEC2                    0x8B50
		#define GL_FLOAT_VEC3                    0x8B51
		#define GL_FLOAT_VEC4                    0x8B52
		#define GL_FRAGMENT_SHADER               0x8B30
		#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
		#define GL_INFO_LOG_LENGTH               0x8B84
		#define GL_INT_VEC2                      0x8B53
		#define GL_INT_VEC3                      0x8B54
		#define GL_INT_VEC4                      0x8B55
		#define GL_LINK_STATUS                   0x8B82
		#define GL_LOWER_LEFT                    0x8CA1
		#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
		#define GL_MAX_DRAW_BUFFERS              0x8824
		#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS 0x8B49
		#define GL_MAX_TEXTURE_COORDS            0x8871
		#define GL_MAX_TEXTURE_IMAGE_UNITS       0x8872
		#define GL_MAX_VARYING_FLOATS            0x8B4B
		#define GL_MAX_VERTEX_ATTRIBS            0x8869
		#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
		#define GL_MAX_VERTEX_UNIFORM_COMPONENTS 0x8B4A
		#define GL_POINT_SPRITE                  0x8861
		#define GL_POINT_SPRITE_COORD_ORIGIN     0x8CA0
		#define GL_SAMPLER_1D                    0x8B5D
		#define GL_SAMPLER_1D_SHADOW             0x8B61
		#define GL_SAMPLER_2D                    0x8B5E
		#define GL_SAMPLER_2D_SHADOW             0x8B62
		#define GL_SAMPLER_3D                    0x8B5F
		#define GL_SAMPLER_CUBE                  0x8B60
		#define GL_SHADER_SOURCE_LENGTH          0x8B88
		#define GL_SHADER_TYPE                   0x8B4F
		#define GL_SHADING_LANGUAGE_VERSION      0x8B8C
		#define GL_STENCIL_BACK_FAIL             0x8801
		#define GL_STENCIL_BACK_FUNC             0x8800
		#define GL_STENCIL_BACK_PASS_DEPTH_FAIL  0x8802
		#define GL_STENCIL_BACK_PASS_DEPTH_PASS  0x8803
		#define GL_STENCIL_BACK_REF              0x8CA3
		#define GL_STENCIL_BACK_VALUE_MASK       0x8CA4
		#define GL_STENCIL_BACK_WRITEMASK        0x8CA5
		#define GL_UPPER_LEFT                    0x8CA2
		#define GL_VALIDATE_STATUS               0x8B83
		#define GL_VERTEX_ATTRIB_ARRAY_ENABLED   0x8622
		#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886A
		#define GL_VERTEX_ATTRIB_ARRAY_POINTER   0x8645
		#define GL_VERTEX_ATTRIB_ARRAY_SIZE      0x8623
		#define GL_VERTEX_ATTRIB_ARRAY_STRIDE    0x8624
		#define GL_VERTEX_ATTRIB_ARRAY_TYPE      0x8625
		#define GL_VERTEX_PROGRAM_POINT_SIZE     0x8642
		#define GL_VERTEX_PROGRAM_TWO_SIDE       0x8643
		#define GL_VERTEX_SHADER                 0x8B31
		
		// Version: 2.1
		#define GL_COMPRESSED_SLUMINANCE         0x8C4A
		#define GL_COMPRESSED_SLUMINANCE_ALPHA   0x8C4B
		#define GL_COMPRESSED_SRGB               0x8C48
		#define GL_COMPRESSED_SRGB_ALPHA         0x8C49
		#define GL_CURRENT_RASTER_SECONDARY_COLOR 0x845F
		#define GL_FLOAT_MAT2x3                  0x8B65
		#define GL_FLOAT_MAT2x4                  0x8B66
		#define GL_FLOAT_MAT3x2                  0x8B67
		#define GL_FLOAT_MAT3x4                  0x8B68
		#define GL_FLOAT_MAT4x2                  0x8B69
		#define GL_FLOAT_MAT4x3                  0x8B6A
		#define GL_PIXEL_PACK_BUFFER             0x88EB
		#define GL_PIXEL_PACK_BUFFER_BINDING     0x88ED
		#define GL_PIXEL_UNPACK_BUFFER           0x88EC
		#define GL_PIXEL_UNPACK_BUFFER_BINDING   0x88EF
		#define GL_SLUMINANCE                    0x8C46
		#define GL_SLUMINANCE8                   0x8C47
		#define GL_SLUMINANCE8_ALPHA8            0x8C45
		#define GL_SLUMINANCE_ALPHA              0x8C44
		#define GL_SRGB                          0x8C40
		#define GL_SRGB8                         0x8C41
		#define GL_SRGB8_ALPHA8                  0x8C43
		#define GL_SRGB_ALPHA                    0x8C42
		
		// Version: 3.0
		#define GL_ALPHA_INTEGER                 0x8D97
		#define GL_BGRA_INTEGER                  0x8D9B
		#define GL_BGR_INTEGER                   0x8D9A
		#define GL_BLUE_INTEGER                  0x8D96
		#define GL_BUFFER_ACCESS_FLAGS           0x911F
		#define GL_BUFFER_MAP_LENGTH             0x9120
		#define GL_BUFFER_MAP_OFFSET             0x9121
		#define GL_CLAMP_FRAGMENT_COLOR          0x891B
		#define GL_CLAMP_READ_COLOR              0x891C
		#define GL_CLAMP_VERTEX_COLOR            0x891A
		#define GL_CLIP_DISTANCE0                0x3000
		#define GL_CLIP_DISTANCE1                0x3001
		#define GL_CLIP_DISTANCE2                0x3002
		#define GL_CLIP_DISTANCE3                0x3003
		#define GL_CLIP_DISTANCE4                0x3004
		#define GL_CLIP_DISTANCE5                0x3005
		#define GL_CLIP_DISTANCE6                0x3006
		#define GL_CLIP_DISTANCE7                0x3007
		#define GL_COLOR_ATTACHMENT0             0x8CE0
		#define GL_COLOR_ATTACHMENT1             0x8CE1
		#define GL_COLOR_ATTACHMENT10            0x8CEA
		#define GL_COLOR_ATTACHMENT11            0x8CEB
		#define GL_COLOR_ATTACHMENT12            0x8CEC
		#define GL_COLOR_ATTACHMENT13            0x8CED
		#define GL_COLOR_ATTACHMENT14            0x8CEE
		#define GL_COLOR_ATTACHMENT15            0x8CEF
		#define GL_COLOR_ATTACHMENT2             0x8CE2
		#define GL_COLOR_ATTACHMENT3             0x8CE3
		#define GL_COLOR_ATTACHMENT4             0x8CE4
		#define GL_COLOR_ATTACHMENT5             0x8CE5
		#define GL_COLOR_ATTACHMENT6             0x8CE6
		#define GL_COLOR_ATTACHMENT7             0x8CE7
		#define GL_COLOR_ATTACHMENT8             0x8CE8
		#define GL_COLOR_ATTACHMENT9             0x8CE9
		#define GL_COMPARE_REF_TO_TEXTURE        0x884E
		#define GL_COMPRESSED_RED                0x8225
		#define GL_COMPRESSED_RED_RGTC1          0x8DBB
		#define GL_COMPRESSED_RG                 0x8226
		#define GL_COMPRESSED_RG_RGTC2           0x8DBD
		#define GL_COMPRESSED_SIGNED_RED_RGTC1   0x8DBC
		#define GL_COMPRESSED_SIGNED_RG_RGTC2    0x8DBE
		#define GL_CONTEXT_FLAGS                 0x821E
		#define GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT 0x00000001
		#define GL_DEPTH24_STENCIL8              0x88F0
		#define GL_DEPTH32F_STENCIL8             0x8CAD
		#define GL_DEPTH_ATTACHMENT              0x8D00
		#define GL_DEPTH_COMPONENT32F            0x8CAC
		#define GL_DEPTH_STENCIL                 0x84F9
		#define GL_DEPTH_STENCIL_ATTACHMENT      0x821A
		#define GL_DRAW_FRAMEBUFFER              0x8CA9
		#define GL_DRAW_FRAMEBUFFER_BINDING      0x8CA6
		#define GL_FIXED_ONLY                    0x891D
		#define GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8DAD
		#define GL_FRAMEBUFFER                   0x8D40
		#define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE 0x8215
		#define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE 0x8214
		#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
		#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
		#define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE 0x8216
		#define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE 0x8213
		#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
		#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
		#define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE 0x8212
		#define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE 0x8217
		#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
		#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8CD4
		#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
		#define GL_FRAMEBUFFER_BINDING           0x8CA6
		#define GL_FRAMEBUFFER_COMPLETE          0x8CD5
		#define GL_FRAMEBUFFER_DEFAULT           0x8218
		#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
		#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 0x8CDB
		#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
		#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8D56
		#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 0x8CDC
		#define GL_FRAMEBUFFER_SRGB              0x8DB9
		#define GL_FRAMEBUFFER_UNDEFINED         0x8219
		#define GL_FRAMEBUFFER_UNSUPPORTED       0x8CDD
		#define GL_GREEN_INTEGER                 0x8D95
		#define GL_HALF_FLOAT                    0x140B
		#define GL_INTERLEAVED_ATTRIBS           0x8C8C
		#define GL_INT_SAMPLER_1D                0x8DC9
		#define GL_INT_SAMPLER_1D_ARRAY          0x8DCE
		#define GL_INT_SAMPLER_2D                0x8DCA
		#define GL_INT_SAMPLER_2D_ARRAY          0x8DCF
		#define GL_INT_SAMPLER_3D                0x8DCB
		#define GL_INT_SAMPLER_CUBE              0x8DCC
		#define GL_INVALID_FRAMEBUFFER_OPERATION 0x0506
		#define GL_MAJOR_VERSION                 0x821B
		#define GL_MAP_FLUSH_EXPLICIT_BIT        0x0010
		#define GL_MAP_INVALIDATE_BUFFER_BIT     0x0008
		#define GL_MAP_INVALIDATE_RANGE_BIT      0x0004
		#define GL_MAP_READ_BIT                  0x0001
		#define GL_MAP_UNSYNCHRONIZED_BIT        0x0020
		#define GL_MAP_WRITE_BIT                 0x0002
		#define GL_MAX_ARRAY_TEXTURE_LAYERS      0x88FF
		#define GL_MAX_CLIP_DISTANCES            0x0D32
		#define GL_MAX_COLOR_ATTACHMENTS         0x8CDF
		#define GL_MAX_PROGRAM_TEXEL_OFFSET      0x8905
		#define GL_MAX_RENDERBUFFER_SIZE         0x84E8
		#define GL_MAX_SAMPLES                   0x8D57
		#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8C8A
		#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 0x8C8B
		#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 0x8C80
		#define GL_MAX_VARYING_COMPONENTS        0x8B4B
		#define GL_MINOR_VERSION                 0x821C
		#define GL_MIN_PROGRAM_TEXEL_OFFSET      0x8904
		#define GL_NUM_EXTENSIONS                0x821D
		#define GL_PRIMITIVES_GENERATED          0x8C87
		#define GL_PROXY_TEXTURE_1D_ARRAY        0x8C19
		#define GL_PROXY_TEXTURE_2D_ARRAY        0x8C1B
		#define GL_QUERY_BY_REGION_NO_WAIT       0x8E16
		#define GL_QUERY_BY_REGION_WAIT          0x8E15
		#define GL_QUERY_NO_WAIT                 0x8E14
		#define GL_QUERY_WAIT                    0x8E13
		#define GL_R11F_G11F_B10F                0x8C3A
		#define GL_R16                           0x822A
		#define GL_R16F                          0x822D
		#define GL_R16I                          0x8233
		#define GL_R16UI                         0x8234
		#define GL_R32F                          0x822E
		#define GL_R32I                          0x8235
		#define GL_R32UI                         0x8236
		#define GL_R8                            0x8229
		#define GL_R8I                           0x8231
		#define GL_R8UI                          0x8232
		#define GL_RASTERIZER_DISCARD            0x8C89
		#define GL_READ_FRAMEBUFFER              0x8CA8
		#define GL_READ_FRAMEBUFFER_BINDING      0x8CAA
		#define GL_RED_INTEGER                   0x8D94
		#define GL_RENDERBUFFER                  0x8D41
		#define GL_RENDERBUFFER_ALPHA_SIZE       0x8D53
		#define GL_RENDERBUFFER_BINDING          0x8CA7
		#define GL_RENDERBUFFER_BLUE_SIZE        0x8D52
		#define GL_RENDERBUFFER_DEPTH_SIZE       0x8D54
		#define GL_RENDERBUFFER_GREEN_SIZE       0x8D51
		#define GL_RENDERBUFFER_HEIGHT           0x8D43
		#define GL_RENDERBUFFER_INTERNAL_FORMAT  0x8D44
		#define GL_RENDERBUFFER_RED_SIZE         0x8D50
		#define GL_RENDERBUFFER_SAMPLES          0x8CAB
		#define GL_RENDERBUFFER_STENCIL_SIZE     0x8D55
		#define GL_RENDERBUFFER_WIDTH            0x8D42
		#define GL_RG                            0x8227
		#define GL_RG16                          0x822C
		#define GL_RG16F                         0x822F
		#define GL_RG16I                         0x8239
		#define GL_RG16UI                        0x823A
		#define GL_RG32F                         0x8230
		#define GL_RG32I                         0x823B
		#define GL_RG32UI                        0x823C
		#define GL_RG8                           0x822B
		#define GL_RG8I                          0x8237
		#define GL_RG8UI                         0x8238
		#define GL_RGB16F                        0x881B
		#define GL_RGB16I                        0x8D89
		#define GL_RGB16UI                       0x8D77
		#define GL_RGB32F                        0x8815
		#define GL_RGB32I                        0x8D83
		#define GL_RGB32UI                       0x8D71
		#define GL_RGB8I                         0x8D8F
		#define GL_RGB8UI                        0x8D7D
		#define GL_RGB9_E5                       0x8C3D
		#define GL_RGBA16F                       0x881A
		#define GL_RGBA16I                       0x8D88
		#define GL_RGBA16UI                      0x8D76
		#define GL_RGBA32F                       0x8814
		#define GL_RGBA32I                       0x8D82
		#define GL_RGBA32UI                      0x8D70
		#define GL_RGBA8I                        0x8D8E
		#define GL_RGBA8UI                       0x8D7C
		#define GL_RGBA_INTEGER                  0x8D99
		#define GL_RGB_INTEGER                   0x8D98
		#define GL_RG_INTEGER                    0x8228
		#define GL_SAMPLER_1D_ARRAY              0x8DC0
		#define GL_SAMPLER_1D_ARRAY_SHADOW       0x8DC3
		#define GL_SAMPLER_2D_ARRAY              0x8DC1
		#define GL_SAMPLER_2D_ARRAY_SHADOW       0x8DC4
		#define GL_SAMPLER_CUBE_SHADOW           0x8DC5
		#define GL_SEPARATE_ATTRIBS              0x8C8D
		#define GL_STENCIL_ATTACHMENT            0x8D20
		#define GL_STENCIL_INDEX1                0x8D46
		#define GL_STENCIL_INDEX16               0x8D49
		#define GL_STENCIL_INDEX4                0x8D47
		#define GL_STENCIL_INDEX8                0x8D48
		#define GL_TEXTURE_1D_ARRAY              0x8C18
		#define GL_TEXTURE_2D_ARRAY              0x8C1A
		#define GL_TEXTURE_ALPHA_TYPE            0x8C13
		#define GL_TEXTURE_BINDING_1D_ARRAY      0x8C1C
		#define GL_TEXTURE_BINDING_2D_ARRAY      0x8C1D
		#define GL_TEXTURE_BLUE_TYPE             0x8C12
		#define GL_TEXTURE_DEPTH_TYPE            0x8C16
		#define GL_TEXTURE_GREEN_TYPE            0x8C11
		#define GL_TEXTURE_RED_TYPE              0x8C10
		#define GL_TEXTURE_SHARED_SIZE           0x8C3F
		#define GL_TEXTURE_STENCIL_SIZE          0x88F1
		#define GL_TRANSFORM_FEEDBACK_BUFFER     0x8C8E
		#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING 0x8C8F
		#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE 0x8C7F
		#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE 0x8C85
		#define GL_TRANSFORM_FEEDBACK_BUFFER_START 0x8C84
		#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 0x8C88
		#define GL_TRANSFORM_FEEDBACK_VARYINGS   0x8C83
		#define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH 0x8C76
		#define GL_UNSIGNED_INT_10F_11F_11F_REV  0x8C3B
		#define GL_UNSIGNED_INT_24_8             0x84FA
		#define GL_UNSIGNED_INT_5_9_9_9_REV      0x8C3E
		#define GL_UNSIGNED_INT_SAMPLER_1D       0x8DD1
		#define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY 0x8DD6
		#define GL_UNSIGNED_INT_SAMPLER_2D       0x8DD2
		#define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY 0x8DD7
		#define GL_UNSIGNED_INT_SAMPLER_3D       0x8DD3
		#define GL_UNSIGNED_INT_SAMPLER_CUBE     0x8DD4
		#define GL_UNSIGNED_INT_VEC2             0x8DC6
		#define GL_UNSIGNED_INT_VEC3             0x8DC7
		#define GL_UNSIGNED_INT_VEC4             0x8DC8
		#define GL_UNSIGNED_NORMALIZED           0x8C17
		#define GL_VERTEX_ARRAY_BINDING          0x85B5
		#define GL_VERTEX_ATTRIB_ARRAY_INTEGER   0x88FD
		
		// Version: 3.1
		#define GL_ACTIVE_UNIFORM_BLOCKS         0x8A36
		#define GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH 0x8A35
		#define GL_COPY_READ_BUFFER              0x8F36
		#define GL_COPY_WRITE_BUFFER             0x8F37
		#define GL_INT_SAMPLER_2D_RECT           0x8DCD
		#define GL_INT_SAMPLER_BUFFER            0x8DD0
		#define GL_INVALID_INDEX                 0xFFFFFFFF
		#define GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS 0x8A33
		#define GL_MAX_COMBINED_UNIFORM_BLOCKS   0x8A2E
		#define GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS 0x8A31
		#define GL_MAX_FRAGMENT_UNIFORM_BLOCKS   0x8A2D
		#define GL_MAX_RECTANGLE_TEXTURE_SIZE    0x84F8
		#define GL_MAX_TEXTURE_BUFFER_SIZE       0x8C2B
		#define GL_MAX_UNIFORM_BLOCK_SIZE        0x8A30
		#define GL_MAX_UNIFORM_BUFFER_BINDINGS   0x8A2F
		#define GL_MAX_VERTEX_UNIFORM_BLOCKS     0x8A2B
		#define GL_PRIMITIVE_RESTART             0x8F9D
		#define GL_PRIMITIVE_RESTART_INDEX       0x8F9E
		#define GL_PROXY_TEXTURE_RECTANGLE       0x84F7
		#define GL_R16_SNORM                     0x8F98
		#define GL_R8_SNORM                      0x8F94
		#define GL_RG16_SNORM                    0x8F99
		#define GL_RG8_SNORM                     0x8F95
		#define GL_RGB16_SNORM                   0x8F9A
		#define GL_RGB8_SNORM                    0x8F96
		#define GL_RGBA16_SNORM                  0x8F9B
		#define GL_RGBA8_SNORM                   0x8F97
		#define GL_SAMPLER_2D_RECT               0x8B63
		#define GL_SAMPLER_2D_RECT_SHADOW        0x8B64
		#define GL_SAMPLER_BUFFER                0x8DC2
		#define GL_SIGNED_NORMALIZED             0x8F9C
		#define GL_TEXTURE_BINDING_BUFFER        0x8C2C
		#define GL_TEXTURE_BINDING_RECTANGLE     0x84F6
		#define GL_TEXTURE_BUFFER                0x8C2A
		#define GL_TEXTURE_BUFFER_DATA_STORE_BINDING 0x8C2D
		#define GL_TEXTURE_RECTANGLE             0x84F5
		#define GL_UNIFORM_ARRAY_STRIDE          0x8A3C
		#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS 0x8A42
		#define GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES 0x8A43
		#define GL_UNIFORM_BLOCK_BINDING         0x8A3F
		#define GL_UNIFORM_BLOCK_DATA_SIZE       0x8A40
		#define GL_UNIFORM_BLOCK_INDEX           0x8A3A
		#define GL_UNIFORM_BLOCK_NAME_LENGTH     0x8A41
		#define GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER 0x8A46
		#define GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER 0x8A44
		#define GL_UNIFORM_BUFFER                0x8A11
		#define GL_UNIFORM_BUFFER_BINDING        0x8A28
		#define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT 0x8A34
		#define GL_UNIFORM_BUFFER_SIZE           0x8A2A
		#define GL_UNIFORM_BUFFER_START          0x8A29
		#define GL_UNIFORM_IS_ROW_MAJOR          0x8A3E
		#define GL_UNIFORM_MATRIX_STRIDE         0x8A3D
		#define GL_UNIFORM_NAME_LENGTH           0x8A39
		#define GL_UNIFORM_OFFSET                0x8A3B
		#define GL_UNIFORM_SIZE                  0x8A38
		#define GL_UNIFORM_TYPE                  0x8A37
		#define GL_UNSIGNED_INT_SAMPLER_2D_RECT  0x8DD5
		#define GL_UNSIGNED_INT_SAMPLER_BUFFER   0x8DD8
		
		// Version: 3.2
		#define GL_ALREADY_SIGNALED              0x911A
		#define GL_CONDITION_SATISFIED           0x911C
		#define GL_CONTEXT_COMPATIBILITY_PROFILE_BIT 0x00000002
		#define GL_CONTEXT_CORE_PROFILE_BIT      0x00000001
		#define GL_CONTEXT_PROFILE_MASK          0x9126
		#define GL_DEPTH_CLAMP                   0x864F
		#define GL_FIRST_VERTEX_CONVENTION       0x8E4D
		#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED 0x8DA7
		#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 0x8DA8
		#define GL_GEOMETRY_INPUT_TYPE           0x8917
		#define GL_GEOMETRY_OUTPUT_TYPE          0x8918
		#define GL_GEOMETRY_SHADER               0x8DD9
		#define GL_GEOMETRY_VERTICES_OUT         0x8916
		#define GL_INT_SAMPLER_2D_MULTISAMPLE    0x9109
		#define GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910C
		#define GL_LAST_VERTEX_CONVENTION        0x8E4E
		#define GL_LINES_ADJACENCY               0x000A
		#define GL_LINE_STRIP_ADJACENCY          0x000B
		#define GL_MAX_COLOR_TEXTURE_SAMPLES     0x910E
		#define GL_MAX_DEPTH_TEXTURE_SAMPLES     0x910F
		#define GL_MAX_FRAGMENT_INPUT_COMPONENTS 0x9125
		#define GL_MAX_GEOMETRY_INPUT_COMPONENTS 0x9123
		#define GL_MAX_GEOMETRY_OUTPUT_COMPONENTS 0x9124
		#define GL_MAX_GEOMETRY_OUTPUT_VERTICES  0x8DE0
		#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS 0x8C29
		#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS 0x8DE1
		#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS 0x8DDF
		#define GL_MAX_INTEGER_SAMPLES           0x9110
		#define GL_MAX_SAMPLE_MASK_WORDS         0x8E59
		#define GL_MAX_SERVER_WAIT_TIMEOUT       0x9111
		#define GL_MAX_VERTEX_OUTPUT_COMPONENTS  0x9122
		#define GL_OBJECT_TYPE                   0x9112
		#define GL_PROGRAM_POINT_SIZE            0x8642
		#define GL_PROVOKING_VERTEX              0x8E4F
		#define GL_PROXY_TEXTURE_2D_MULTISAMPLE  0x9101
		#define GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9103
		#define GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION 0x8E4C
		#define GL_SAMPLER_2D_MULTISAMPLE        0x9108
		#define GL_SAMPLER_2D_MULTISAMPLE_ARRAY  0x910B
		#define GL_SAMPLE_MASK                   0x8E51
		#define GL_SAMPLE_MASK_VALUE             0x8E52
		#define GL_SAMPLE_POSITION               0x8E50
		#define GL_SIGNALED                      0x9119
		#define GL_SYNC_CONDITION                0x9113
		#define GL_SYNC_FENCE                    0x9116
		#define GL_SYNC_FLAGS                    0x9115
		#define GL_SYNC_FLUSH_COMMANDS_BIT       0x00000001
		#define GL_SYNC_GPU_COMMANDS_COMPLETE    0x9117
		#define GL_SYNC_STATUS                   0x9114
		#define GL_TEXTURE_2D_MULTISAMPLE        0x9100
		#define GL_TEXTURE_2D_MULTISAMPLE_ARRAY  0x9102
		#define GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
		#define GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
		#define GL_TEXTURE_CUBE_MAP_SEAMLESS     0x884F
		#define GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
		#define GL_TEXTURE_SAMPLES               0x9106
		#define GL_TIMEOUT_EXPIRED               0x911B
		#define GL_TIMEOUT_IGNORED               0xFFFFFFFFFFFFFFFF
		#define GL_TRIANGLES_ADJACENCY           0x000C
		#define GL_TRIANGLE_STRIP_ADJACENCY      0x000D
		#define GL_UNSIGNALED                    0x9118
		#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910A
		#define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910D
		#define GL_WAIT_FAILED                   0x911D
		
		// Version: 3.3
		#define GL_ANY_SAMPLES_PASSED            0x8C2F
		#define GL_INT_2_10_10_10_REV            0x8D9F
		#define GL_MAX_DUAL_SOURCE_DRAW_BUFFERS  0x88FC
		#define GL_ONE_MINUS_SRC1_ALPHA          0x88FB
		#define GL_ONE_MINUS_SRC1_COLOR          0x88FA
		#define GL_RGB10_A2UI                    0x906F
		#define GL_SAMPLER_BINDING               0x8919
		#define GL_SRC1_COLOR                    0x88F9
		#define GL_TEXTURE_SWIZZLE_A             0x8E45
		#define GL_TEXTURE_SWIZZLE_B             0x8E44
		#define GL_TEXTURE_SWIZZLE_G             0x8E43
		#define GL_TEXTURE_SWIZZLE_R             0x8E42
		#define GL_TEXTURE_SWIZZLE_RGBA          0x8E46
		#define GL_TIMESTAMP                     0x8E28
		#define GL_TIME_ELAPSED                  0x88BF
		#define GL_VERTEX_ATTRIB_ARRAY_DIVISOR   0x88FE
		
		// Version: 4.0
		#define GL_ACTIVE_SUBROUTINES            0x8DE5
		#define GL_ACTIVE_SUBROUTINE_MAX_LENGTH  0x8E48
		#define GL_ACTIVE_SUBROUTINE_UNIFORMS    0x8DE6
		#define GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS 0x8E47
		#define GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH 0x8E49
		#define GL_COMPATIBLE_SUBROUTINES        0x8E4B
		#define GL_DOUBLE_MAT2                   0x8F46
		#define GL_DOUBLE_MAT2x3                 0x8F49
		#define GL_DOUBLE_MAT2x4                 0x8F4A
		#define GL_DOUBLE_MAT3                   0x8F47
		#define GL_DOUBLE_MAT3x2                 0x8F4B
		#define GL_DOUBLE_MAT3x4                 0x8F4C
		#define GL_DOUBLE_MAT4                   0x8F48
		#define GL_DOUBLE_MAT4x2                 0x8F4D
		#define GL_DOUBLE_MAT4x3                 0x8F4E
		#define GL_DOUBLE_VEC2                   0x8FFC
		#define GL_DOUBLE_VEC3                   0x8FFD
		#define GL_DOUBLE_VEC4                   0x8FFE
		#define GL_DRAW_INDIRECT_BUFFER          0x8F3F
		#define GL_DRAW_INDIRECT_BUFFER_BINDING  0x8F43
		#define GL_FRACTIONAL_EVEN               0x8E7C
		#define GL_FRACTIONAL_ODD                0x8E7B
		#define GL_FRAGMENT_INTERPOLATION_OFFSET_BITS 0x8E5D
		#define GL_GEOMETRY_SHADER_INVOCATIONS   0x887F
		#define GL_INT_SAMPLER_CUBE_MAP_ARRAY    0x900E
		#define GL_ISOLINES                      0x8E7A
		#define GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS 0x8E1E
		#define GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8E1F
		#define GL_MAX_FRAGMENT_INTERPOLATION_OFFSET 0x8E5C
		#define GL_MAX_GEOMETRY_SHADER_INVOCATIONS 0x8E5A
		#define GL_MAX_PATCH_VERTICES            0x8E7D
		#define GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET 0x8E5F
		#define GL_MAX_SUBROUTINES               0x8DE7
		#define GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS 0x8DE8
		#define GL_MAX_TESS_CONTROL_INPUT_COMPONENTS 0x886C
		#define GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS 0x8E83
		#define GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS 0x8E81
		#define GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS 0x8E85
		#define GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS 0x8E89
		#define GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS 0x8E7F
		#define GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS 0x886D
		#define GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS 0x8E86
		#define GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS 0x8E82
		#define GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS 0x8E8A
		#define GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8E80
		#define GL_MAX_TESS_GEN_LEVEL            0x8E7E
		#define GL_MAX_TESS_PATCH_COMPONENTS     0x8E84
		#define GL_MAX_TRANSFORM_FEEDBACK_BUFFERS 0x8E70
		#define GL_MAX_VERTEX_STREAMS            0x8E71
		#define GL_MIN_FRAGMENT_INTERPOLATION_OFFSET 0x8E5B
		#define GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET 0x8E5E
		#define GL_MIN_SAMPLE_SHADING_VALUE      0x8C37
		#define GL_NUM_COMPATIBLE_SUBROUTINES    0x8E4A
		#define GL_PATCHES                       0x000E
		#define GL_PATCH_DEFAULT_INNER_LEVEL     0x8E73
		#define GL_PATCH_DEFAULT_OUTER_LEVEL     0x8E74
		#define GL_PATCH_VERTICES                0x8E72
		#define GL_PROXY_TEXTURE_CUBE_MAP_ARRAY  0x900B
		#define GL_SAMPLER_CUBE_MAP_ARRAY        0x900C
		#define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW 0x900D
		#define GL_SAMPLE_SHADING                0x8C36
		#define GL_TESS_CONTROL_OUTPUT_VERTICES  0x8E75
		#define GL_TESS_CONTROL_SHADER           0x8E88
		#define GL_TESS_EVALUATION_SHADER        0x8E87
		#define GL_TESS_GEN_MODE                 0x8E76
		#define GL_TESS_GEN_POINT_MODE           0x8E79
		#define GL_TESS_GEN_SPACING              0x8E77
		#define GL_TESS_GEN_VERTEX_ORDER         0x8E78
		#define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 0x900A
		#define GL_TEXTURE_CUBE_MAP_ARRAY        0x9009
		#define GL_TRANSFORM_FEEDBACK            0x8E22
		#define GL_TRANSFORM_FEEDBACK_BINDING    0x8E25
		#define GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE 0x8E24
		#define GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED 0x8E23
		#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER 0x84F0
		#define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER 0x84F1
		#define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY 0x900F
		
		// Version: 4.1
		#define GL_ACTIVE_PROGRAM                0x8259
		#define GL_ALL_SHADER_BITS               0xFFFFFFFF
		#define GL_FIXED                         0x140C
		#define GL_FRAGMENT_SHADER_BIT           0x00000002
		#define GL_GEOMETRY_SHADER_BIT           0x00000004
		#define GL_HIGH_FLOAT                    0x8DF2
		#define GL_HIGH_INT                      0x8DF5
		#define GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
		#define GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
		#define GL_LAYER_PROVOKING_VERTEX        0x825E
		#define GL_LOW_FLOAT                     0x8DF0
		#define GL_LOW_INT                       0x8DF3
		#define GL_MAX_FRAGMENT_UNIFORM_VECTORS  0x8DFD
		#define GL_MAX_VARYING_VECTORS           0x8DFC
		#define GL_MAX_VERTEX_UNIFORM_VECTORS    0x8DFB
		#define GL_MAX_VIEWPORTS                 0x825B
		#define GL_MEDIUM_FLOAT                  0x8DF1
		#define GL_MEDIUM_INT                    0x8DF4
		#define GL_NUM_PROGRAM_BINARY_FORMATS    0x87FE
		#define GL_NUM_SHADER_BINARY_FORMATS     0x8DF9
		#define GL_PROGRAM_BINARY_FORMATS        0x87FF
		#define GL_PROGRAM_BINARY_LENGTH         0x8741
		#define GL_PROGRAM_BINARY_RETRIEVABLE_HINT 0x8257
		#define GL_PROGRAM_PIPELINE_BINDING      0x825A
		#define GL_PROGRAM_SEPARABLE             0x8258
		#define GL_RGB565                        0x8D62
		#define GL_SHADER_BINARY_FORMATS         0x8DF8
		#define GL_SHADER_COMPILER               0x8DFA
		#define GL_TESS_CONTROL_SHADER_BIT       0x00000008
		#define GL_TESS_EVALUATION_SHADER_BIT    0x00000010
		#define GL_UNDEFINED_VERTEX              0x8260
		#define GL_VERTEX_SHADER_BIT             0x00000001
		#define GL_VIEWPORT_BOUNDS_RANGE         0x825D
		#define GL_VIEWPORT_INDEX_PROVOKING_VERTEX 0x825F
		#define GL_VIEWPORT_SUBPIXEL_BITS        0x825C
		
		// Version: 4.2
		#define GL_ACTIVE_ATOMIC_COUNTER_BUFFERS 0x92D9
		#define GL_ALL_BARRIER_BITS              0xFFFFFFFF
		#define GL_ATOMIC_COUNTER_BARRIER_BIT    0x00001000
		#define GL_ATOMIC_COUNTER_BUFFER         0x92C0
		#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS 0x92C5
		#define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES 0x92C6
		#define GL_ATOMIC_COUNTER_BUFFER_BINDING 0x92C1
		#define GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE 0x92C4
		#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER 0x92CB
		#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER 0x92CA
		#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER 0x92C8
		#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER 0x92C9
		#define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER 0x92C7
		#define GL_ATOMIC_COUNTER_BUFFER_SIZE    0x92C3
		#define GL_ATOMIC_COUNTER_BUFFER_START   0x92C2
		#define GL_BUFFER_UPDATE_BARRIER_BIT     0x00000200
		#define GL_COMMAND_BARRIER_BIT           0x00000040
		#define GL_ELEMENT_ARRAY_BARRIER_BIT     0x00000002
		#define GL_FRAMEBUFFER_BARRIER_BIT       0x00000400
		#define GL_IMAGE_1D                      0x904C
		#define GL_IMAGE_1D_ARRAY                0x9052
		#define GL_IMAGE_2D                      0x904D
		#define GL_IMAGE_2D_ARRAY                0x9053
		#define GL_IMAGE_2D_MULTISAMPLE          0x9055
		#define GL_IMAGE_2D_MULTISAMPLE_ARRAY    0x9056
		#define GL_IMAGE_2D_RECT                 0x904F
		#define GL_IMAGE_3D                      0x904E
		#define GL_IMAGE_BINDING_ACCESS          0x8F3E
		#define GL_IMAGE_BINDING_FORMAT          0x906E
		#define GL_IMAGE_BINDING_LAYER           0x8F3D
		#define GL_IMAGE_BINDING_LAYERED         0x8F3C
		#define GL_IMAGE_BINDING_LEVEL           0x8F3B
		#define GL_IMAGE_BINDING_NAME            0x8F3A
		#define GL_IMAGE_BUFFER                  0x9051
		#define GL_IMAGE_CUBE                    0x9050
		#define GL_IMAGE_CUBE_MAP_ARRAY          0x9054
		#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS 0x90C9
		#define GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE 0x90C8
		#define GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 0x90C7
		#define GL_INT_IMAGE_1D                  0x9057
		#define GL_INT_IMAGE_1D_ARRAY            0x905D
		#define GL_INT_IMAGE_2D                  0x9058
		#define GL_INT_IMAGE_2D_ARRAY            0x905E
		#define GL_INT_IMAGE_2D_MULTISAMPLE      0x9060
		#define GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY 0x9061
		#define GL_INT_IMAGE_2D_RECT             0x905A
		#define GL_INT_IMAGE_3D                  0x9059
		#define GL_INT_IMAGE_BUFFER              0x905C
		#define GL_INT_IMAGE_CUBE                0x905B
		#define GL_INT_IMAGE_CUBE_MAP_ARRAY      0x905F
		#define GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS 0x92DC
		#define GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE 0x92D8
		#define GL_MAX_COMBINED_ATOMIC_COUNTERS  0x92D7
		#define GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS 0x92D1
		#define GL_MAX_COMBINED_IMAGE_UNIFORMS   0x90CF
		#define GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS 0x8F39
		#define GL_MAX_FRAGMENT_ATOMIC_COUNTERS  0x92D6
		#define GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS 0x92D0
		#define GL_MAX_FRAGMENT_IMAGE_UNIFORMS   0x90CE
		#define GL_MAX_GEOMETRY_ATOMIC_COUNTERS  0x92D5
		#define GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS 0x92CF
		#define GL_MAX_GEOMETRY_IMAGE_UNIFORMS   0x90CD
		#define GL_MAX_IMAGE_SAMPLES             0x906D
		#define GL_MAX_IMAGE_UNITS               0x8F38
		#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS 0x92D3
		#define GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS 0x92CD
		#define GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS 0x90CB
		#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS 0x92D4
		#define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS 0x92CE
		#define GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS 0x90CC
		#define GL_MAX_VERTEX_ATOMIC_COUNTERS    0x92D2
		#define GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS 0x92CC
		#define GL_MAX_VERTEX_IMAGE_UNIFORMS     0x90CA
		#define GL_MIN_MAP_BUFFER_ALIGNMENT      0x90BC
		#define GL_NUM_SAMPLE_COUNTS             0x9380
		#define GL_PACK_COMPRESSED_BLOCK_DEPTH   0x912D
		#define GL_PACK_COMPRESSED_BLOCK_HEIGHT  0x912C
		#define GL_PACK_COMPRESSED_BLOCK_SIZE    0x912E
		#define GL_PACK_COMPRESSED_BLOCK_WIDTH   0x912B
		#define GL_PIXEL_BUFFER_BARRIER_BIT      0x00000080
		#define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT 0x00000020
		#define GL_TEXTURE_FETCH_BARRIER_BIT     0x00000008
		#define GL_TEXTURE_IMMUTABLE_FORMAT      0x912F
		#define GL_TEXTURE_UPDATE_BARRIER_BIT    0x00000100
		#define GL_TRANSFORM_FEEDBACK_BARRIER_BIT 0x00000800
		#define GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX 0x92DA
		#define GL_UNIFORM_BARRIER_BIT           0x00000004
		#define GL_UNPACK_COMPRESSED_BLOCK_DEPTH 0x9129
		#define GL_UNPACK_COMPRESSED_BLOCK_HEIGHT 0x9128
		#define GL_UNPACK_COMPRESSED_BLOCK_SIZE  0x912A
		#define GL_UNPACK_COMPRESSED_BLOCK_WIDTH 0x9127
		#define GL_UNSIGNED_INT_ATOMIC_COUNTER   0x92DB
		#define GL_UNSIGNED_INT_IMAGE_1D         0x9062
		#define GL_UNSIGNED_INT_IMAGE_1D_ARRAY   0x9068
		#define GL_UNSIGNED_INT_IMAGE_2D         0x9063
		#define GL_UNSIGNED_INT_IMAGE_2D_ARRAY   0x9069
		#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE 0x906B
		#define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY 0x906C
		#define GL_UNSIGNED_INT_IMAGE_2D_RECT    0x9065
		#define GL_UNSIGNED_INT_IMAGE_3D         0x9064
		#define GL_UNSIGNED_INT_IMAGE_BUFFER     0x9067
		#define GL_UNSIGNED_INT_IMAGE_CUBE       0x9066
		#define GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY 0x906A
		#define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT 0x00000001
		
		
		// Extension: 1.0
		extern void (CODEGEN_FUNCPTR *_ptrc_glAccum)(GLenum op, GLfloat value);
		#define glAccum _ptrc_glAccum
		extern void (CODEGEN_FUNCPTR *_ptrc_glAlphaFunc)(GLenum func, GLfloat ref);
		#define glAlphaFunc _ptrc_glAlphaFunc
		extern void (CODEGEN_FUNCPTR *_ptrc_glBegin)(GLenum mode);
		#define glBegin _ptrc_glBegin
		extern void (CODEGEN_FUNCPTR *_ptrc_glBitmap)(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap);
		#define glBitmap _ptrc_glBitmap
		extern void (CODEGEN_FUNCPTR *_ptrc_glBlendFunc)(GLenum sfactor, GLenum dfactor);
		#define glBlendFunc _ptrc_glBlendFunc
		extern void (CODEGEN_FUNCPTR *_ptrc_glCallList)(GLuint list);
		#define glCallList _ptrc_glCallList
		extern void (CODEGEN_FUNCPTR *_ptrc_glCallLists)(GLsizei n, GLenum type, const GLvoid * lists);
		#define glCallLists _ptrc_glCallLists
		extern void (CODEGEN_FUNCPTR *_ptrc_glClear)(GLbitfield mask);
		#define glClear _ptrc_glClear
		extern void (CODEGEN_FUNCPTR *_ptrc_glClearAccum)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
		#define glClearAccum _ptrc_glClearAccum
		extern void (CODEGEN_FUNCPTR *_ptrc_glClearColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
		#define glClearColor _ptrc_glClearColor
		extern void (CODEGEN_FUNCPTR *_ptrc_glClearDepth)(GLdouble depth);
		#define glClearDepth _ptrc_glClearDepth
		extern void (CODEGEN_FUNCPTR *_ptrc_glClearIndex)(GLfloat c);
		#define glClearIndex _ptrc_glClearIndex
		extern void (CODEGEN_FUNCPTR *_ptrc_glClearStencil)(GLint s);
		#define glClearStencil _ptrc_glClearStencil
		extern void (CODEGEN_FUNCPTR *_ptrc_glClipPlane)(GLenum plane, const GLdouble * equation);
		#define glClipPlane _ptrc_glClipPlane
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor3b)(GLbyte red, GLbyte green, GLbyte blue);
		#define glColor3b _ptrc_glColor3b
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor3bv)(const GLbyte * v);
		#define glColor3bv _ptrc_glColor3bv
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor3d)(GLdouble red, GLdouble green, GLdouble blue);
		#define glColor3d _ptrc_glColor3d
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor3dv)(const GLdouble * v);
		#define glColor3dv _ptrc_glColor3dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor3f)(GLfloat red, GLfloat green, GLfloat blue);
		#define glColor3f _ptrc_glColor3f
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor3fv)(const GLfloat * v);
		#define glColor3fv _ptrc_glColor3fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor3i)(GLint red, GLint green, GLint blue);
		#define glColor3i _ptrc_glColor3i
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor3iv)(const GLint * v);
		#define glColor3iv _ptrc_glColor3iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor3s)(GLshort red, GLshort green, GLshort blue);
		#define glColor3s _ptrc_glColor3s
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor3sv)(const GLshort * v);
		#define glColor3sv _ptrc_glColor3sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor3ub)(GLubyte red, GLubyte green, GLubyte blue);
		#define glColor3ub _ptrc_glColor3ub
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor3ubv)(const GLubyte * v);
		#define glColor3ubv _ptrc_glColor3ubv
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor3ui)(GLuint red, GLuint green, GLuint blue);
		#define glColor3ui _ptrc_glColor3ui
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor3uiv)(const GLuint * v);
		#define glColor3uiv _ptrc_glColor3uiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor3us)(GLushort red, GLushort green, GLushort blue);
		#define glColor3us _ptrc_glColor3us
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor3usv)(const GLushort * v);
		#define glColor3usv _ptrc_glColor3usv
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor4b)(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
		#define glColor4b _ptrc_glColor4b
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor4bv)(const GLbyte * v);
		#define glColor4bv _ptrc_glColor4bv
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor4d)(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
		#define glColor4d _ptrc_glColor4d
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor4dv)(const GLdouble * v);
		#define glColor4dv _ptrc_glColor4dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor4f)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
		#define glColor4f _ptrc_glColor4f
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor4fv)(const GLfloat * v);
		#define glColor4fv _ptrc_glColor4fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor4i)(GLint red, GLint green, GLint blue, GLint alpha);
		#define glColor4i _ptrc_glColor4i
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor4iv)(const GLint * v);
		#define glColor4iv _ptrc_glColor4iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor4s)(GLshort red, GLshort green, GLshort blue, GLshort alpha);
		#define glColor4s _ptrc_glColor4s
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor4sv)(const GLshort * v);
		#define glColor4sv _ptrc_glColor4sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor4ub)(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
		#define glColor4ub _ptrc_glColor4ub
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor4ubv)(const GLubyte * v);
		#define glColor4ubv _ptrc_glColor4ubv
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor4ui)(GLuint red, GLuint green, GLuint blue, GLuint alpha);
		#define glColor4ui _ptrc_glColor4ui
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor4uiv)(const GLuint * v);
		#define glColor4uiv _ptrc_glColor4uiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor4us)(GLushort red, GLushort green, GLushort blue, GLushort alpha);
		#define glColor4us _ptrc_glColor4us
		extern void (CODEGEN_FUNCPTR *_ptrc_glColor4usv)(const GLushort * v);
		#define glColor4usv _ptrc_glColor4usv
		extern void (CODEGEN_FUNCPTR *_ptrc_glColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
		#define glColorMask _ptrc_glColorMask
		extern void (CODEGEN_FUNCPTR *_ptrc_glColorMaterial)(GLenum face, GLenum mode);
		#define glColorMaterial _ptrc_glColorMaterial
		extern void (CODEGEN_FUNCPTR *_ptrc_glCopyPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
		#define glCopyPixels _ptrc_glCopyPixels
		extern void (CODEGEN_FUNCPTR *_ptrc_glCullFace)(GLenum mode);
		#define glCullFace _ptrc_glCullFace
		extern void (CODEGEN_FUNCPTR *_ptrc_glDeleteLists)(GLuint list, GLsizei range);
		#define glDeleteLists _ptrc_glDeleteLists
		extern void (CODEGEN_FUNCPTR *_ptrc_glDepthFunc)(GLenum func);
		#define glDepthFunc _ptrc_glDepthFunc
		extern void (CODEGEN_FUNCPTR *_ptrc_glDepthMask)(GLboolean flag);
		#define glDepthMask _ptrc_glDepthMask
		extern void (CODEGEN_FUNCPTR *_ptrc_glDepthRange)(GLdouble ren_near, GLdouble ren_far);
		#define glDepthRange _ptrc_glDepthRange
		extern void (CODEGEN_FUNCPTR *_ptrc_glDisable)(GLenum cap);
		#define glDisable _ptrc_glDisable
		extern void (CODEGEN_FUNCPTR *_ptrc_glDrawBuffer)(GLenum mode);
		#define glDrawBuffer _ptrc_glDrawBuffer
		extern void (CODEGEN_FUNCPTR *_ptrc_glDrawPixels)(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels);
		#define glDrawPixels _ptrc_glDrawPixels
		extern void (CODEGEN_FUNCPTR *_ptrc_glEdgeFlag)(GLboolean flag);
		#define glEdgeFlag _ptrc_glEdgeFlag
		extern void (CODEGEN_FUNCPTR *_ptrc_glEdgeFlagv)(const GLboolean * flag);
		#define glEdgeFlagv _ptrc_glEdgeFlagv
		extern void (CODEGEN_FUNCPTR *_ptrc_glEnable)(GLenum cap);
		#define glEnable _ptrc_glEnable
		extern void (CODEGEN_FUNCPTR *_ptrc_glEnd)();
		#define glEnd _ptrc_glEnd
		extern void (CODEGEN_FUNCPTR *_ptrc_glEndList)();
		#define glEndList _ptrc_glEndList
		extern void (CODEGEN_FUNCPTR *_ptrc_glEvalCoord1d)(GLdouble u);
		#define glEvalCoord1d _ptrc_glEvalCoord1d
		extern void (CODEGEN_FUNCPTR *_ptrc_glEvalCoord1dv)(const GLdouble * u);
		#define glEvalCoord1dv _ptrc_glEvalCoord1dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glEvalCoord1f)(GLfloat u);
		#define glEvalCoord1f _ptrc_glEvalCoord1f
		extern void (CODEGEN_FUNCPTR *_ptrc_glEvalCoord1fv)(const GLfloat * u);
		#define glEvalCoord1fv _ptrc_glEvalCoord1fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glEvalCoord2d)(GLdouble u, GLdouble v);
		#define glEvalCoord2d _ptrc_glEvalCoord2d
		extern void (CODEGEN_FUNCPTR *_ptrc_glEvalCoord2dv)(const GLdouble * u);
		#define glEvalCoord2dv _ptrc_glEvalCoord2dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glEvalCoord2f)(GLfloat u, GLfloat v);
		#define glEvalCoord2f _ptrc_glEvalCoord2f
		extern void (CODEGEN_FUNCPTR *_ptrc_glEvalCoord2fv)(const GLfloat * u);
		#define glEvalCoord2fv _ptrc_glEvalCoord2fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glEvalMesh1)(GLenum mode, GLint i1, GLint i2);
		#define glEvalMesh1 _ptrc_glEvalMesh1
		extern void (CODEGEN_FUNCPTR *_ptrc_glEvalMesh2)(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
		#define glEvalMesh2 _ptrc_glEvalMesh2
		extern void (CODEGEN_FUNCPTR *_ptrc_glEvalPoint1)(GLint i);
		#define glEvalPoint1 _ptrc_glEvalPoint1
		extern void (CODEGEN_FUNCPTR *_ptrc_glEvalPoint2)(GLint i, GLint j);
		#define glEvalPoint2 _ptrc_glEvalPoint2
		extern void (CODEGEN_FUNCPTR *_ptrc_glFeedbackBuffer)(GLsizei size, GLenum type, GLfloat * buffer);
		#define glFeedbackBuffer _ptrc_glFeedbackBuffer
		extern void (CODEGEN_FUNCPTR *_ptrc_glFinish)();
		#define glFinish _ptrc_glFinish
		extern void (CODEGEN_FUNCPTR *_ptrc_glFlush)();
		#define glFlush _ptrc_glFlush
		extern void (CODEGEN_FUNCPTR *_ptrc_glFogf)(GLenum pname, GLfloat param);
		#define glFogf _ptrc_glFogf
		extern void (CODEGEN_FUNCPTR *_ptrc_glFogfv)(GLenum pname, const GLfloat * params);
		#define glFogfv _ptrc_glFogfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glFogi)(GLenum pname, GLint param);
		#define glFogi _ptrc_glFogi
		extern void (CODEGEN_FUNCPTR *_ptrc_glFogiv)(GLenum pname, const GLint * params);
		#define glFogiv _ptrc_glFogiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glFrontFace)(GLenum mode);
		#define glFrontFace _ptrc_glFrontFace
		extern void (CODEGEN_FUNCPTR *_ptrc_glFrustum)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
		#define glFrustum _ptrc_glFrustum
		extern GLuint (CODEGEN_FUNCPTR *_ptrc_glGenLists)(GLsizei range);
		#define glGenLists _ptrc_glGenLists
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetBooleanv)(GLenum pname, GLboolean * params);
		#define glGetBooleanv _ptrc_glGetBooleanv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetClipPlane)(GLenum plane, GLdouble * equation);
		#define glGetClipPlane _ptrc_glGetClipPlane
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetDoublev)(GLenum pname, GLdouble * params);
		#define glGetDoublev _ptrc_glGetDoublev
		extern GLenum (CODEGEN_FUNCPTR *_ptrc_glGetError)();
		#define glGetError _ptrc_glGetError
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetFloatv)(GLenum pname, GLfloat * params);
		#define glGetFloatv _ptrc_glGetFloatv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetIntegerv)(GLenum pname, GLint * params);
		#define glGetIntegerv _ptrc_glGetIntegerv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetLightfv)(GLenum light, GLenum pname, GLfloat * params);
		#define glGetLightfv _ptrc_glGetLightfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetLightiv)(GLenum light, GLenum pname, GLint * params);
		#define glGetLightiv _ptrc_glGetLightiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetMapdv)(GLenum target, GLenum query, GLdouble * v);
		#define glGetMapdv _ptrc_glGetMapdv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetMapfv)(GLenum target, GLenum query, GLfloat * v);
		#define glGetMapfv _ptrc_glGetMapfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetMapiv)(GLenum target, GLenum query, GLint * v);
		#define glGetMapiv _ptrc_glGetMapiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetMaterialfv)(GLenum face, GLenum pname, GLfloat * params);
		#define glGetMaterialfv _ptrc_glGetMaterialfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetMaterialiv)(GLenum face, GLenum pname, GLint * params);
		#define glGetMaterialiv _ptrc_glGetMaterialiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetPixelMapfv)(GLenum map, GLfloat * values);
		#define glGetPixelMapfv _ptrc_glGetPixelMapfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetPixelMapuiv)(GLenum map, GLuint * values);
		#define glGetPixelMapuiv _ptrc_glGetPixelMapuiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetPixelMapusv)(GLenum map, GLushort * values);
		#define glGetPixelMapusv _ptrc_glGetPixelMapusv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetPolygonStipple)(GLubyte * mask);
		#define glGetPolygonStipple _ptrc_glGetPolygonStipple
		extern const GLubyte * (CODEGEN_FUNCPTR *_ptrc_glGetString)(GLenum name);
		#define glGetString _ptrc_glGetString
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetTexEnvfv)(GLenum target, GLenum pname, GLfloat * params);
		#define glGetTexEnvfv _ptrc_glGetTexEnvfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetTexEnviv)(GLenum target, GLenum pname, GLint * params);
		#define glGetTexEnviv _ptrc_glGetTexEnviv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetTexGendv)(GLenum coord, GLenum pname, GLdouble * params);
		#define glGetTexGendv _ptrc_glGetTexGendv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetTexGenfv)(GLenum coord, GLenum pname, GLfloat * params);
		#define glGetTexGenfv _ptrc_glGetTexGenfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetTexGeniv)(GLenum coord, GLenum pname, GLint * params);
		#define glGetTexGeniv _ptrc_glGetTexGeniv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetTexImage)(GLenum target, GLint level, GLenum format, GLenum type, GLvoid * pixels);
		#define glGetTexImage _ptrc_glGetTexImage
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetTexLevelParameterfv)(GLenum target, GLint level, GLenum pname, GLfloat * params);
		#define glGetTexLevelParameterfv _ptrc_glGetTexLevelParameterfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetTexLevelParameteriv)(GLenum target, GLint level, GLenum pname, GLint * params);
		#define glGetTexLevelParameteriv _ptrc_glGetTexLevelParameteriv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetTexParameterfv)(GLenum target, GLenum pname, GLfloat * params);
		#define glGetTexParameterfv _ptrc_glGetTexParameterfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetTexParameteriv)(GLenum target, GLenum pname, GLint * params);
		#define glGetTexParameteriv _ptrc_glGetTexParameteriv
		extern void (CODEGEN_FUNCPTR *_ptrc_glHint)(GLenum target, GLenum mode);
		#define glHint _ptrc_glHint
		extern void (CODEGEN_FUNCPTR *_ptrc_glIndexMask)(GLuint mask);
		#define glIndexMask _ptrc_glIndexMask
		extern void (CODEGEN_FUNCPTR *_ptrc_glIndexd)(GLdouble c);
		#define glIndexd _ptrc_glIndexd
		extern void (CODEGEN_FUNCPTR *_ptrc_glIndexdv)(const GLdouble * c);
		#define glIndexdv _ptrc_glIndexdv
		extern void (CODEGEN_FUNCPTR *_ptrc_glIndexf)(GLfloat c);
		#define glIndexf _ptrc_glIndexf
		extern void (CODEGEN_FUNCPTR *_ptrc_glIndexfv)(const GLfloat * c);
		#define glIndexfv _ptrc_glIndexfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glIndexi)(GLint c);
		#define glIndexi _ptrc_glIndexi
		extern void (CODEGEN_FUNCPTR *_ptrc_glIndexiv)(const GLint * c);
		#define glIndexiv _ptrc_glIndexiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glIndexs)(GLshort c);
		#define glIndexs _ptrc_glIndexs
		extern void (CODEGEN_FUNCPTR *_ptrc_glIndexsv)(const GLshort * c);
		#define glIndexsv _ptrc_glIndexsv
		extern void (CODEGEN_FUNCPTR *_ptrc_glInitNames)();
		#define glInitNames _ptrc_glInitNames
		extern GLboolean (CODEGEN_FUNCPTR *_ptrc_glIsEnabled)(GLenum cap);
		#define glIsEnabled _ptrc_glIsEnabled
		extern GLboolean (CODEGEN_FUNCPTR *_ptrc_glIsList)(GLuint list);
		#define glIsList _ptrc_glIsList
		extern void (CODEGEN_FUNCPTR *_ptrc_glLightModelf)(GLenum pname, GLfloat param);
		#define glLightModelf _ptrc_glLightModelf
		extern void (CODEGEN_FUNCPTR *_ptrc_glLightModelfv)(GLenum pname, const GLfloat * params);
		#define glLightModelfv _ptrc_glLightModelfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glLightModeli)(GLenum pname, GLint param);
		#define glLightModeli _ptrc_glLightModeli
		extern void (CODEGEN_FUNCPTR *_ptrc_glLightModeliv)(GLenum pname, const GLint * params);
		#define glLightModeliv _ptrc_glLightModeliv
		extern void (CODEGEN_FUNCPTR *_ptrc_glLightf)(GLenum light, GLenum pname, GLfloat param);
		#define glLightf _ptrc_glLightf
		extern void (CODEGEN_FUNCPTR *_ptrc_glLightfv)(GLenum light, GLenum pname, const GLfloat * params);
		#define glLightfv _ptrc_glLightfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glLighti)(GLenum light, GLenum pname, GLint param);
		#define glLighti _ptrc_glLighti
		extern void (CODEGEN_FUNCPTR *_ptrc_glLightiv)(GLenum light, GLenum pname, const GLint * params);
		#define glLightiv _ptrc_glLightiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glLineStipple)(GLint factor, GLushort pattern);
		#define glLineStipple _ptrc_glLineStipple
		extern void (CODEGEN_FUNCPTR *_ptrc_glLineWidth)(GLfloat width);
		#define glLineWidth _ptrc_glLineWidth
		extern void (CODEGEN_FUNCPTR *_ptrc_glListBase)(GLuint base);
		#define glListBase _ptrc_glListBase
		extern void (CODEGEN_FUNCPTR *_ptrc_glLoadIdentity)();
		#define glLoadIdentity _ptrc_glLoadIdentity
		extern void (CODEGEN_FUNCPTR *_ptrc_glLoadMatrixd)(const GLdouble * m);
		#define glLoadMatrixd _ptrc_glLoadMatrixd
		extern void (CODEGEN_FUNCPTR *_ptrc_glLoadMatrixf)(const GLfloat * m);
		#define glLoadMatrixf _ptrc_glLoadMatrixf
		extern void (CODEGEN_FUNCPTR *_ptrc_glLoadName)(GLuint name);
		#define glLoadName _ptrc_glLoadName
		extern void (CODEGEN_FUNCPTR *_ptrc_glLogicOp)(GLenum opcode);
		#define glLogicOp _ptrc_glLogicOp
		extern void (CODEGEN_FUNCPTR *_ptrc_glMap1d)(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points);
		#define glMap1d _ptrc_glMap1d
		extern void (CODEGEN_FUNCPTR *_ptrc_glMap1f)(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points);
		#define glMap1f _ptrc_glMap1f
		extern void (CODEGEN_FUNCPTR *_ptrc_glMap2d)(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points);
		#define glMap2d _ptrc_glMap2d
		extern void (CODEGEN_FUNCPTR *_ptrc_glMap2f)(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points);
		#define glMap2f _ptrc_glMap2f
		extern void (CODEGEN_FUNCPTR *_ptrc_glMapGrid1d)(GLint un, GLdouble u1, GLdouble u2);
		#define glMapGrid1d _ptrc_glMapGrid1d
		extern void (CODEGEN_FUNCPTR *_ptrc_glMapGrid1f)(GLint un, GLfloat u1, GLfloat u2);
		#define glMapGrid1f _ptrc_glMapGrid1f
		extern void (CODEGEN_FUNCPTR *_ptrc_glMapGrid2d)(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
		#define glMapGrid2d _ptrc_glMapGrid2d
		extern void (CODEGEN_FUNCPTR *_ptrc_glMapGrid2f)(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
		#define glMapGrid2f _ptrc_glMapGrid2f
		extern void (CODEGEN_FUNCPTR *_ptrc_glMaterialf)(GLenum face, GLenum pname, GLfloat param);
		#define glMaterialf _ptrc_glMaterialf
		extern void (CODEGEN_FUNCPTR *_ptrc_glMaterialfv)(GLenum face, GLenum pname, const GLfloat * params);
		#define glMaterialfv _ptrc_glMaterialfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glMateriali)(GLenum face, GLenum pname, GLint param);
		#define glMateriali _ptrc_glMateriali
		extern void (CODEGEN_FUNCPTR *_ptrc_glMaterialiv)(GLenum face, GLenum pname, const GLint * params);
		#define glMaterialiv _ptrc_glMaterialiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glMatrixMode)(GLenum mode);
		#define glMatrixMode _ptrc_glMatrixMode
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultMatrixd)(const GLdouble * m);
		#define glMultMatrixd _ptrc_glMultMatrixd
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultMatrixf)(const GLfloat * m);
		#define glMultMatrixf _ptrc_glMultMatrixf
		extern void (CODEGEN_FUNCPTR *_ptrc_glNewList)(GLuint list, GLenum mode);
		#define glNewList _ptrc_glNewList
		extern void (CODEGEN_FUNCPTR *_ptrc_glNormal3b)(GLbyte nx, GLbyte ny, GLbyte nz);
		#define glNormal3b _ptrc_glNormal3b
		extern void (CODEGEN_FUNCPTR *_ptrc_glNormal3bv)(const GLbyte * v);
		#define glNormal3bv _ptrc_glNormal3bv
		extern void (CODEGEN_FUNCPTR *_ptrc_glNormal3d)(GLdouble nx, GLdouble ny, GLdouble nz);
		#define glNormal3d _ptrc_glNormal3d
		extern void (CODEGEN_FUNCPTR *_ptrc_glNormal3dv)(const GLdouble * v);
		#define glNormal3dv _ptrc_glNormal3dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glNormal3f)(GLfloat nx, GLfloat ny, GLfloat nz);
		#define glNormal3f _ptrc_glNormal3f
		extern void (CODEGEN_FUNCPTR *_ptrc_glNormal3fv)(const GLfloat * v);
		#define glNormal3fv _ptrc_glNormal3fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glNormal3i)(GLint nx, GLint ny, GLint nz);
		#define glNormal3i _ptrc_glNormal3i
		extern void (CODEGEN_FUNCPTR *_ptrc_glNormal3iv)(const GLint * v);
		#define glNormal3iv _ptrc_glNormal3iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glNormal3s)(GLshort nx, GLshort ny, GLshort nz);
		#define glNormal3s _ptrc_glNormal3s
		extern void (CODEGEN_FUNCPTR *_ptrc_glNormal3sv)(const GLshort * v);
		#define glNormal3sv _ptrc_glNormal3sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glOrtho)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
		#define glOrtho _ptrc_glOrtho
		extern void (CODEGEN_FUNCPTR *_ptrc_glPassThrough)(GLfloat token);
		#define glPassThrough _ptrc_glPassThrough
		extern void (CODEGEN_FUNCPTR *_ptrc_glPixelMapfv)(GLenum map, GLsizei mapsize, const GLfloat * values);
		#define glPixelMapfv _ptrc_glPixelMapfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glPixelMapuiv)(GLenum map, GLsizei mapsize, const GLuint * values);
		#define glPixelMapuiv _ptrc_glPixelMapuiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glPixelMapusv)(GLenum map, GLsizei mapsize, const GLushort * values);
		#define glPixelMapusv _ptrc_glPixelMapusv
		extern void (CODEGEN_FUNCPTR *_ptrc_glPixelStoref)(GLenum pname, GLfloat param);
		#define glPixelStoref _ptrc_glPixelStoref
		extern void (CODEGEN_FUNCPTR *_ptrc_glPixelStorei)(GLenum pname, GLint param);
		#define glPixelStorei _ptrc_glPixelStorei
		extern void (CODEGEN_FUNCPTR *_ptrc_glPixelTransferf)(GLenum pname, GLfloat param);
		#define glPixelTransferf _ptrc_glPixelTransferf
		extern void (CODEGEN_FUNCPTR *_ptrc_glPixelTransferi)(GLenum pname, GLint param);
		#define glPixelTransferi _ptrc_glPixelTransferi
		extern void (CODEGEN_FUNCPTR *_ptrc_glPixelZoom)(GLfloat xfactor, GLfloat yfactor);
		#define glPixelZoom _ptrc_glPixelZoom
		extern void (CODEGEN_FUNCPTR *_ptrc_glPointSize)(GLfloat size);
		#define glPointSize _ptrc_glPointSize
		extern void (CODEGEN_FUNCPTR *_ptrc_glPolygonMode)(GLenum face, GLenum mode);
		#define glPolygonMode _ptrc_glPolygonMode
		extern void (CODEGEN_FUNCPTR *_ptrc_glPolygonStipple)(const GLubyte * mask);
		#define glPolygonStipple _ptrc_glPolygonStipple
		extern void (CODEGEN_FUNCPTR *_ptrc_glPopAttrib)();
		#define glPopAttrib _ptrc_glPopAttrib
		extern void (CODEGEN_FUNCPTR *_ptrc_glPopMatrix)();
		#define glPopMatrix _ptrc_glPopMatrix
		extern void (CODEGEN_FUNCPTR *_ptrc_glPopName)();
		#define glPopName _ptrc_glPopName
		extern void (CODEGEN_FUNCPTR *_ptrc_glPushAttrib)(GLbitfield mask);
		#define glPushAttrib _ptrc_glPushAttrib
		extern void (CODEGEN_FUNCPTR *_ptrc_glPushMatrix)();
		#define glPushMatrix _ptrc_glPushMatrix
		extern void (CODEGEN_FUNCPTR *_ptrc_glPushName)(GLuint name);
		#define glPushName _ptrc_glPushName
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos2d)(GLdouble x, GLdouble y);
		#define glRasterPos2d _ptrc_glRasterPos2d
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos2dv)(const GLdouble * v);
		#define glRasterPos2dv _ptrc_glRasterPos2dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos2f)(GLfloat x, GLfloat y);
		#define glRasterPos2f _ptrc_glRasterPos2f
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos2fv)(const GLfloat * v);
		#define glRasterPos2fv _ptrc_glRasterPos2fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos2i)(GLint x, GLint y);
		#define glRasterPos2i _ptrc_glRasterPos2i
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos2iv)(const GLint * v);
		#define glRasterPos2iv _ptrc_glRasterPos2iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos2s)(GLshort x, GLshort y);
		#define glRasterPos2s _ptrc_glRasterPos2s
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos2sv)(const GLshort * v);
		#define glRasterPos2sv _ptrc_glRasterPos2sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos3d)(GLdouble x, GLdouble y, GLdouble z);
		#define glRasterPos3d _ptrc_glRasterPos3d
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos3dv)(const GLdouble * v);
		#define glRasterPos3dv _ptrc_glRasterPos3dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos3f)(GLfloat x, GLfloat y, GLfloat z);
		#define glRasterPos3f _ptrc_glRasterPos3f
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos3fv)(const GLfloat * v);
		#define glRasterPos3fv _ptrc_glRasterPos3fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos3i)(GLint x, GLint y, GLint z);
		#define glRasterPos3i _ptrc_glRasterPos3i
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos3iv)(const GLint * v);
		#define glRasterPos3iv _ptrc_glRasterPos3iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos3s)(GLshort x, GLshort y, GLshort z);
		#define glRasterPos3s _ptrc_glRasterPos3s
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos3sv)(const GLshort * v);
		#define glRasterPos3sv _ptrc_glRasterPos3sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos4d)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
		#define glRasterPos4d _ptrc_glRasterPos4d
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos4dv)(const GLdouble * v);
		#define glRasterPos4dv _ptrc_glRasterPos4dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos4f)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		#define glRasterPos4f _ptrc_glRasterPos4f
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos4fv)(const GLfloat * v);
		#define glRasterPos4fv _ptrc_glRasterPos4fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos4i)(GLint x, GLint y, GLint z, GLint w);
		#define glRasterPos4i _ptrc_glRasterPos4i
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos4iv)(const GLint * v);
		#define glRasterPos4iv _ptrc_glRasterPos4iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos4s)(GLshort x, GLshort y, GLshort z, GLshort w);
		#define glRasterPos4s _ptrc_glRasterPos4s
		extern void (CODEGEN_FUNCPTR *_ptrc_glRasterPos4sv)(const GLshort * v);
		#define glRasterPos4sv _ptrc_glRasterPos4sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glReadBuffer)(GLenum mode);
		#define glReadBuffer _ptrc_glReadBuffer
		extern void (CODEGEN_FUNCPTR *_ptrc_glReadPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid * pixels);
		#define glReadPixels _ptrc_glReadPixels
		extern void (CODEGEN_FUNCPTR *_ptrc_glRectd)(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
		#define glRectd _ptrc_glRectd
		extern void (CODEGEN_FUNCPTR *_ptrc_glRectdv)(const GLdouble * v1, const GLdouble * v2);
		#define glRectdv _ptrc_glRectdv
		extern void (CODEGEN_FUNCPTR *_ptrc_glRectf)(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
		#define glRectf _ptrc_glRectf
		extern void (CODEGEN_FUNCPTR *_ptrc_glRectfv)(const GLfloat * v1, const GLfloat * v2);
		#define glRectfv _ptrc_glRectfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glRecti)(GLint x1, GLint y1, GLint x2, GLint y2);
		#define glRecti _ptrc_glRecti
		extern void (CODEGEN_FUNCPTR *_ptrc_glRectiv)(const GLint * v1, const GLint * v2);
		#define glRectiv _ptrc_glRectiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glRects)(GLshort x1, GLshort y1, GLshort x2, GLshort y2);
		#define glRects _ptrc_glRects
		extern void (CODEGEN_FUNCPTR *_ptrc_glRectsv)(const GLshort * v1, const GLshort * v2);
		#define glRectsv _ptrc_glRectsv
		extern GLint (CODEGEN_FUNCPTR *_ptrc_glRenderMode)(GLenum mode);
		#define glRenderMode _ptrc_glRenderMode
		extern void (CODEGEN_FUNCPTR *_ptrc_glRotated)(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
		#define glRotated _ptrc_glRotated
		extern void (CODEGEN_FUNCPTR *_ptrc_glRotatef)(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
		#define glRotatef _ptrc_glRotatef
		extern void (CODEGEN_FUNCPTR *_ptrc_glScaled)(GLdouble x, GLdouble y, GLdouble z);
		#define glScaled _ptrc_glScaled
		extern void (CODEGEN_FUNCPTR *_ptrc_glScalef)(GLfloat x, GLfloat y, GLfloat z);
		#define glScalef _ptrc_glScalef
		extern void (CODEGEN_FUNCPTR *_ptrc_glScissor)(GLint x, GLint y, GLsizei width, GLsizei height);
		#define glScissor _ptrc_glScissor
		extern void (CODEGEN_FUNCPTR *_ptrc_glSelectBuffer)(GLsizei size, GLuint * buffer);
		#define glSelectBuffer _ptrc_glSelectBuffer
		extern void (CODEGEN_FUNCPTR *_ptrc_glShadeModel)(GLenum mode);
		#define glShadeModel _ptrc_glShadeModel
		extern void (CODEGEN_FUNCPTR *_ptrc_glStencilFunc)(GLenum func, GLint ref, GLuint mask);
		#define glStencilFunc _ptrc_glStencilFunc
		extern void (CODEGEN_FUNCPTR *_ptrc_glStencilMask)(GLuint mask);
		#define glStencilMask _ptrc_glStencilMask
		extern void (CODEGEN_FUNCPTR *_ptrc_glStencilOp)(GLenum fail, GLenum zfail, GLenum zpass);
		#define glStencilOp _ptrc_glStencilOp
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord1d)(GLdouble s);
		#define glTexCoord1d _ptrc_glTexCoord1d
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord1dv)(const GLdouble * v);
		#define glTexCoord1dv _ptrc_glTexCoord1dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord1f)(GLfloat s);
		#define glTexCoord1f _ptrc_glTexCoord1f
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord1fv)(const GLfloat * v);
		#define glTexCoord1fv _ptrc_glTexCoord1fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord1i)(GLint s);
		#define glTexCoord1i _ptrc_glTexCoord1i
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord1iv)(const GLint * v);
		#define glTexCoord1iv _ptrc_glTexCoord1iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord1s)(GLshort s);
		#define glTexCoord1s _ptrc_glTexCoord1s
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord1sv)(const GLshort * v);
		#define glTexCoord1sv _ptrc_glTexCoord1sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord2d)(GLdouble s, GLdouble t);
		#define glTexCoord2d _ptrc_glTexCoord2d
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord2dv)(const GLdouble * v);
		#define glTexCoord2dv _ptrc_glTexCoord2dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord2f)(GLfloat s, GLfloat t);
		#define glTexCoord2f _ptrc_glTexCoord2f
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord2fv)(const GLfloat * v);
		#define glTexCoord2fv _ptrc_glTexCoord2fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord2i)(GLint s, GLint t);
		#define glTexCoord2i _ptrc_glTexCoord2i
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord2iv)(const GLint * v);
		#define glTexCoord2iv _ptrc_glTexCoord2iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord2s)(GLshort s, GLshort t);
		#define glTexCoord2s _ptrc_glTexCoord2s
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord2sv)(const GLshort * v);
		#define glTexCoord2sv _ptrc_glTexCoord2sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord3d)(GLdouble s, GLdouble t, GLdouble r);
		#define glTexCoord3d _ptrc_glTexCoord3d
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord3dv)(const GLdouble * v);
		#define glTexCoord3dv _ptrc_glTexCoord3dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord3f)(GLfloat s, GLfloat t, GLfloat r);
		#define glTexCoord3f _ptrc_glTexCoord3f
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord3fv)(const GLfloat * v);
		#define glTexCoord3fv _ptrc_glTexCoord3fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord3i)(GLint s, GLint t, GLint r);
		#define glTexCoord3i _ptrc_glTexCoord3i
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord3iv)(const GLint * v);
		#define glTexCoord3iv _ptrc_glTexCoord3iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord3s)(GLshort s, GLshort t, GLshort r);
		#define glTexCoord3s _ptrc_glTexCoord3s
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord3sv)(const GLshort * v);
		#define glTexCoord3sv _ptrc_glTexCoord3sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord4d)(GLdouble s, GLdouble t, GLdouble r, GLdouble q);
		#define glTexCoord4d _ptrc_glTexCoord4d
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord4dv)(const GLdouble * v);
		#define glTexCoord4dv _ptrc_glTexCoord4dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord4f)(GLfloat s, GLfloat t, GLfloat r, GLfloat q);
		#define glTexCoord4f _ptrc_glTexCoord4f
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord4fv)(const GLfloat * v);
		#define glTexCoord4fv _ptrc_glTexCoord4fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord4i)(GLint s, GLint t, GLint r, GLint q);
		#define glTexCoord4i _ptrc_glTexCoord4i
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord4iv)(const GLint * v);
		#define glTexCoord4iv _ptrc_glTexCoord4iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord4s)(GLshort s, GLshort t, GLshort r, GLshort q);
		#define glTexCoord4s _ptrc_glTexCoord4s
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoord4sv)(const GLshort * v);
		#define glTexCoord4sv _ptrc_glTexCoord4sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexEnvf)(GLenum target, GLenum pname, GLfloat param);
		#define glTexEnvf _ptrc_glTexEnvf
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexEnvfv)(GLenum target, GLenum pname, const GLfloat * params);
		#define glTexEnvfv _ptrc_glTexEnvfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexEnvi)(GLenum target, GLenum pname, GLint param);
		#define glTexEnvi _ptrc_glTexEnvi
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexEnviv)(GLenum target, GLenum pname, const GLint * params);
		#define glTexEnviv _ptrc_glTexEnviv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexGend)(GLenum coord, GLenum pname, GLdouble param);
		#define glTexGend _ptrc_glTexGend
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexGendv)(GLenum coord, GLenum pname, const GLdouble * params);
		#define glTexGendv _ptrc_glTexGendv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexGenf)(GLenum coord, GLenum pname, GLfloat param);
		#define glTexGenf _ptrc_glTexGenf
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexGenfv)(GLenum coord, GLenum pname, const GLfloat * params);
		#define glTexGenfv _ptrc_glTexGenfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexGeni)(GLenum coord, GLenum pname, GLint param);
		#define glTexGeni _ptrc_glTexGeni
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexGeniv)(GLenum coord, GLenum pname, const GLint * params);
		#define glTexGeniv _ptrc_glTexGeniv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexImage1D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid * pixels);
		#define glTexImage1D _ptrc_glTexImage1D
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * pixels);
		#define glTexImage2D _ptrc_glTexImage2D
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexParameterf)(GLenum target, GLenum pname, GLfloat param);
		#define glTexParameterf _ptrc_glTexParameterf
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexParameterfv)(GLenum target, GLenum pname, const GLfloat * params);
		#define glTexParameterfv _ptrc_glTexParameterfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexParameteri)(GLenum target, GLenum pname, GLint param);
		#define glTexParameteri _ptrc_glTexParameteri
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexParameteriv)(GLenum target, GLenum pname, const GLint * params);
		#define glTexParameteriv _ptrc_glTexParameteriv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTranslated)(GLdouble x, GLdouble y, GLdouble z);
		#define glTranslated _ptrc_glTranslated
		extern void (CODEGEN_FUNCPTR *_ptrc_glTranslatef)(GLfloat x, GLfloat y, GLfloat z);
		#define glTranslatef _ptrc_glTranslatef
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex2d)(GLdouble x, GLdouble y);
		#define glVertex2d _ptrc_glVertex2d
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex2dv)(const GLdouble * v);
		#define glVertex2dv _ptrc_glVertex2dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex2f)(GLfloat x, GLfloat y);
		#define glVertex2f _ptrc_glVertex2f
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex2fv)(const GLfloat * v);
		#define glVertex2fv _ptrc_glVertex2fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex2i)(GLint x, GLint y);
		#define glVertex2i _ptrc_glVertex2i
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex2iv)(const GLint * v);
		#define glVertex2iv _ptrc_glVertex2iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex2s)(GLshort x, GLshort y);
		#define glVertex2s _ptrc_glVertex2s
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex2sv)(const GLshort * v);
		#define glVertex2sv _ptrc_glVertex2sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex3d)(GLdouble x, GLdouble y, GLdouble z);
		#define glVertex3d _ptrc_glVertex3d
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex3dv)(const GLdouble * v);
		#define glVertex3dv _ptrc_glVertex3dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex3f)(GLfloat x, GLfloat y, GLfloat z);
		#define glVertex3f _ptrc_glVertex3f
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex3fv)(const GLfloat * v);
		#define glVertex3fv _ptrc_glVertex3fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex3i)(GLint x, GLint y, GLint z);
		#define glVertex3i _ptrc_glVertex3i
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex3iv)(const GLint * v);
		#define glVertex3iv _ptrc_glVertex3iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex3s)(GLshort x, GLshort y, GLshort z);
		#define glVertex3s _ptrc_glVertex3s
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex3sv)(const GLshort * v);
		#define glVertex3sv _ptrc_glVertex3sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex4d)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
		#define glVertex4d _ptrc_glVertex4d
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex4dv)(const GLdouble * v);
		#define glVertex4dv _ptrc_glVertex4dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex4f)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		#define glVertex4f _ptrc_glVertex4f
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex4fv)(const GLfloat * v);
		#define glVertex4fv _ptrc_glVertex4fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex4i)(GLint x, GLint y, GLint z, GLint w);
		#define glVertex4i _ptrc_glVertex4i
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex4iv)(const GLint * v);
		#define glVertex4iv _ptrc_glVertex4iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex4s)(GLshort x, GLshort y, GLshort z, GLshort w);
		#define glVertex4s _ptrc_glVertex4s
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertex4sv)(const GLshort * v);
		#define glVertex4sv _ptrc_glVertex4sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glViewport)(GLint x, GLint y, GLsizei width, GLsizei height);
		#define glViewport _ptrc_glViewport
		
		// Extension: 1.1
		extern GLboolean (CODEGEN_FUNCPTR *_ptrc_glAreTexturesResident)(GLsizei n, const GLuint * textures, GLboolean * residences);
		#define glAreTexturesResident _ptrc_glAreTexturesResident
		extern void (CODEGEN_FUNCPTR *_ptrc_glArrayElement)(GLint i);
		#define glArrayElement _ptrc_glArrayElement
		extern void (CODEGEN_FUNCPTR *_ptrc_glBindTexture)(GLenum target, GLuint texture);
		#define glBindTexture _ptrc_glBindTexture
		extern void (CODEGEN_FUNCPTR *_ptrc_glColorPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer);
		#define glColorPointer _ptrc_glColorPointer
		extern void (CODEGEN_FUNCPTR *_ptrc_glCopyTexImage1D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
		#define glCopyTexImage1D _ptrc_glCopyTexImage1D
		extern void (CODEGEN_FUNCPTR *_ptrc_glCopyTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
		#define glCopyTexImage2D _ptrc_glCopyTexImage2D
		extern void (CODEGEN_FUNCPTR *_ptrc_glCopyTexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
		#define glCopyTexSubImage1D _ptrc_glCopyTexSubImage1D
		extern void (CODEGEN_FUNCPTR *_ptrc_glCopyTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
		#define glCopyTexSubImage2D _ptrc_glCopyTexSubImage2D
		extern void (CODEGEN_FUNCPTR *_ptrc_glDeleteTextures)(GLsizei n, const GLuint * textures);
		#define glDeleteTextures _ptrc_glDeleteTextures
		extern void (CODEGEN_FUNCPTR *_ptrc_glDisableClientState)(GLenum ren_array);
		#define glDisableClientState _ptrc_glDisableClientState
		extern void (CODEGEN_FUNCPTR *_ptrc_glDrawArrays)(GLenum mode, GLint first, GLsizei count);
		#define glDrawArrays _ptrc_glDrawArrays
		extern void (CODEGEN_FUNCPTR *_ptrc_glDrawElements)(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices);
		#define glDrawElements _ptrc_glDrawElements
		extern void (CODEGEN_FUNCPTR *_ptrc_glEdgeFlagPointer)(GLsizei stride, const GLvoid * pointer);
		#define glEdgeFlagPointer _ptrc_glEdgeFlagPointer
		extern void (CODEGEN_FUNCPTR *_ptrc_glEnableClientState)(GLenum ren_array);
		#define glEnableClientState _ptrc_glEnableClientState
		extern void (CODEGEN_FUNCPTR *_ptrc_glGenTextures)(GLsizei n, GLuint * textures);
		#define glGenTextures _ptrc_glGenTextures
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetPointerv)(GLenum pname, GLvoid ** params);
		#define glGetPointerv _ptrc_glGetPointerv
		extern void (CODEGEN_FUNCPTR *_ptrc_glIndexPointer)(GLenum type, GLsizei stride, const GLvoid * pointer);
		#define glIndexPointer _ptrc_glIndexPointer
		extern void (CODEGEN_FUNCPTR *_ptrc_glIndexub)(GLubyte c);
		#define glIndexub _ptrc_glIndexub
		extern void (CODEGEN_FUNCPTR *_ptrc_glIndexubv)(const GLubyte * c);
		#define glIndexubv _ptrc_glIndexubv
		extern void (CODEGEN_FUNCPTR *_ptrc_glInterleavedArrays)(GLenum format, GLsizei stride, const GLvoid * pointer);
		#define glInterleavedArrays _ptrc_glInterleavedArrays
		extern GLboolean (CODEGEN_FUNCPTR *_ptrc_glIsTexture)(GLuint texture);
		#define glIsTexture _ptrc_glIsTexture
		extern void (CODEGEN_FUNCPTR *_ptrc_glNormalPointer)(GLenum type, GLsizei stride, const GLvoid * pointer);
		#define glNormalPointer _ptrc_glNormalPointer
		extern void (CODEGEN_FUNCPTR *_ptrc_glPolygonOffset)(GLfloat factor, GLfloat units);
		#define glPolygonOffset _ptrc_glPolygonOffset
		extern void (CODEGEN_FUNCPTR *_ptrc_glPopClientAttrib)();
		#define glPopClientAttrib _ptrc_glPopClientAttrib
		extern void (CODEGEN_FUNCPTR *_ptrc_glPrioritizeTextures)(GLsizei n, const GLuint * textures, const GLfloat * priorities);
		#define glPrioritizeTextures _ptrc_glPrioritizeTextures
		extern void (CODEGEN_FUNCPTR *_ptrc_glPushClientAttrib)(GLbitfield mask);
		#define glPushClientAttrib _ptrc_glPushClientAttrib
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexCoordPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer);
		#define glTexCoordPointer _ptrc_glTexCoordPointer
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid * pixels);
		#define glTexSubImage1D _ptrc_glTexSubImage1D
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels);
		#define glTexSubImage2D _ptrc_glTexSubImage2D
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer);
		#define glVertexPointer _ptrc_glVertexPointer
		
		// Extension: 1.2
		extern void (CODEGEN_FUNCPTR *_ptrc_glBlendColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
		#define glBlendColor _ptrc_glBlendColor
		extern void (CODEGEN_FUNCPTR *_ptrc_glBlendEquation)(GLenum mode);
		#define glBlendEquation _ptrc_glBlendEquation
		extern void (CODEGEN_FUNCPTR *_ptrc_glCopyTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
		#define glCopyTexSubImage3D _ptrc_glCopyTexSubImage3D
		extern void (CODEGEN_FUNCPTR *_ptrc_glDrawRangeElements)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices);
		#define glDrawRangeElements _ptrc_glDrawRangeElements
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexImage3D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid * pixels);
		#define glTexImage3D _ptrc_glTexImage3D
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * pixels);
		#define glTexSubImage3D _ptrc_glTexSubImage3D
		
		// Extension: 1.3
		extern void (CODEGEN_FUNCPTR *_ptrc_glActiveTexture)(GLenum texture);
		#define glActiveTexture _ptrc_glActiveTexture
		extern void (CODEGEN_FUNCPTR *_ptrc_glClientActiveTexture)(GLenum texture);
		#define glClientActiveTexture _ptrc_glClientActiveTexture
		extern void (CODEGEN_FUNCPTR *_ptrc_glCompressedTexImage1D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid * data);
		#define glCompressedTexImage1D _ptrc_glCompressedTexImage1D
		extern void (CODEGEN_FUNCPTR *_ptrc_glCompressedTexImage2D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid * data);
		#define glCompressedTexImage2D _ptrc_glCompressedTexImage2D
		extern void (CODEGEN_FUNCPTR *_ptrc_glCompressedTexImage3D)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid * data);
		#define glCompressedTexImage3D _ptrc_glCompressedTexImage3D
		extern void (CODEGEN_FUNCPTR *_ptrc_glCompressedTexSubImage1D)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid * data);
		#define glCompressedTexSubImage1D _ptrc_glCompressedTexSubImage1D
		extern void (CODEGEN_FUNCPTR *_ptrc_glCompressedTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid * data);
		#define glCompressedTexSubImage2D _ptrc_glCompressedTexSubImage2D
		extern void (CODEGEN_FUNCPTR *_ptrc_glCompressedTexSubImage3D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid * data);
		#define glCompressedTexSubImage3D _ptrc_glCompressedTexSubImage3D
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetCompressedTexImage)(GLenum target, GLint level, GLvoid * img);
		#define glGetCompressedTexImage _ptrc_glGetCompressedTexImage
		extern void (CODEGEN_FUNCPTR *_ptrc_glLoadTransposeMatrixd)(const GLdouble * m);
		#define glLoadTransposeMatrixd _ptrc_glLoadTransposeMatrixd
		extern void (CODEGEN_FUNCPTR *_ptrc_glLoadTransposeMatrixf)(const GLfloat * m);
		#define glLoadTransposeMatrixf _ptrc_glLoadTransposeMatrixf
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultTransposeMatrixd)(const GLdouble * m);
		#define glMultTransposeMatrixd _ptrc_glMultTransposeMatrixd
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultTransposeMatrixf)(const GLfloat * m);
		#define glMultTransposeMatrixf _ptrc_glMultTransposeMatrixf
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord1d)(GLenum target, GLdouble s);
		#define glMultiTexCoord1d _ptrc_glMultiTexCoord1d
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord1dv)(GLenum target, const GLdouble * v);
		#define glMultiTexCoord1dv _ptrc_glMultiTexCoord1dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord1f)(GLenum target, GLfloat s);
		#define glMultiTexCoord1f _ptrc_glMultiTexCoord1f
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord1fv)(GLenum target, const GLfloat * v);
		#define glMultiTexCoord1fv _ptrc_glMultiTexCoord1fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord1i)(GLenum target, GLint s);
		#define glMultiTexCoord1i _ptrc_glMultiTexCoord1i
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord1iv)(GLenum target, const GLint * v);
		#define glMultiTexCoord1iv _ptrc_glMultiTexCoord1iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord1s)(GLenum target, GLshort s);
		#define glMultiTexCoord1s _ptrc_glMultiTexCoord1s
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord1sv)(GLenum target, const GLshort * v);
		#define glMultiTexCoord1sv _ptrc_glMultiTexCoord1sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord2d)(GLenum target, GLdouble s, GLdouble t);
		#define glMultiTexCoord2d _ptrc_glMultiTexCoord2d
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord2dv)(GLenum target, const GLdouble * v);
		#define glMultiTexCoord2dv _ptrc_glMultiTexCoord2dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord2f)(GLenum target, GLfloat s, GLfloat t);
		#define glMultiTexCoord2f _ptrc_glMultiTexCoord2f
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord2fv)(GLenum target, const GLfloat * v);
		#define glMultiTexCoord2fv _ptrc_glMultiTexCoord2fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord2i)(GLenum target, GLint s, GLint t);
		#define glMultiTexCoord2i _ptrc_glMultiTexCoord2i
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord2iv)(GLenum target, const GLint * v);
		#define glMultiTexCoord2iv _ptrc_glMultiTexCoord2iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord2s)(GLenum target, GLshort s, GLshort t);
		#define glMultiTexCoord2s _ptrc_glMultiTexCoord2s
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord2sv)(GLenum target, const GLshort * v);
		#define glMultiTexCoord2sv _ptrc_glMultiTexCoord2sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord3d)(GLenum target, GLdouble s, GLdouble t, GLdouble r);
		#define glMultiTexCoord3d _ptrc_glMultiTexCoord3d
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord3dv)(GLenum target, const GLdouble * v);
		#define glMultiTexCoord3dv _ptrc_glMultiTexCoord3dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord3f)(GLenum target, GLfloat s, GLfloat t, GLfloat r);
		#define glMultiTexCoord3f _ptrc_glMultiTexCoord3f
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord3fv)(GLenum target, const GLfloat * v);
		#define glMultiTexCoord3fv _ptrc_glMultiTexCoord3fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord3i)(GLenum target, GLint s, GLint t, GLint r);
		#define glMultiTexCoord3i _ptrc_glMultiTexCoord3i
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord3iv)(GLenum target, const GLint * v);
		#define glMultiTexCoord3iv _ptrc_glMultiTexCoord3iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord3s)(GLenum target, GLshort s, GLshort t, GLshort r);
		#define glMultiTexCoord3s _ptrc_glMultiTexCoord3s
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord3sv)(GLenum target, const GLshort * v);
		#define glMultiTexCoord3sv _ptrc_glMultiTexCoord3sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord4d)(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
		#define glMultiTexCoord4d _ptrc_glMultiTexCoord4d
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord4dv)(GLenum target, const GLdouble * v);
		#define glMultiTexCoord4dv _ptrc_glMultiTexCoord4dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord4f)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
		#define glMultiTexCoord4f _ptrc_glMultiTexCoord4f
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord4fv)(GLenum target, const GLfloat * v);
		#define glMultiTexCoord4fv _ptrc_glMultiTexCoord4fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord4i)(GLenum target, GLint s, GLint t, GLint r, GLint q);
		#define glMultiTexCoord4i _ptrc_glMultiTexCoord4i
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord4iv)(GLenum target, const GLint * v);
		#define glMultiTexCoord4iv _ptrc_glMultiTexCoord4iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord4s)(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
		#define glMultiTexCoord4s _ptrc_glMultiTexCoord4s
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiTexCoord4sv)(GLenum target, const GLshort * v);
		#define glMultiTexCoord4sv _ptrc_glMultiTexCoord4sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glSampleCoverage)(GLfloat value, GLboolean invert);
		#define glSampleCoverage _ptrc_glSampleCoverage
		
		// Extension: 1.4
		extern void (CODEGEN_FUNCPTR *_ptrc_glBlendFuncSeparate)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
		#define glBlendFuncSeparate _ptrc_glBlendFuncSeparate
		extern void (CODEGEN_FUNCPTR *_ptrc_glFogCoordPointer)(GLenum type, GLsizei stride, const GLvoid * pointer);
		#define glFogCoordPointer _ptrc_glFogCoordPointer
		extern void (CODEGEN_FUNCPTR *_ptrc_glFogCoordd)(GLdouble coord);
		#define glFogCoordd _ptrc_glFogCoordd
		extern void (CODEGEN_FUNCPTR *_ptrc_glFogCoorddv)(const GLdouble * coord);
		#define glFogCoorddv _ptrc_glFogCoorddv
		extern void (CODEGEN_FUNCPTR *_ptrc_glFogCoordf)(GLfloat coord);
		#define glFogCoordf _ptrc_glFogCoordf
		extern void (CODEGEN_FUNCPTR *_ptrc_glFogCoordfv)(const GLfloat * coord);
		#define glFogCoordfv _ptrc_glFogCoordfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiDrawArrays)(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount);
		#define glMultiDrawArrays _ptrc_glMultiDrawArrays
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiDrawElements)(GLenum mode, const GLsizei * count, GLenum type, const GLvoid *const* indices, GLsizei drawcount);
		#define glMultiDrawElements _ptrc_glMultiDrawElements
		extern void (CODEGEN_FUNCPTR *_ptrc_glPointParameterf)(GLenum pname, GLfloat param);
		#define glPointParameterf _ptrc_glPointParameterf
		extern void (CODEGEN_FUNCPTR *_ptrc_glPointParameterfv)(GLenum pname, const GLfloat * params);
		#define glPointParameterfv _ptrc_glPointParameterfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glPointParameteri)(GLenum pname, GLint param);
		#define glPointParameteri _ptrc_glPointParameteri
		extern void (CODEGEN_FUNCPTR *_ptrc_glPointParameteriv)(GLenum pname, const GLint * params);
		#define glPointParameteriv _ptrc_glPointParameteriv
		extern void (CODEGEN_FUNCPTR *_ptrc_glSecondaryColor3b)(GLbyte red, GLbyte green, GLbyte blue);
		#define glSecondaryColor3b _ptrc_glSecondaryColor3b
		extern void (CODEGEN_FUNCPTR *_ptrc_glSecondaryColor3bv)(const GLbyte * v);
		#define glSecondaryColor3bv _ptrc_glSecondaryColor3bv
		extern void (CODEGEN_FUNCPTR *_ptrc_glSecondaryColor3d)(GLdouble red, GLdouble green, GLdouble blue);
		#define glSecondaryColor3d _ptrc_glSecondaryColor3d
		extern void (CODEGEN_FUNCPTR *_ptrc_glSecondaryColor3dv)(const GLdouble * v);
		#define glSecondaryColor3dv _ptrc_glSecondaryColor3dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glSecondaryColor3f)(GLfloat red, GLfloat green, GLfloat blue);
		#define glSecondaryColor3f _ptrc_glSecondaryColor3f
		extern void (CODEGEN_FUNCPTR *_ptrc_glSecondaryColor3fv)(const GLfloat * v);
		#define glSecondaryColor3fv _ptrc_glSecondaryColor3fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glSecondaryColor3i)(GLint red, GLint green, GLint blue);
		#define glSecondaryColor3i _ptrc_glSecondaryColor3i
		extern void (CODEGEN_FUNCPTR *_ptrc_glSecondaryColor3iv)(const GLint * v);
		#define glSecondaryColor3iv _ptrc_glSecondaryColor3iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glSecondaryColor3s)(GLshort red, GLshort green, GLshort blue);
		#define glSecondaryColor3s _ptrc_glSecondaryColor3s
		extern void (CODEGEN_FUNCPTR *_ptrc_glSecondaryColor3sv)(const GLshort * v);
		#define glSecondaryColor3sv _ptrc_glSecondaryColor3sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glSecondaryColor3ub)(GLubyte red, GLubyte green, GLubyte blue);
		#define glSecondaryColor3ub _ptrc_glSecondaryColor3ub
		extern void (CODEGEN_FUNCPTR *_ptrc_glSecondaryColor3ubv)(const GLubyte * v);
		#define glSecondaryColor3ubv _ptrc_glSecondaryColor3ubv
		extern void (CODEGEN_FUNCPTR *_ptrc_glSecondaryColor3ui)(GLuint red, GLuint green, GLuint blue);
		#define glSecondaryColor3ui _ptrc_glSecondaryColor3ui
		extern void (CODEGEN_FUNCPTR *_ptrc_glSecondaryColor3uiv)(const GLuint * v);
		#define glSecondaryColor3uiv _ptrc_glSecondaryColor3uiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glSecondaryColor3us)(GLushort red, GLushort green, GLushort blue);
		#define glSecondaryColor3us _ptrc_glSecondaryColor3us
		extern void (CODEGEN_FUNCPTR *_ptrc_glSecondaryColor3usv)(const GLushort * v);
		#define glSecondaryColor3usv _ptrc_glSecondaryColor3usv
		extern void (CODEGEN_FUNCPTR *_ptrc_glSecondaryColorPointer)(GLint size, GLenum type, GLsizei stride, const GLvoid * pointer);
		#define glSecondaryColorPointer _ptrc_glSecondaryColorPointer
		extern void (CODEGEN_FUNCPTR *_ptrc_glWindowPos2d)(GLdouble x, GLdouble y);
		#define glWindowPos2d _ptrc_glWindowPos2d
		extern void (CODEGEN_FUNCPTR *_ptrc_glWindowPos2dv)(const GLdouble * v);
		#define glWindowPos2dv _ptrc_glWindowPos2dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glWindowPos2f)(GLfloat x, GLfloat y);
		#define glWindowPos2f _ptrc_glWindowPos2f
		extern void (CODEGEN_FUNCPTR *_ptrc_glWindowPos2fv)(const GLfloat * v);
		#define glWindowPos2fv _ptrc_glWindowPos2fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glWindowPos2i)(GLint x, GLint y);
		#define glWindowPos2i _ptrc_glWindowPos2i
		extern void (CODEGEN_FUNCPTR *_ptrc_glWindowPos2iv)(const GLint * v);
		#define glWindowPos2iv _ptrc_glWindowPos2iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glWindowPos2s)(GLshort x, GLshort y);
		#define glWindowPos2s _ptrc_glWindowPos2s
		extern void (CODEGEN_FUNCPTR *_ptrc_glWindowPos2sv)(const GLshort * v);
		#define glWindowPos2sv _ptrc_glWindowPos2sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glWindowPos3d)(GLdouble x, GLdouble y, GLdouble z);
		#define glWindowPos3d _ptrc_glWindowPos3d
		extern void (CODEGEN_FUNCPTR *_ptrc_glWindowPos3dv)(const GLdouble * v);
		#define glWindowPos3dv _ptrc_glWindowPos3dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glWindowPos3f)(GLfloat x, GLfloat y, GLfloat z);
		#define glWindowPos3f _ptrc_glWindowPos3f
		extern void (CODEGEN_FUNCPTR *_ptrc_glWindowPos3fv)(const GLfloat * v);
		#define glWindowPos3fv _ptrc_glWindowPos3fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glWindowPos3i)(GLint x, GLint y, GLint z);
		#define glWindowPos3i _ptrc_glWindowPos3i
		extern void (CODEGEN_FUNCPTR *_ptrc_glWindowPos3iv)(const GLint * v);
		#define glWindowPos3iv _ptrc_glWindowPos3iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glWindowPos3s)(GLshort x, GLshort y, GLshort z);
		#define glWindowPos3s _ptrc_glWindowPos3s
		extern void (CODEGEN_FUNCPTR *_ptrc_glWindowPos3sv)(const GLshort * v);
		#define glWindowPos3sv _ptrc_glWindowPos3sv
		
		// Extension: 1.5
		extern void (CODEGEN_FUNCPTR *_ptrc_glBeginQuery)(GLenum target, GLuint id);
		#define glBeginQuery _ptrc_glBeginQuery
		extern void (CODEGEN_FUNCPTR *_ptrc_glBindBuffer)(GLenum target, GLuint buffer);
		#define glBindBuffer _ptrc_glBindBuffer
		extern void (CODEGEN_FUNCPTR *_ptrc_glBufferData)(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage);
		#define glBufferData _ptrc_glBufferData
		extern void (CODEGEN_FUNCPTR *_ptrc_glBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid * data);
		#define glBufferSubData _ptrc_glBufferSubData
		extern void (CODEGEN_FUNCPTR *_ptrc_glDeleteBuffers)(GLsizei n, const GLuint * buffers);
		#define glDeleteBuffers _ptrc_glDeleteBuffers
		extern void (CODEGEN_FUNCPTR *_ptrc_glDeleteQueries)(GLsizei n, const GLuint * ids);
		#define glDeleteQueries _ptrc_glDeleteQueries
		extern void (CODEGEN_FUNCPTR *_ptrc_glEndQuery)(GLenum target);
		#define glEndQuery _ptrc_glEndQuery
		extern void (CODEGEN_FUNCPTR *_ptrc_glGenBuffers)(GLsizei n, GLuint * buffers);
		#define glGenBuffers _ptrc_glGenBuffers
		extern void (CODEGEN_FUNCPTR *_ptrc_glGenQueries)(GLsizei n, GLuint * ids);
		#define glGenQueries _ptrc_glGenQueries
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetBufferParameteriv)(GLenum target, GLenum pname, GLint * params);
		#define glGetBufferParameteriv _ptrc_glGetBufferParameteriv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetBufferPointerv)(GLenum target, GLenum pname, GLvoid ** params);
		#define glGetBufferPointerv _ptrc_glGetBufferPointerv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid * data);
		#define glGetBufferSubData _ptrc_glGetBufferSubData
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetQueryObjectiv)(GLuint id, GLenum pname, GLint * params);
		#define glGetQueryObjectiv _ptrc_glGetQueryObjectiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetQueryObjectuiv)(GLuint id, GLenum pname, GLuint * params);
		#define glGetQueryObjectuiv _ptrc_glGetQueryObjectuiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetQueryiv)(GLenum target, GLenum pname, GLint * params);
		#define glGetQueryiv _ptrc_glGetQueryiv
		extern GLboolean (CODEGEN_FUNCPTR *_ptrc_glIsBuffer)(GLuint buffer);
		#define glIsBuffer _ptrc_glIsBuffer
		extern GLboolean (CODEGEN_FUNCPTR *_ptrc_glIsQuery)(GLuint id);
		#define glIsQuery _ptrc_glIsQuery
		extern void * (CODEGEN_FUNCPTR *_ptrc_glMapBuffer)(GLenum target, GLenum access);
		#define glMapBuffer _ptrc_glMapBuffer
		extern GLboolean (CODEGEN_FUNCPTR *_ptrc_glUnmapBuffer)(GLenum target);
		#define glUnmapBuffer _ptrc_glUnmapBuffer
		
		// Extension: 2.0
		extern void (CODEGEN_FUNCPTR *_ptrc_glAttachShader)(GLuint program, GLuint shader);
		#define glAttachShader _ptrc_glAttachShader
		extern void (CODEGEN_FUNCPTR *_ptrc_glBindAttribLocation)(GLuint program, GLuint index, const GLchar * name);
		#define glBindAttribLocation _ptrc_glBindAttribLocation
		extern void (CODEGEN_FUNCPTR *_ptrc_glBlendEquationSeparate)(GLenum modeRGB, GLenum modeAlpha);
		#define glBlendEquationSeparate _ptrc_glBlendEquationSeparate
		extern void (CODEGEN_FUNCPTR *_ptrc_glCompileShader)(GLuint shader);
		#define glCompileShader _ptrc_glCompileShader
		extern GLuint (CODEGEN_FUNCPTR *_ptrc_glCreateProgram)();
		#define glCreateProgram _ptrc_glCreateProgram
		extern GLuint (CODEGEN_FUNCPTR *_ptrc_glCreateShader)(GLenum type);
		#define glCreateShader _ptrc_glCreateShader
		extern void (CODEGEN_FUNCPTR *_ptrc_glDeleteProgram)(GLuint program);
		#define glDeleteProgram _ptrc_glDeleteProgram
		extern void (CODEGEN_FUNCPTR *_ptrc_glDeleteShader)(GLuint shader);
		#define glDeleteShader _ptrc_glDeleteShader
		extern void (CODEGEN_FUNCPTR *_ptrc_glDetachShader)(GLuint program, GLuint shader);
		#define glDetachShader _ptrc_glDetachShader
		extern void (CODEGEN_FUNCPTR *_ptrc_glDisableVertexAttribArray)(GLuint index);
		#define glDisableVertexAttribArray _ptrc_glDisableVertexAttribArray
		extern void (CODEGEN_FUNCPTR *_ptrc_glDrawBuffers)(GLsizei n, const GLenum * bufs);
		#define glDrawBuffers _ptrc_glDrawBuffers
		extern void (CODEGEN_FUNCPTR *_ptrc_glEnableVertexAttribArray)(GLuint index);
		#define glEnableVertexAttribArray _ptrc_glEnableVertexAttribArray
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetActiveAttrib)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
		#define glGetActiveAttrib _ptrc_glGetActiveAttrib
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetActiveUniform)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
		#define glGetActiveUniform _ptrc_glGetActiveUniform
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetAttachedShaders)(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders);
		#define glGetAttachedShaders _ptrc_glGetAttachedShaders
		extern GLint (CODEGEN_FUNCPTR *_ptrc_glGetAttribLocation)(GLuint program, const GLchar * name);
		#define glGetAttribLocation _ptrc_glGetAttribLocation
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetProgramInfoLog)(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
		#define glGetProgramInfoLog _ptrc_glGetProgramInfoLog
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetProgramiv)(GLuint program, GLenum pname, GLint * params);
		#define glGetProgramiv _ptrc_glGetProgramiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetShaderInfoLog)(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
		#define glGetShaderInfoLog _ptrc_glGetShaderInfoLog
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetShaderSource)(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source);
		#define glGetShaderSource _ptrc_glGetShaderSource
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetShaderiv)(GLuint shader, GLenum pname, GLint * params);
		#define glGetShaderiv _ptrc_glGetShaderiv
		extern GLint (CODEGEN_FUNCPTR *_ptrc_glGetUniformLocation)(GLuint program, const GLchar * name);
		#define glGetUniformLocation _ptrc_glGetUniformLocation
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetUniformfv)(GLuint program, GLint location, GLfloat * params);
		#define glGetUniformfv _ptrc_glGetUniformfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetUniformiv)(GLuint program, GLint location, GLint * params);
		#define glGetUniformiv _ptrc_glGetUniformiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetVertexAttribPointerv)(GLuint index, GLenum pname, GLvoid ** pointer);
		#define glGetVertexAttribPointerv _ptrc_glGetVertexAttribPointerv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetVertexAttribdv)(GLuint index, GLenum pname, GLdouble * params);
		#define glGetVertexAttribdv _ptrc_glGetVertexAttribdv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetVertexAttribfv)(GLuint index, GLenum pname, GLfloat * params);
		#define glGetVertexAttribfv _ptrc_glGetVertexAttribfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetVertexAttribiv)(GLuint index, GLenum pname, GLint * params);
		#define glGetVertexAttribiv _ptrc_glGetVertexAttribiv
		extern GLboolean (CODEGEN_FUNCPTR *_ptrc_glIsProgram)(GLuint program);
		#define glIsProgram _ptrc_glIsProgram
		extern GLboolean (CODEGEN_FUNCPTR *_ptrc_glIsShader)(GLuint shader);
		#define glIsShader _ptrc_glIsShader
		extern void (CODEGEN_FUNCPTR *_ptrc_glLinkProgram)(GLuint program);
		#define glLinkProgram _ptrc_glLinkProgram
		extern void (CODEGEN_FUNCPTR *_ptrc_glShaderSource)(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length);
		#define glShaderSource _ptrc_glShaderSource
		extern void (CODEGEN_FUNCPTR *_ptrc_glStencilFuncSeparate)(GLenum face, GLenum func, GLint ref, GLuint mask);
		#define glStencilFuncSeparate _ptrc_glStencilFuncSeparate
		extern void (CODEGEN_FUNCPTR *_ptrc_glStencilMaskSeparate)(GLenum face, GLuint mask);
		#define glStencilMaskSeparate _ptrc_glStencilMaskSeparate
		extern void (CODEGEN_FUNCPTR *_ptrc_glStencilOpSeparate)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
		#define glStencilOpSeparate _ptrc_glStencilOpSeparate
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform1f)(GLint location, GLfloat v0);
		#define glUniform1f _ptrc_glUniform1f
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform1fv)(GLint location, GLsizei count, const GLfloat * value);
		#define glUniform1fv _ptrc_glUniform1fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform1i)(GLint location, GLint v0);
		#define glUniform1i _ptrc_glUniform1i
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform1iv)(GLint location, GLsizei count, const GLint * value);
		#define glUniform1iv _ptrc_glUniform1iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform2f)(GLint location, GLfloat v0, GLfloat v1);
		#define glUniform2f _ptrc_glUniform2f
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform2fv)(GLint location, GLsizei count, const GLfloat * value);
		#define glUniform2fv _ptrc_glUniform2fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform2i)(GLint location, GLint v0, GLint v1);
		#define glUniform2i _ptrc_glUniform2i
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform2iv)(GLint location, GLsizei count, const GLint * value);
		#define glUniform2iv _ptrc_glUniform2iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform3f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
		#define glUniform3f _ptrc_glUniform3f
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform3fv)(GLint location, GLsizei count, const GLfloat * value);
		#define glUniform3fv _ptrc_glUniform3fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform3i)(GLint location, GLint v0, GLint v1, GLint v2);
		#define glUniform3i _ptrc_glUniform3i
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform3iv)(GLint location, GLsizei count, const GLint * value);
		#define glUniform3iv _ptrc_glUniform3iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform4f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
		#define glUniform4f _ptrc_glUniform4f
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform4fv)(GLint location, GLsizei count, const GLfloat * value);
		#define glUniform4fv _ptrc_glUniform4fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform4i)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
		#define glUniform4i _ptrc_glUniform4i
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform4iv)(GLint location, GLsizei count, const GLint * value);
		#define glUniform4iv _ptrc_glUniform4iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniformMatrix2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		#define glUniformMatrix2fv _ptrc_glUniformMatrix2fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniformMatrix3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		#define glUniformMatrix3fv _ptrc_glUniformMatrix3fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		#define glUniformMatrix4fv _ptrc_glUniformMatrix4fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUseProgram)(GLuint program);
		#define glUseProgram _ptrc_glUseProgram
		extern void (CODEGEN_FUNCPTR *_ptrc_glValidateProgram)(GLuint program);
		#define glValidateProgram _ptrc_glValidateProgram
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib1d)(GLuint index, GLdouble x);
		#define glVertexAttrib1d _ptrc_glVertexAttrib1d
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib1dv)(GLuint index, const GLdouble * v);
		#define glVertexAttrib1dv _ptrc_glVertexAttrib1dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib1f)(GLuint index, GLfloat x);
		#define glVertexAttrib1f _ptrc_glVertexAttrib1f
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib1fv)(GLuint index, const GLfloat * v);
		#define glVertexAttrib1fv _ptrc_glVertexAttrib1fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib1s)(GLuint index, GLshort x);
		#define glVertexAttrib1s _ptrc_glVertexAttrib1s
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib1sv)(GLuint index, const GLshort * v);
		#define glVertexAttrib1sv _ptrc_glVertexAttrib1sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib2d)(GLuint index, GLdouble x, GLdouble y);
		#define glVertexAttrib2d _ptrc_glVertexAttrib2d
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib2dv)(GLuint index, const GLdouble * v);
		#define glVertexAttrib2dv _ptrc_glVertexAttrib2dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib2f)(GLuint index, GLfloat x, GLfloat y);
		#define glVertexAttrib2f _ptrc_glVertexAttrib2f
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib2fv)(GLuint index, const GLfloat * v);
		#define glVertexAttrib2fv _ptrc_glVertexAttrib2fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib2s)(GLuint index, GLshort x, GLshort y);
		#define glVertexAttrib2s _ptrc_glVertexAttrib2s
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib2sv)(GLuint index, const GLshort * v);
		#define glVertexAttrib2sv _ptrc_glVertexAttrib2sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib3d)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
		#define glVertexAttrib3d _ptrc_glVertexAttrib3d
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib3dv)(GLuint index, const GLdouble * v);
		#define glVertexAttrib3dv _ptrc_glVertexAttrib3dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib3f)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
		#define glVertexAttrib3f _ptrc_glVertexAttrib3f
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib3fv)(GLuint index, const GLfloat * v);
		#define glVertexAttrib3fv _ptrc_glVertexAttrib3fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib3s)(GLuint index, GLshort x, GLshort y, GLshort z);
		#define glVertexAttrib3s _ptrc_glVertexAttrib3s
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib3sv)(GLuint index, const GLshort * v);
		#define glVertexAttrib3sv _ptrc_glVertexAttrib3sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib4Nbv)(GLuint index, const GLbyte * v);
		#define glVertexAttrib4Nbv _ptrc_glVertexAttrib4Nbv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib4Niv)(GLuint index, const GLint * v);
		#define glVertexAttrib4Niv _ptrc_glVertexAttrib4Niv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib4Nsv)(GLuint index, const GLshort * v);
		#define glVertexAttrib4Nsv _ptrc_glVertexAttrib4Nsv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib4Nub)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
		#define glVertexAttrib4Nub _ptrc_glVertexAttrib4Nub
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib4Nubv)(GLuint index, const GLubyte * v);
		#define glVertexAttrib4Nubv _ptrc_glVertexAttrib4Nubv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib4Nuiv)(GLuint index, const GLuint * v);
		#define glVertexAttrib4Nuiv _ptrc_glVertexAttrib4Nuiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib4Nusv)(GLuint index, const GLushort * v);
		#define glVertexAttrib4Nusv _ptrc_glVertexAttrib4Nusv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib4bv)(GLuint index, const GLbyte * v);
		#define glVertexAttrib4bv _ptrc_glVertexAttrib4bv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib4d)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
		#define glVertexAttrib4d _ptrc_glVertexAttrib4d
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib4dv)(GLuint index, const GLdouble * v);
		#define glVertexAttrib4dv _ptrc_glVertexAttrib4dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib4f)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
		#define glVertexAttrib4f _ptrc_glVertexAttrib4f
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib4fv)(GLuint index, const GLfloat * v);
		#define glVertexAttrib4fv _ptrc_glVertexAttrib4fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib4iv)(GLuint index, const GLint * v);
		#define glVertexAttrib4iv _ptrc_glVertexAttrib4iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib4s)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
		#define glVertexAttrib4s _ptrc_glVertexAttrib4s
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib4sv)(GLuint index, const GLshort * v);
		#define glVertexAttrib4sv _ptrc_glVertexAttrib4sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib4ubv)(GLuint index, const GLubyte * v);
		#define glVertexAttrib4ubv _ptrc_glVertexAttrib4ubv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib4uiv)(GLuint index, const GLuint * v);
		#define glVertexAttrib4uiv _ptrc_glVertexAttrib4uiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttrib4usv)(GLuint index, const GLushort * v);
		#define glVertexAttrib4usv _ptrc_glVertexAttrib4usv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer);
		#define glVertexAttribPointer _ptrc_glVertexAttribPointer
		
		// Extension: 2.1
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniformMatrix2x3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		#define glUniformMatrix2x3fv _ptrc_glUniformMatrix2x3fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniformMatrix2x4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		#define glUniformMatrix2x4fv _ptrc_glUniformMatrix2x4fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniformMatrix3x2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		#define glUniformMatrix3x2fv _ptrc_glUniformMatrix3x2fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniformMatrix3x4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		#define glUniformMatrix3x4fv _ptrc_glUniformMatrix3x4fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniformMatrix4x2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		#define glUniformMatrix4x2fv _ptrc_glUniformMatrix4x2fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniformMatrix4x3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		#define glUniformMatrix4x3fv _ptrc_glUniformMatrix4x3fv
		
		// Extension: 3.0
		extern void (CODEGEN_FUNCPTR *_ptrc_glBeginConditionalRender)(GLuint id, GLenum mode);
		#define glBeginConditionalRender _ptrc_glBeginConditionalRender
		extern void (CODEGEN_FUNCPTR *_ptrc_glBeginTransformFeedback)(GLenum primitiveMode);
		#define glBeginTransformFeedback _ptrc_glBeginTransformFeedback
		extern void (CODEGEN_FUNCPTR *_ptrc_glBindBufferBase)(GLenum target, GLuint index, GLuint buffer);
		#define glBindBufferBase _ptrc_glBindBufferBase
		extern void (CODEGEN_FUNCPTR *_ptrc_glBindBufferRange)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
		#define glBindBufferRange _ptrc_glBindBufferRange
		extern void (CODEGEN_FUNCPTR *_ptrc_glBindFragDataLocation)(GLuint program, GLuint color, const GLchar * name);
		#define glBindFragDataLocation _ptrc_glBindFragDataLocation
		extern void (CODEGEN_FUNCPTR *_ptrc_glBindFramebuffer)(GLenum target, GLuint framebuffer);
		#define glBindFramebuffer _ptrc_glBindFramebuffer
		extern void (CODEGEN_FUNCPTR *_ptrc_glBindRenderbuffer)(GLenum target, GLuint renderbuffer);
		#define glBindRenderbuffer _ptrc_glBindRenderbuffer
		extern void (CODEGEN_FUNCPTR *_ptrc_glBindVertexArray)(GLuint ren_array);
		#define glBindVertexArray _ptrc_glBindVertexArray
		extern void (CODEGEN_FUNCPTR *_ptrc_glBlitFramebuffer)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
		#define glBlitFramebuffer _ptrc_glBlitFramebuffer
		extern GLenum (CODEGEN_FUNCPTR *_ptrc_glCheckFramebufferStatus)(GLenum target);
		#define glCheckFramebufferStatus _ptrc_glCheckFramebufferStatus
		extern void (CODEGEN_FUNCPTR *_ptrc_glClampColor)(GLenum target, GLenum clamp);
		#define glClampColor _ptrc_glClampColor
		extern void (CODEGEN_FUNCPTR *_ptrc_glClearBufferfi)(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
		#define glClearBufferfi _ptrc_glClearBufferfi
		extern void (CODEGEN_FUNCPTR *_ptrc_glClearBufferfv)(GLenum buffer, GLint drawbuffer, const GLfloat * value);
		#define glClearBufferfv _ptrc_glClearBufferfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glClearBufferiv)(GLenum buffer, GLint drawbuffer, const GLint * value);
		#define glClearBufferiv _ptrc_glClearBufferiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glClearBufferuiv)(GLenum buffer, GLint drawbuffer, const GLuint * value);
		#define glClearBufferuiv _ptrc_glClearBufferuiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glColorMaski)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
		#define glColorMaski _ptrc_glColorMaski
		extern void (CODEGEN_FUNCPTR *_ptrc_glDeleteFramebuffers)(GLsizei n, const GLuint * framebuffers);
		#define glDeleteFramebuffers _ptrc_glDeleteFramebuffers
		extern void (CODEGEN_FUNCPTR *_ptrc_glDeleteRenderbuffers)(GLsizei n, const GLuint * renderbuffers);
		#define glDeleteRenderbuffers _ptrc_glDeleteRenderbuffers
		extern void (CODEGEN_FUNCPTR *_ptrc_glDeleteVertexArrays)(GLsizei n, const GLuint * arrays);
		#define glDeleteVertexArrays _ptrc_glDeleteVertexArrays
		extern void (CODEGEN_FUNCPTR *_ptrc_glDisablei)(GLenum target, GLuint index);
		#define glDisablei _ptrc_glDisablei
		extern void (CODEGEN_FUNCPTR *_ptrc_glEnablei)(GLenum target, GLuint index);
		#define glEnablei _ptrc_glEnablei
		extern void (CODEGEN_FUNCPTR *_ptrc_glEndConditionalRender)();
		#define glEndConditionalRender _ptrc_glEndConditionalRender
		extern void (CODEGEN_FUNCPTR *_ptrc_glEndTransformFeedback)();
		#define glEndTransformFeedback _ptrc_glEndTransformFeedback
		extern void (CODEGEN_FUNCPTR *_ptrc_glFlushMappedBufferRange)(GLenum target, GLintptr offset, GLsizeiptr length);
		#define glFlushMappedBufferRange _ptrc_glFlushMappedBufferRange
		extern void (CODEGEN_FUNCPTR *_ptrc_glFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
		#define glFramebufferRenderbuffer _ptrc_glFramebufferRenderbuffer
		extern void (CODEGEN_FUNCPTR *_ptrc_glFramebufferTexture1D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
		#define glFramebufferTexture1D _ptrc_glFramebufferTexture1D
		extern void (CODEGEN_FUNCPTR *_ptrc_glFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
		#define glFramebufferTexture2D _ptrc_glFramebufferTexture2D
		extern void (CODEGEN_FUNCPTR *_ptrc_glFramebufferTexture3D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
		#define glFramebufferTexture3D _ptrc_glFramebufferTexture3D
		extern void (CODEGEN_FUNCPTR *_ptrc_glFramebufferTextureLayer)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
		#define glFramebufferTextureLayer _ptrc_glFramebufferTextureLayer
		extern void (CODEGEN_FUNCPTR *_ptrc_glGenFramebuffers)(GLsizei n, GLuint * framebuffers);
		#define glGenFramebuffers _ptrc_glGenFramebuffers
		extern void (CODEGEN_FUNCPTR *_ptrc_glGenRenderbuffers)(GLsizei n, GLuint * renderbuffers);
		#define glGenRenderbuffers _ptrc_glGenRenderbuffers
		extern void (CODEGEN_FUNCPTR *_ptrc_glGenVertexArrays)(GLsizei n, GLuint * arrays);
		#define glGenVertexArrays _ptrc_glGenVertexArrays
		extern void (CODEGEN_FUNCPTR *_ptrc_glGenerateMipmap)(GLenum target);
		#define glGenerateMipmap _ptrc_glGenerateMipmap
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetBooleani_v)(GLenum target, GLuint index, GLboolean * data);
		#define glGetBooleani_v _ptrc_glGetBooleani_v
		extern GLint (CODEGEN_FUNCPTR *_ptrc_glGetFragDataLocation)(GLuint program, const GLchar * name);
		#define glGetFragDataLocation _ptrc_glGetFragDataLocation
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetFramebufferAttachmentParameteriv)(GLenum target, GLenum attachment, GLenum pname, GLint * params);
		#define glGetFramebufferAttachmentParameteriv _ptrc_glGetFramebufferAttachmentParameteriv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetIntegeri_v)(GLenum target, GLuint index, GLint * data);
		#define glGetIntegeri_v _ptrc_glGetIntegeri_v
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetRenderbufferParameteriv)(GLenum target, GLenum pname, GLint * params);
		#define glGetRenderbufferParameteriv _ptrc_glGetRenderbufferParameteriv
		extern const GLubyte * (CODEGEN_FUNCPTR *_ptrc_glGetStringi)(GLenum name, GLuint index);
		#define glGetStringi _ptrc_glGetStringi
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetTexParameterIiv)(GLenum target, GLenum pname, GLint * params);
		#define glGetTexParameterIiv _ptrc_glGetTexParameterIiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetTexParameterIuiv)(GLenum target, GLenum pname, GLuint * params);
		#define glGetTexParameterIuiv _ptrc_glGetTexParameterIuiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetTransformFeedbackVarying)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name);
		#define glGetTransformFeedbackVarying _ptrc_glGetTransformFeedbackVarying
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetUniformuiv)(GLuint program, GLint location, GLuint * params);
		#define glGetUniformuiv _ptrc_glGetUniformuiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetVertexAttribIiv)(GLuint index, GLenum pname, GLint * params);
		#define glGetVertexAttribIiv _ptrc_glGetVertexAttribIiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetVertexAttribIuiv)(GLuint index, GLenum pname, GLuint * params);
		#define glGetVertexAttribIuiv _ptrc_glGetVertexAttribIuiv
		extern GLboolean (CODEGEN_FUNCPTR *_ptrc_glIsEnabledi)(GLenum target, GLuint index);
		#define glIsEnabledi _ptrc_glIsEnabledi
		extern GLboolean (CODEGEN_FUNCPTR *_ptrc_glIsFramebuffer)(GLuint framebuffer);
		#define glIsFramebuffer _ptrc_glIsFramebuffer
		extern GLboolean (CODEGEN_FUNCPTR *_ptrc_glIsRenderbuffer)(GLuint renderbuffer);
		#define glIsRenderbuffer _ptrc_glIsRenderbuffer
		extern GLboolean (CODEGEN_FUNCPTR *_ptrc_glIsVertexArray)(GLuint ren_array);
		#define glIsVertexArray _ptrc_glIsVertexArray
		extern void * (CODEGEN_FUNCPTR *_ptrc_glMapBufferRange)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
		#define glMapBufferRange _ptrc_glMapBufferRange
		extern void (CODEGEN_FUNCPTR *_ptrc_glRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
		#define glRenderbufferStorage _ptrc_glRenderbufferStorage
		extern void (CODEGEN_FUNCPTR *_ptrc_glRenderbufferStorageMultisample)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
		#define glRenderbufferStorageMultisample _ptrc_glRenderbufferStorageMultisample
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexParameterIiv)(GLenum target, GLenum pname, const GLint * params);
		#define glTexParameterIiv _ptrc_glTexParameterIiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexParameterIuiv)(GLenum target, GLenum pname, const GLuint * params);
		#define glTexParameterIuiv _ptrc_glTexParameterIuiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glTransformFeedbackVaryings)(GLuint program, GLsizei count, const GLchar *const* varyings, GLenum bufferMode);
		#define glTransformFeedbackVaryings _ptrc_glTransformFeedbackVaryings
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform1ui)(GLint location, GLuint v0);
		#define glUniform1ui _ptrc_glUniform1ui
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform1uiv)(GLint location, GLsizei count, const GLuint * value);
		#define glUniform1uiv _ptrc_glUniform1uiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform2ui)(GLint location, GLuint v0, GLuint v1);
		#define glUniform2ui _ptrc_glUniform2ui
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform2uiv)(GLint location, GLsizei count, const GLuint * value);
		#define glUniform2uiv _ptrc_glUniform2uiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform3ui)(GLint location, GLuint v0, GLuint v1, GLuint v2);
		#define glUniform3ui _ptrc_glUniform3ui
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform3uiv)(GLint location, GLsizei count, const GLuint * value);
		#define glUniform3uiv _ptrc_glUniform3uiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform4ui)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
		#define glUniform4ui _ptrc_glUniform4ui
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform4uiv)(GLint location, GLsizei count, const GLuint * value);
		#define glUniform4uiv _ptrc_glUniform4uiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribI1i)(GLuint index, GLint x);
		#define glVertexAttribI1i _ptrc_glVertexAttribI1i
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribI1iv)(GLuint index, const GLint * v);
		#define glVertexAttribI1iv _ptrc_glVertexAttribI1iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribI1ui)(GLuint index, GLuint x);
		#define glVertexAttribI1ui _ptrc_glVertexAttribI1ui
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribI1uiv)(GLuint index, const GLuint * v);
		#define glVertexAttribI1uiv _ptrc_glVertexAttribI1uiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribI2i)(GLuint index, GLint x, GLint y);
		#define glVertexAttribI2i _ptrc_glVertexAttribI2i
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribI2iv)(GLuint index, const GLint * v);
		#define glVertexAttribI2iv _ptrc_glVertexAttribI2iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribI2ui)(GLuint index, GLuint x, GLuint y);
		#define glVertexAttribI2ui _ptrc_glVertexAttribI2ui
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribI2uiv)(GLuint index, const GLuint * v);
		#define glVertexAttribI2uiv _ptrc_glVertexAttribI2uiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribI3i)(GLuint index, GLint x, GLint y, GLint z);
		#define glVertexAttribI3i _ptrc_glVertexAttribI3i
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribI3iv)(GLuint index, const GLint * v);
		#define glVertexAttribI3iv _ptrc_glVertexAttribI3iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribI3ui)(GLuint index, GLuint x, GLuint y, GLuint z);
		#define glVertexAttribI3ui _ptrc_glVertexAttribI3ui
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribI3uiv)(GLuint index, const GLuint * v);
		#define glVertexAttribI3uiv _ptrc_glVertexAttribI3uiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribI4bv)(GLuint index, const GLbyte * v);
		#define glVertexAttribI4bv _ptrc_glVertexAttribI4bv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribI4i)(GLuint index, GLint x, GLint y, GLint z, GLint w);
		#define glVertexAttribI4i _ptrc_glVertexAttribI4i
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribI4iv)(GLuint index, const GLint * v);
		#define glVertexAttribI4iv _ptrc_glVertexAttribI4iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribI4sv)(GLuint index, const GLshort * v);
		#define glVertexAttribI4sv _ptrc_glVertexAttribI4sv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribI4ubv)(GLuint index, const GLubyte * v);
		#define glVertexAttribI4ubv _ptrc_glVertexAttribI4ubv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribI4ui)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
		#define glVertexAttribI4ui _ptrc_glVertexAttribI4ui
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribI4uiv)(GLuint index, const GLuint * v);
		#define glVertexAttribI4uiv _ptrc_glVertexAttribI4uiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribI4usv)(GLuint index, const GLushort * v);
		#define glVertexAttribI4usv _ptrc_glVertexAttribI4usv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribIPointer)(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer);
		#define glVertexAttribIPointer _ptrc_glVertexAttribIPointer
		
		// Extension: 3.1
		extern void (CODEGEN_FUNCPTR *_ptrc_glCopyBufferSubData)(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
		#define glCopyBufferSubData _ptrc_glCopyBufferSubData
		extern void (CODEGEN_FUNCPTR *_ptrc_glDrawArraysInstanced)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
		#define glDrawArraysInstanced _ptrc_glDrawArraysInstanced
		extern void (CODEGEN_FUNCPTR *_ptrc_glDrawElementsInstanced)(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLsizei instancecount);
		#define glDrawElementsInstanced _ptrc_glDrawElementsInstanced
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetActiveUniformBlockName)(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName);
		#define glGetActiveUniformBlockName _ptrc_glGetActiveUniformBlockName
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetActiveUniformBlockiv)(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params);
		#define glGetActiveUniformBlockiv _ptrc_glGetActiveUniformBlockiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetActiveUniformName)(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName);
		#define glGetActiveUniformName _ptrc_glGetActiveUniformName
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetActiveUniformsiv)(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params);
		#define glGetActiveUniformsiv _ptrc_glGetActiveUniformsiv
		extern GLuint (CODEGEN_FUNCPTR *_ptrc_glGetUniformBlockIndex)(GLuint program, const GLchar * uniformBlockName);
		#define glGetUniformBlockIndex _ptrc_glGetUniformBlockIndex
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetUniformIndices)(GLuint program, GLsizei uniformCount, const GLchar *const* uniformNames, GLuint * uniformIndices);
		#define glGetUniformIndices _ptrc_glGetUniformIndices
		extern void (CODEGEN_FUNCPTR *_ptrc_glPrimitiveRestartIndex)(GLuint index);
		#define glPrimitiveRestartIndex _ptrc_glPrimitiveRestartIndex
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexBuffer)(GLenum target, GLenum internalformat, GLuint buffer);
		#define glTexBuffer _ptrc_glTexBuffer
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniformBlockBinding)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
		#define glUniformBlockBinding _ptrc_glUniformBlockBinding
		
		// Extension: 3.2
		extern GLenum (CODEGEN_FUNCPTR *_ptrc_glClientWaitSync)(GLsync sync, GLbitfield flags, GLuint64 timeout);
		#define glClientWaitSync _ptrc_glClientWaitSync
		extern void (CODEGEN_FUNCPTR *_ptrc_glDeleteSync)(GLsync sync);
		#define glDeleteSync _ptrc_glDeleteSync
		extern void (CODEGEN_FUNCPTR *_ptrc_glDrawElementsBaseVertex)(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLint basevertex);
		#define glDrawElementsBaseVertex _ptrc_glDrawElementsBaseVertex
		extern void (CODEGEN_FUNCPTR *_ptrc_glDrawElementsInstancedBaseVertex)(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLsizei instancecount, GLint basevertex);
		#define glDrawElementsInstancedBaseVertex _ptrc_glDrawElementsInstancedBaseVertex
		extern void (CODEGEN_FUNCPTR *_ptrc_glDrawRangeElementsBaseVertex)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices, GLint basevertex);
		#define glDrawRangeElementsBaseVertex _ptrc_glDrawRangeElementsBaseVertex
		extern GLsync (CODEGEN_FUNCPTR *_ptrc_glFenceSync)(GLenum condition, GLbitfield flags);
		#define glFenceSync _ptrc_glFenceSync
		extern void (CODEGEN_FUNCPTR *_ptrc_glFramebufferTexture)(GLenum target, GLenum attachment, GLuint texture, GLint level);
		#define glFramebufferTexture _ptrc_glFramebufferTexture
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetBufferParameteri64v)(GLenum target, GLenum pname, GLint64 * params);
		#define glGetBufferParameteri64v _ptrc_glGetBufferParameteri64v
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetInteger64i_v)(GLenum target, GLuint index, GLint64 * data);
		#define glGetInteger64i_v _ptrc_glGetInteger64i_v
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetInteger64v)(GLenum pname, GLint64 * params);
		#define glGetInteger64v _ptrc_glGetInteger64v
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetMultisamplefv)(GLenum pname, GLuint index, GLfloat * val);
		#define glGetMultisamplefv _ptrc_glGetMultisamplefv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetSynciv)(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei * length, GLint * values);
		#define glGetSynciv _ptrc_glGetSynciv
		extern GLboolean (CODEGEN_FUNCPTR *_ptrc_glIsSync)(GLsync sync);
		#define glIsSync _ptrc_glIsSync
		extern void (CODEGEN_FUNCPTR *_ptrc_glMultiDrawElementsBaseVertex)(GLenum mode, const GLsizei * count, GLenum type, const GLvoid *const* indices, GLsizei drawcount, const GLint * basevertex);
		#define glMultiDrawElementsBaseVertex _ptrc_glMultiDrawElementsBaseVertex
		extern void (CODEGEN_FUNCPTR *_ptrc_glProvokingVertex)(GLenum mode);
		#define glProvokingVertex _ptrc_glProvokingVertex
		extern void (CODEGEN_FUNCPTR *_ptrc_glSampleMaski)(GLuint index, GLbitfield mask);
		#define glSampleMaski _ptrc_glSampleMaski
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexImage2DMultisample)(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
		#define glTexImage2DMultisample _ptrc_glTexImage2DMultisample
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexImage3DMultisample)(GLenum target, GLsizei samples, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
		#define glTexImage3DMultisample _ptrc_glTexImage3DMultisample
		extern void (CODEGEN_FUNCPTR *_ptrc_glWaitSync)(GLsync sync, GLbitfield flags, GLuint64 timeout);
		#define glWaitSync _ptrc_glWaitSync
		
		// Extension: 3.3
		extern void (CODEGEN_FUNCPTR *_ptrc_glBindFragDataLocationIndexed)(GLuint program, GLuint colorNumber, GLuint index, const GLchar * name);
		#define glBindFragDataLocationIndexed _ptrc_glBindFragDataLocationIndexed
		extern void (CODEGEN_FUNCPTR *_ptrc_glBindSampler)(GLuint unit, GLuint sampler);
		#define glBindSampler _ptrc_glBindSampler
		extern void (CODEGEN_FUNCPTR *_ptrc_glDeleteSamplers)(GLsizei count, const GLuint * samplers);
		#define glDeleteSamplers _ptrc_glDeleteSamplers
		extern void (CODEGEN_FUNCPTR *_ptrc_glGenSamplers)(GLsizei count, GLuint * samplers);
		#define glGenSamplers _ptrc_glGenSamplers
		extern GLint (CODEGEN_FUNCPTR *_ptrc_glGetFragDataIndex)(GLuint program, const GLchar * name);
		#define glGetFragDataIndex _ptrc_glGetFragDataIndex
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetQueryObjecti64v)(GLuint id, GLenum pname, GLint64 * params);
		#define glGetQueryObjecti64v _ptrc_glGetQueryObjecti64v
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetQueryObjectui64v)(GLuint id, GLenum pname, GLuint64 * params);
		#define glGetQueryObjectui64v _ptrc_glGetQueryObjectui64v
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetSamplerParameterIiv)(GLuint sampler, GLenum pname, GLint * params);
		#define glGetSamplerParameterIiv _ptrc_glGetSamplerParameterIiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetSamplerParameterIuiv)(GLuint sampler, GLenum pname, GLuint * params);
		#define glGetSamplerParameterIuiv _ptrc_glGetSamplerParameterIuiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetSamplerParameterfv)(GLuint sampler, GLenum pname, GLfloat * params);
		#define glGetSamplerParameterfv _ptrc_glGetSamplerParameterfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetSamplerParameteriv)(GLuint sampler, GLenum pname, GLint * params);
		#define glGetSamplerParameteriv _ptrc_glGetSamplerParameteriv
		extern GLboolean (CODEGEN_FUNCPTR *_ptrc_glIsSampler)(GLuint sampler);
		#define glIsSampler _ptrc_glIsSampler
		extern void (CODEGEN_FUNCPTR *_ptrc_glQueryCounter)(GLuint id, GLenum target);
		#define glQueryCounter _ptrc_glQueryCounter
		extern void (CODEGEN_FUNCPTR *_ptrc_glSamplerParameterIiv)(GLuint sampler, GLenum pname, const GLint * param);
		#define glSamplerParameterIiv _ptrc_glSamplerParameterIiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glSamplerParameterIuiv)(GLuint sampler, GLenum pname, const GLuint * param);
		#define glSamplerParameterIuiv _ptrc_glSamplerParameterIuiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glSamplerParameterf)(GLuint sampler, GLenum pname, GLfloat param);
		#define glSamplerParameterf _ptrc_glSamplerParameterf
		extern void (CODEGEN_FUNCPTR *_ptrc_glSamplerParameterfv)(GLuint sampler, GLenum pname, const GLfloat * param);
		#define glSamplerParameterfv _ptrc_glSamplerParameterfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glSamplerParameteri)(GLuint sampler, GLenum pname, GLint param);
		#define glSamplerParameteri _ptrc_glSamplerParameteri
		extern void (CODEGEN_FUNCPTR *_ptrc_glSamplerParameteriv)(GLuint sampler, GLenum pname, const GLint * param);
		#define glSamplerParameteriv _ptrc_glSamplerParameteriv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribDivisor)(GLuint index, GLuint divisor);
		#define glVertexAttribDivisor _ptrc_glVertexAttribDivisor
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribP1ui)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
		#define glVertexAttribP1ui _ptrc_glVertexAttribP1ui
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribP1uiv)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
		#define glVertexAttribP1uiv _ptrc_glVertexAttribP1uiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribP2ui)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
		#define glVertexAttribP2ui _ptrc_glVertexAttribP2ui
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribP2uiv)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
		#define glVertexAttribP2uiv _ptrc_glVertexAttribP2uiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribP3ui)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
		#define glVertexAttribP3ui _ptrc_glVertexAttribP3ui
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribP3uiv)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
		#define glVertexAttribP3uiv _ptrc_glVertexAttribP3uiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribP4ui)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
		#define glVertexAttribP4ui _ptrc_glVertexAttribP4ui
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribP4uiv)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
		#define glVertexAttribP4uiv _ptrc_glVertexAttribP4uiv
		
		// Extension: 4.0
		extern void (CODEGEN_FUNCPTR *_ptrc_glBeginQueryIndexed)(GLenum target, GLuint index, GLuint id);
		#define glBeginQueryIndexed _ptrc_glBeginQueryIndexed
		extern void (CODEGEN_FUNCPTR *_ptrc_glBindTransformFeedback)(GLenum target, GLuint id);
		#define glBindTransformFeedback _ptrc_glBindTransformFeedback
		extern void (CODEGEN_FUNCPTR *_ptrc_glBlendEquationSeparatei)(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
		#define glBlendEquationSeparatei _ptrc_glBlendEquationSeparatei
		extern void (CODEGEN_FUNCPTR *_ptrc_glBlendEquationi)(GLuint buf, GLenum mode);
		#define glBlendEquationi _ptrc_glBlendEquationi
		extern void (CODEGEN_FUNCPTR *_ptrc_glBlendFuncSeparatei)(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
		#define glBlendFuncSeparatei _ptrc_glBlendFuncSeparatei
		extern void (CODEGEN_FUNCPTR *_ptrc_glBlendFunci)(GLuint buf, GLenum src, GLenum dst);
		#define glBlendFunci _ptrc_glBlendFunci
		extern void (CODEGEN_FUNCPTR *_ptrc_glDeleteTransformFeedbacks)(GLsizei n, const GLuint * ids);
		#define glDeleteTransformFeedbacks _ptrc_glDeleteTransformFeedbacks
		extern void (CODEGEN_FUNCPTR *_ptrc_glDrawArraysIndirect)(GLenum mode, const GLvoid * indirect);
		#define glDrawArraysIndirect _ptrc_glDrawArraysIndirect
		extern void (CODEGEN_FUNCPTR *_ptrc_glDrawElementsIndirect)(GLenum mode, GLenum type, const GLvoid * indirect);
		#define glDrawElementsIndirect _ptrc_glDrawElementsIndirect
		extern void (CODEGEN_FUNCPTR *_ptrc_glDrawTransformFeedback)(GLenum mode, GLuint id);
		#define glDrawTransformFeedback _ptrc_glDrawTransformFeedback
		extern void (CODEGEN_FUNCPTR *_ptrc_glDrawTransformFeedbackStream)(GLenum mode, GLuint id, GLuint stream);
		#define glDrawTransformFeedbackStream _ptrc_glDrawTransformFeedbackStream
		extern void (CODEGEN_FUNCPTR *_ptrc_glEndQueryIndexed)(GLenum target, GLuint index);
		#define glEndQueryIndexed _ptrc_glEndQueryIndexed
		extern void (CODEGEN_FUNCPTR *_ptrc_glGenTransformFeedbacks)(GLsizei n, GLuint * ids);
		#define glGenTransformFeedbacks _ptrc_glGenTransformFeedbacks
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetActiveSubroutineName)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name);
		#define glGetActiveSubroutineName _ptrc_glGetActiveSubroutineName
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetActiveSubroutineUniformName)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name);
		#define glGetActiveSubroutineUniformName _ptrc_glGetActiveSubroutineUniformName
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetActiveSubroutineUniformiv)(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values);
		#define glGetActiveSubroutineUniformiv _ptrc_glGetActiveSubroutineUniformiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetProgramStageiv)(GLuint program, GLenum shadertype, GLenum pname, GLint * values);
		#define glGetProgramStageiv _ptrc_glGetProgramStageiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetQueryIndexediv)(GLenum target, GLuint index, GLenum pname, GLint * params);
		#define glGetQueryIndexediv _ptrc_glGetQueryIndexediv
		extern GLuint (CODEGEN_FUNCPTR *_ptrc_glGetSubroutineIndex)(GLuint program, GLenum shadertype, const GLchar * name);
		#define glGetSubroutineIndex _ptrc_glGetSubroutineIndex
		extern GLint (CODEGEN_FUNCPTR *_ptrc_glGetSubroutineUniformLocation)(GLuint program, GLenum shadertype, const GLchar * name);
		#define glGetSubroutineUniformLocation _ptrc_glGetSubroutineUniformLocation
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetUniformSubroutineuiv)(GLenum shadertype, GLint location, GLuint * params);
		#define glGetUniformSubroutineuiv _ptrc_glGetUniformSubroutineuiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetUniformdv)(GLuint program, GLint location, GLdouble * params);
		#define glGetUniformdv _ptrc_glGetUniformdv
		extern GLboolean (CODEGEN_FUNCPTR *_ptrc_glIsTransformFeedback)(GLuint id);
		#define glIsTransformFeedback _ptrc_glIsTransformFeedback
		extern void (CODEGEN_FUNCPTR *_ptrc_glMinSampleShading)(GLfloat value);
		#define glMinSampleShading _ptrc_glMinSampleShading
		extern void (CODEGEN_FUNCPTR *_ptrc_glPatchParameterfv)(GLenum pname, const GLfloat * values);
		#define glPatchParameterfv _ptrc_glPatchParameterfv
		extern void (CODEGEN_FUNCPTR *_ptrc_glPatchParameteri)(GLenum pname, GLint value);
		#define glPatchParameteri _ptrc_glPatchParameteri
		extern void (CODEGEN_FUNCPTR *_ptrc_glPauseTransformFeedback)();
		#define glPauseTransformFeedback _ptrc_glPauseTransformFeedback
		extern void (CODEGEN_FUNCPTR *_ptrc_glResumeTransformFeedback)();
		#define glResumeTransformFeedback _ptrc_glResumeTransformFeedback
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform1d)(GLint location, GLdouble x);
		#define glUniform1d _ptrc_glUniform1d
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform1dv)(GLint location, GLsizei count, const GLdouble * value);
		#define glUniform1dv _ptrc_glUniform1dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform2d)(GLint location, GLdouble x, GLdouble y);
		#define glUniform2d _ptrc_glUniform2d
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform2dv)(GLint location, GLsizei count, const GLdouble * value);
		#define glUniform2dv _ptrc_glUniform2dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform3d)(GLint location, GLdouble x, GLdouble y, GLdouble z);
		#define glUniform3d _ptrc_glUniform3d
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform3dv)(GLint location, GLsizei count, const GLdouble * value);
		#define glUniform3dv _ptrc_glUniform3dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform4d)(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
		#define glUniform4d _ptrc_glUniform4d
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniform4dv)(GLint location, GLsizei count, const GLdouble * value);
		#define glUniform4dv _ptrc_glUniform4dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniformMatrix2dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		#define glUniformMatrix2dv _ptrc_glUniformMatrix2dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniformMatrix2x3dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		#define glUniformMatrix2x3dv _ptrc_glUniformMatrix2x3dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniformMatrix2x4dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		#define glUniformMatrix2x4dv _ptrc_glUniformMatrix2x4dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniformMatrix3dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		#define glUniformMatrix3dv _ptrc_glUniformMatrix3dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniformMatrix3x2dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		#define glUniformMatrix3x2dv _ptrc_glUniformMatrix3x2dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniformMatrix3x4dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		#define glUniformMatrix3x4dv _ptrc_glUniformMatrix3x4dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniformMatrix4dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		#define glUniformMatrix4dv _ptrc_glUniformMatrix4dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniformMatrix4x2dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		#define glUniformMatrix4x2dv _ptrc_glUniformMatrix4x2dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniformMatrix4x3dv)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		#define glUniformMatrix4x3dv _ptrc_glUniformMatrix4x3dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glUniformSubroutinesuiv)(GLenum shadertype, GLsizei count, const GLuint * indices);
		#define glUniformSubroutinesuiv _ptrc_glUniformSubroutinesuiv
		
		// Extension: 4.1
		extern void (CODEGEN_FUNCPTR *_ptrc_glActiveShaderProgram)(GLuint pipeline, GLuint program);
		#define glActiveShaderProgram _ptrc_glActiveShaderProgram
		extern void (CODEGEN_FUNCPTR *_ptrc_glBindProgramPipeline)(GLuint pipeline);
		#define glBindProgramPipeline _ptrc_glBindProgramPipeline
		extern void (CODEGEN_FUNCPTR *_ptrc_glClearDepthf)(GLfloat d);
		#define glClearDepthf _ptrc_glClearDepthf
		extern GLuint (CODEGEN_FUNCPTR *_ptrc_glCreateShaderProgramv)(GLenum type, GLsizei count, const GLchar *const* strings);
		#define glCreateShaderProgramv _ptrc_glCreateShaderProgramv
		extern void (CODEGEN_FUNCPTR *_ptrc_glDeleteProgramPipelines)(GLsizei n, const GLuint * pipelines);
		#define glDeleteProgramPipelines _ptrc_glDeleteProgramPipelines
		extern void (CODEGEN_FUNCPTR *_ptrc_glDepthRangeArrayv)(GLuint first, GLsizei count, const GLdouble * v);
		#define glDepthRangeArrayv _ptrc_glDepthRangeArrayv
		extern void (CODEGEN_FUNCPTR *_ptrc_glDepthRangeIndexed)(GLuint index, GLdouble n, GLdouble f);
		#define glDepthRangeIndexed _ptrc_glDepthRangeIndexed
		extern void (CODEGEN_FUNCPTR *_ptrc_glDepthRangef)(GLfloat n, GLfloat f);
		#define glDepthRangef _ptrc_glDepthRangef
		extern void (CODEGEN_FUNCPTR *_ptrc_glGenProgramPipelines)(GLsizei n, GLuint * pipelines);
		#define glGenProgramPipelines _ptrc_glGenProgramPipelines
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetDoublei_v)(GLenum target, GLuint index, GLdouble * data);
		#define glGetDoublei_v _ptrc_glGetDoublei_v
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetFloati_v)(GLenum target, GLuint index, GLfloat * data);
		#define glGetFloati_v _ptrc_glGetFloati_v
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetProgramBinary)(GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, GLvoid * binary);
		#define glGetProgramBinary _ptrc_glGetProgramBinary
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetProgramPipelineInfoLog)(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
		#define glGetProgramPipelineInfoLog _ptrc_glGetProgramPipelineInfoLog
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetProgramPipelineiv)(GLuint pipeline, GLenum pname, GLint * params);
		#define glGetProgramPipelineiv _ptrc_glGetProgramPipelineiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetShaderPrecisionFormat)(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision);
		#define glGetShaderPrecisionFormat _ptrc_glGetShaderPrecisionFormat
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetVertexAttribLdv)(GLuint index, GLenum pname, GLdouble * params);
		#define glGetVertexAttribLdv _ptrc_glGetVertexAttribLdv
		extern GLboolean (CODEGEN_FUNCPTR *_ptrc_glIsProgramPipeline)(GLuint pipeline);
		#define glIsProgramPipeline _ptrc_glIsProgramPipeline
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramBinary)(GLuint program, GLenum binaryFormat, const GLvoid * binary, GLsizei length);
		#define glProgramBinary _ptrc_glProgramBinary
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramParameteri)(GLuint program, GLenum pname, GLint value);
		#define glProgramParameteri _ptrc_glProgramParameteri
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform1d)(GLuint program, GLint location, GLdouble v0);
		#define glProgramUniform1d _ptrc_glProgramUniform1d
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform1dv)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
		#define glProgramUniform1dv _ptrc_glProgramUniform1dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform1f)(GLuint program, GLint location, GLfloat v0);
		#define glProgramUniform1f _ptrc_glProgramUniform1f
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform1fv)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
		#define glProgramUniform1fv _ptrc_glProgramUniform1fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform1i)(GLuint program, GLint location, GLint v0);
		#define glProgramUniform1i _ptrc_glProgramUniform1i
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform1iv)(GLuint program, GLint location, GLsizei count, const GLint * value);
		#define glProgramUniform1iv _ptrc_glProgramUniform1iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform1ui)(GLuint program, GLint location, GLuint v0);
		#define glProgramUniform1ui _ptrc_glProgramUniform1ui
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform1uiv)(GLuint program, GLint location, GLsizei count, const GLuint * value);
		#define glProgramUniform1uiv _ptrc_glProgramUniform1uiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform2d)(GLuint program, GLint location, GLdouble v0, GLdouble v1);
		#define glProgramUniform2d _ptrc_glProgramUniform2d
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform2dv)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
		#define glProgramUniform2dv _ptrc_glProgramUniform2dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform2f)(GLuint program, GLint location, GLfloat v0, GLfloat v1);
		#define glProgramUniform2f _ptrc_glProgramUniform2f
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform2fv)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
		#define glProgramUniform2fv _ptrc_glProgramUniform2fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform2i)(GLuint program, GLint location, GLint v0, GLint v1);
		#define glProgramUniform2i _ptrc_glProgramUniform2i
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform2iv)(GLuint program, GLint location, GLsizei count, const GLint * value);
		#define glProgramUniform2iv _ptrc_glProgramUniform2iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform2ui)(GLuint program, GLint location, GLuint v0, GLuint v1);
		#define glProgramUniform2ui _ptrc_glProgramUniform2ui
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform2uiv)(GLuint program, GLint location, GLsizei count, const GLuint * value);
		#define glProgramUniform2uiv _ptrc_glProgramUniform2uiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform3d)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
		#define glProgramUniform3d _ptrc_glProgramUniform3d
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform3dv)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
		#define glProgramUniform3dv _ptrc_glProgramUniform3dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform3f)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
		#define glProgramUniform3f _ptrc_glProgramUniform3f
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform3fv)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
		#define glProgramUniform3fv _ptrc_glProgramUniform3fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform3i)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
		#define glProgramUniform3i _ptrc_glProgramUniform3i
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform3iv)(GLuint program, GLint location, GLsizei count, const GLint * value);
		#define glProgramUniform3iv _ptrc_glProgramUniform3iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform3ui)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
		#define glProgramUniform3ui _ptrc_glProgramUniform3ui
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform3uiv)(GLuint program, GLint location, GLsizei count, const GLuint * value);
		#define glProgramUniform3uiv _ptrc_glProgramUniform3uiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform4d)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
		#define glProgramUniform4d _ptrc_glProgramUniform4d
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform4dv)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
		#define glProgramUniform4dv _ptrc_glProgramUniform4dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform4f)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
		#define glProgramUniform4f _ptrc_glProgramUniform4f
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform4fv)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
		#define glProgramUniform4fv _ptrc_glProgramUniform4fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform4i)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
		#define glProgramUniform4i _ptrc_glProgramUniform4i
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform4iv)(GLuint program, GLint location, GLsizei count, const GLint * value);
		#define glProgramUniform4iv _ptrc_glProgramUniform4iv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform4ui)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
		#define glProgramUniform4ui _ptrc_glProgramUniform4ui
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniform4uiv)(GLuint program, GLint location, GLsizei count, const GLuint * value);
		#define glProgramUniform4uiv _ptrc_glProgramUniform4uiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniformMatrix2dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		#define glProgramUniformMatrix2dv _ptrc_glProgramUniformMatrix2dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniformMatrix2fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		#define glProgramUniformMatrix2fv _ptrc_glProgramUniformMatrix2fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniformMatrix2x3dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		#define glProgramUniformMatrix2x3dv _ptrc_glProgramUniformMatrix2x3dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniformMatrix2x3fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		#define glProgramUniformMatrix2x3fv _ptrc_glProgramUniformMatrix2x3fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniformMatrix2x4dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		#define glProgramUniformMatrix2x4dv _ptrc_glProgramUniformMatrix2x4dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniformMatrix2x4fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		#define glProgramUniformMatrix2x4fv _ptrc_glProgramUniformMatrix2x4fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniformMatrix3dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		#define glProgramUniformMatrix3dv _ptrc_glProgramUniformMatrix3dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniformMatrix3fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		#define glProgramUniformMatrix3fv _ptrc_glProgramUniformMatrix3fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniformMatrix3x2dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		#define glProgramUniformMatrix3x2dv _ptrc_glProgramUniformMatrix3x2dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniformMatrix3x2fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		#define glProgramUniformMatrix3x2fv _ptrc_glProgramUniformMatrix3x2fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniformMatrix3x4dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		#define glProgramUniformMatrix3x4dv _ptrc_glProgramUniformMatrix3x4dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniformMatrix3x4fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		#define glProgramUniformMatrix3x4fv _ptrc_glProgramUniformMatrix3x4fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniformMatrix4dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		#define glProgramUniformMatrix4dv _ptrc_glProgramUniformMatrix4dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniformMatrix4fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		#define glProgramUniformMatrix4fv _ptrc_glProgramUniformMatrix4fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniformMatrix4x2dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		#define glProgramUniformMatrix4x2dv _ptrc_glProgramUniformMatrix4x2dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniformMatrix4x2fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		#define glProgramUniformMatrix4x2fv _ptrc_glProgramUniformMatrix4x2fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniformMatrix4x3dv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
		#define glProgramUniformMatrix4x3dv _ptrc_glProgramUniformMatrix4x3dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glProgramUniformMatrix4x3fv)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
		#define glProgramUniformMatrix4x3fv _ptrc_glProgramUniformMatrix4x3fv
		extern void (CODEGEN_FUNCPTR *_ptrc_glReleaseShaderCompiler)();
		#define glReleaseShaderCompiler _ptrc_glReleaseShaderCompiler
		extern void (CODEGEN_FUNCPTR *_ptrc_glScissorArrayv)(GLuint first, GLsizei count, const GLint * v);
		#define glScissorArrayv _ptrc_glScissorArrayv
		extern void (CODEGEN_FUNCPTR *_ptrc_glScissorIndexed)(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
		#define glScissorIndexed _ptrc_glScissorIndexed
		extern void (CODEGEN_FUNCPTR *_ptrc_glScissorIndexedv)(GLuint index, const GLint * v);
		#define glScissorIndexedv _ptrc_glScissorIndexedv
		extern void (CODEGEN_FUNCPTR *_ptrc_glShaderBinary)(GLsizei count, const GLuint * shaders, GLenum binaryformat, const GLvoid * binary, GLsizei length);
		#define glShaderBinary _ptrc_glShaderBinary
		extern void (CODEGEN_FUNCPTR *_ptrc_glUseProgramStages)(GLuint pipeline, GLbitfield stages, GLuint program);
		#define glUseProgramStages _ptrc_glUseProgramStages
		extern void (CODEGEN_FUNCPTR *_ptrc_glValidateProgramPipeline)(GLuint pipeline);
		#define glValidateProgramPipeline _ptrc_glValidateProgramPipeline
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribL1d)(GLuint index, GLdouble x);
		#define glVertexAttribL1d _ptrc_glVertexAttribL1d
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribL1dv)(GLuint index, const GLdouble * v);
		#define glVertexAttribL1dv _ptrc_glVertexAttribL1dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribL2d)(GLuint index, GLdouble x, GLdouble y);
		#define glVertexAttribL2d _ptrc_glVertexAttribL2d
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribL2dv)(GLuint index, const GLdouble * v);
		#define glVertexAttribL2dv _ptrc_glVertexAttribL2dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribL3d)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
		#define glVertexAttribL3d _ptrc_glVertexAttribL3d
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribL3dv)(GLuint index, const GLdouble * v);
		#define glVertexAttribL3dv _ptrc_glVertexAttribL3dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribL4d)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
		#define glVertexAttribL4d _ptrc_glVertexAttribL4d
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribL4dv)(GLuint index, const GLdouble * v);
		#define glVertexAttribL4dv _ptrc_glVertexAttribL4dv
		extern void (CODEGEN_FUNCPTR *_ptrc_glVertexAttribLPointer)(GLuint index, GLint size, GLenum type, GLsizei stride, const GLvoid * pointer);
		#define glVertexAttribLPointer _ptrc_glVertexAttribLPointer
		extern void (CODEGEN_FUNCPTR *_ptrc_glViewportArrayv)(GLuint first, GLsizei count, const GLfloat * v);
		#define glViewportArrayv _ptrc_glViewportArrayv
		extern void (CODEGEN_FUNCPTR *_ptrc_glViewportIndexedf)(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
		#define glViewportIndexedf _ptrc_glViewportIndexedf
		extern void (CODEGEN_FUNCPTR *_ptrc_glViewportIndexedfv)(GLuint index, const GLfloat * v);
		#define glViewportIndexedfv _ptrc_glViewportIndexedfv
		
		// Extension: 4.2
		extern void (CODEGEN_FUNCPTR *_ptrc_glBindImageTexture)(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
		#define glBindImageTexture _ptrc_glBindImageTexture
		extern void (CODEGEN_FUNCPTR *_ptrc_glDrawArraysInstancedBaseInstance)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance);
		#define glDrawArraysInstancedBaseInstance _ptrc_glDrawArraysInstancedBaseInstance
		extern void (CODEGEN_FUNCPTR *_ptrc_glDrawElementsInstancedBaseInstance)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLuint baseinstance);
		#define glDrawElementsInstancedBaseInstance _ptrc_glDrawElementsInstancedBaseInstance
		extern void (CODEGEN_FUNCPTR *_ptrc_glDrawElementsInstancedBaseVertexBaseInstance)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
		#define glDrawElementsInstancedBaseVertexBaseInstance _ptrc_glDrawElementsInstancedBaseVertexBaseInstance
		extern void (CODEGEN_FUNCPTR *_ptrc_glDrawTransformFeedbackInstanced)(GLenum mode, GLuint id, GLsizei instancecount);
		#define glDrawTransformFeedbackInstanced _ptrc_glDrawTransformFeedbackInstanced
		extern void (CODEGEN_FUNCPTR *_ptrc_glDrawTransformFeedbackStreamInstanced)(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount);
		#define glDrawTransformFeedbackStreamInstanced _ptrc_glDrawTransformFeedbackStreamInstanced
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetActiveAtomicCounterBufferiv)(GLuint program, GLuint bufferIndex, GLenum pname, GLint * params);
		#define glGetActiveAtomicCounterBufferiv _ptrc_glGetActiveAtomicCounterBufferiv
		extern void (CODEGEN_FUNCPTR *_ptrc_glGetInternalformati64v)(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 * params);
		#define glGetInternalformati64v _ptrc_glGetInternalformati64v
		extern void (CODEGEN_FUNCPTR *_ptrc_glMemoryBarrier)(GLbitfield barriers);
		#define glMemoryBarrier _ptrc_glMemoryBarrier
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexStorage1D)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
		#define glTexStorage1D _ptrc_glTexStorage1D
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexStorage2D)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
		#define glTexStorage2D _ptrc_glTexStorage2D
		extern void (CODEGEN_FUNCPTR *_ptrc_glTexStorage3D)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
		#define glTexStorage3D _ptrc_glTexStorage3D
		
		void ogl_CheckExtensions();
		
		#ifdef __cplusplus
		}
		#endif /*__cplusplus*/
		
		#endif //OPENGL_NOLOAD_STYLE_H
