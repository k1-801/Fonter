#ifndef WIDGETGLYPH_HPP
#define WIDGETGLYPH_HPP

#include <QOpenGLWidget>
#include <QVector>

#include "Glyph.hpp"

class WidgetGlyph : public QOpenGLWidget
{
    private:
        Glyph* glyph;
        int _w, _h;
        void ortho();

    public:
        WidgetGlyph(QWidget*);
        void setGlyph(Glyph*);
        void mousePressEvent(QMouseEvent*);
        void initializeGL();
        void     resizeGL(int, int);
        void      paintGL();
        Glyph* getGlyph();
};

#endif // WIDGETGLYPH_HPP
