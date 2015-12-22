#include "WidgetGlyph.hpp"

// C++
#include <algorithm>
// Qt
#include <QDebug>
#include <QMouseEvent>
// GLU
#include <GL/glu.h>

WidgetGlyph::WidgetGlyph(QWidget* parent) : QOpenGLWidget(parent)
{
    glyph = NULL;
}

void WidgetGlyph::ortho()
{
    glDisable( GL_DEPTH_TEST );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, _w, _h, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void WidgetGlyph::mousePressEvent(QMouseEvent *event)
{
    if(glyph)
    {
        int w = glyph->width();
        int h = glyph->height();
        int k = std::min(_w / w, _h / h);
        int startx = (_w - k * w) / 2;
        int starty = (_h - k * h) / 2;

        int x = event->x() - startx;
        int y = event->y() - starty;
        if(x > 0 && y > 0)
        {
            x /= k;
            y /= k;
            if(x < w && y < h)
            {
                glyph->pixel(x, y) = !glyph->pixel(x, y);
            }
        }
    }
    event->accept();
    update();
}

void WidgetGlyph::setGlyph(Glyph* g)
{
    glyph = g;
    update();
}

void WidgetGlyph::initializeGL()
{
    _w = width();
    _h = height();
}

void WidgetGlyph::resizeGL(int w, int h)
{
    _w = w;
    _h = h;
}

void WidgetGlyph::paintGL()
{
    ortho();
    if(glyph)
    {
        int w = glyph->width();
        int h = glyph->height();
        int k = std::min(_w / w, _h / h);
        int startx = (_w - k * w) / 2;
        int starty = (_h - k * h) / 2;
        int i, j;

        // Draw font pixels
        glBegin(GL_QUADS);
        glColor3ub(192, 192, 192);
        for(i = 0; i < h; ++i)
        {
            for(j = 0; j < w; ++j)
            {
                if(glyph->pixel(j, i))
                {
                    glVertex2i(startx + (j    ) * k, starty + (i    ) * k);
                    glVertex2i(startx + (j + 1) * k, starty + (i    ) * k);
                    glVertex2i(startx + (j + 1) * k, starty + (i + 1) * k);
                    glVertex2i(startx + (j    ) * k, starty + (i + 1) * k);
                }
            }
        }
        glEnd();
        // Draw grid
        glBegin(GL_LINES);
        glColor3ub(127, 127, 127);
        for(i = 0; i < w + 1; ++i)
        {
            glVertex2i(startx + i * k,      starty);
            glVertex2i(startx + i * k, _h - starty);
        }
        for(i = 0; i < h + 1; ++i)
        {
            glVertex2i(     startx, starty + i * k);
            glVertex2i(_w - startx, starty + i * k);
        }
        glEnd();
    }
}

Glyph* WidgetGlyph::getGlyph()
{
    return glyph;
}
