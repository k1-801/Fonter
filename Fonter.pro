#-------------------------------------------------
#
# Project created by QtCreator 2015-12-20T14:55:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS     += -lGLU

TARGET   = Fonter
TEMPLATE = app


SOURCES  += main.cpp \
            Glyph.cpp \
            MainWindow.cpp \
            WidgetGlyph.cpp \
            WidgetPreview.cpp

HEADERS  += Glyph.hpp \
            MainWindow.hpp \
            WidgetGlyph.hpp \
            WidgetPreview.hpp

FORMS    += MainWindow.ui
