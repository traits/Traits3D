TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = \
  src \
  examples/qt/simpleplot \
  examples/qt/quickexample

simpleplot.depends = src
quickexample.depends = src
