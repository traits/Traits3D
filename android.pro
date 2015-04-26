TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = \
  src \
#  examples/qt/mesh
  examples/qt/simpleplot
# examples/qt/quickexample

# mesh.depends = src
 simpleplot.depends = src
# quickexample.depends = src
