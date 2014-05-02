TEMPLATE = subdirs

SUBDIRS += \
    src \
    demo

demo.depends = src
