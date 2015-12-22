#ifndef WIDGETPREVIEW_HPP
#define WIDGETPREVIEW_HPP

#include <QOpenGLWidget>
#include <QString>
#include <QVector>

#include "Glyph.hpp"

class WidgetPreview : public QOpenGLWidget
{
    private:
        QVector<Glyph>* _g;
        QColor _for;
        QColor _back;
        QString _text;
        int _w, _h;
        void ortho();

    public:
        WidgetPreview(QWidget*);
        void initializeGL();
        void     resizeGL(int, int);
        void      paintGL();
        void changeText(QString);
        void init(QVector<Glyph>*);

        QColor getBackground();
        QColor getForeground();
        void setBackground(QColor);
        void setForeground(QColor);
};

#endif // WIDGETPREVIEW_HPP
