#include "WidgetPreview.hpp"

// Qt
#include <QDebug>
// GL
#include <GL/glu.h>

WidgetPreview::WidgetPreview(QWidget* parent) : QOpenGLWidget(parent)
{
    _g = NULL;
    _for = QColor(192, 192, 192);
    _back = QColor(0, 0, 0);
}

void WidgetPreview::ortho()
{
    glDisable( GL_DEPTH_TEST );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, _w, _h, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void WidgetPreview::init(QVector<Glyph>* g)
{
    _g = g;
}

void WidgetPreview::initializeGL()
{
    _w = width();
    _h = height();
}

void WidgetPreview::resizeGL(int w, int h)
{
    _w = w;
    _h = h;
}

void WidgetPreview::paintGL()
{
    ortho();
    int i, j, k, l, cx = 4, cy = 4, gw, gh;
    uint32_t scan;
    glClearColor(_back.redF(), _back.greenF(), _back.blueF(), 0);
    glClear(GL_COLOR_BUFFER_BIT);
    if(_g && !_g->empty())
    {
        gw = _g->at(0).width();
        gh = _g->at(0).height();

        glBegin(GL_POINTS);
        glColor3f(_for.redF(), _for.greenF(), _for.blueF());
        for(i = 0; i < _text.length(); ++i)
        {
            scan = _text[i].unicode();
            if(scan == '\n')
            {
                cx = 4;
                cy += gh;
            }
            else
            {
                for(j = 0; j < _g->size(); ++j)
                {
                    if(_g->at(j).code() == scan)
                    {
                        cx += _g->at(j).offset;
                        if(cx < 0)
                            cx = 0;
                        for(k = 0; k < gh; ++k)
                        {
                            for(l = 0; l < gw; ++l)
                            {
                                if(_g->at(j).check(l, k))
                                {
                                    glVertex2i(cx + l, cy + k);
                                }
                            }
                        }
                        cx += gw;
                        if(_w - gw - 8 < cx)
                        {
                            cx = 4;
                            cy += gh;
                        }
                        break;
                    }
                }
            }
        }
        glEnd();
    }
}

void WidgetPreview::changeText(QString text)
{
    _text = text;
    update();
}

QColor WidgetPreview::getBackground()
{
    return _back;
}

QColor WidgetPreview::getForeground()
{
    return _for;
}

void WidgetPreview::setBackground(QColor n)
{
    if(n.isValid())
    {
        _back = n;
    }
}

void WidgetPreview::setForeground(QColor n)
{
    if(n.isValid())
    {
        _for = n;
    }
}
