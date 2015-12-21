#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

// C
#include <stdint.h>
// Qt
#include <QListWidgetItem>
#include <QMainWindow>
#include <QVector>

#include "Glyph.hpp"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    private:
        Ui::MainWindow *ui;
        QVector<Glyph> glyphs;

        uint32_t gw;
        uint32_t gh;

        void _readFrom(QString);
        void _saveTo(QString);

        QString fitInteger(QString);

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
        void error(QString);
        void resizeGlyphs(uint32_t, uint32_t);

    private slots:
        void on_pushButton_add_clicked();
        void on_pushButton_open_clicked();
        void on_pushButton_save_clicked();

        void on_lineEdit_symbol_editingFinished();
        void on_lineEdit_width_editingFinished();
        void on_lineEdit_height_editingFinished();
        void on_listWidget_itemClicked(QListWidgetItem *item);
};

#endif // MAINWINDOW_HPP
