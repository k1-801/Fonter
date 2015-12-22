#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gw = 8;
    gh = 16;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::error(QString text)
{
    qDebug() << "Error: " << text;
    exit(EXIT_FAILURE);
}

void MainWindow::_saveTo(QString name)
{
    QFile f(name);
    if(!f.open(QFile::WriteOnly))
        error(tr("Failed to open file %1").arg(name));
    uint32_t header[3];
    header[0] = glyphs.size();
    header[1] = gw;
    header[2] = gh;
    f.write((char*)(header), 12);

    std::sort(glyphs.begin(), glyphs.end());

    QTextStream str(&f);
    int i;
    for(i = 0; i < glyphs.size(); ++i)
    {
        str << glyphs[i];
    }
}

void MainWindow::_readFrom(QString name)
{
    int i;
    uint32_t header[3]; // Number of glyphs, glyph width and height, glyph symbol code, temporary reading variable
    glyphs.clear();
    ui->listWidget->clear();
    QFile f(name);
    if(!f.open(QFile::ReadOnly))
        error(tr("Failed to open file %1").arg(name));
    if(f.read((char*)(header), 12) != 12)
        error(tr("Failed to read font header"));

    glyphs.resize(header[0]);
    gw = header[1];
    gh = header[2];

    QTextStream str(&f);

    for(i = 0; i < glyphs.size(); ++i) // i - current glyph
    {
        glyphs[i].resize(gw, gh);
        str >> glyphs[i];

        QString symbol;
        QTextStream strcode(&symbol);
        strcode << glyphs[i].code();
        ui->listWidget->addItem(symbol);
    }
}

QString MainWindow::fitInteger(QString result)
{
    QTextStream str(&result);
    uint32_t code;
    str >> code;
    result.clear();
    str << code;
    return result;
}

void MainWindow::resizeGlyphs(uint32_t w, uint32_t h)
{
    int i;
    for(i = 0; i < glyphs.size(); ++i)
    {
        glyphs[i].resize(w, h);
    }
    ui->widgetGlyph->update();
}

void MainWindow::on_pushButton_add_clicked()
{
    QString fit = ui->lineEdit_symbol->text();
    QTextStream str(&fit);
    uint32_t code;
    str >> code;
    fit.clear();
    str << code;
    ui->lineEdit_symbol->setText(fit);

    bool f = false;
    int i;
    for(i = 0; i < glyphs.size(); ++i)
        if(glyphs[i].code() == code)
            f = true;
    if(!f)
    {
        glyphs.push_back(Glyph(code, gw, gh));
        ui->listWidget->addItem(fit);
    }
}

void MainWindow::on_pushButton_open_clicked()
{
    QString name = QFileDialog::getOpenFileName(NULL, tr("Open font"), "", tr("Binary font file(*.bfn)"));
    if(!name.isEmpty())
    {
        ui->widgetGlyph->setGlyph(0);
        if(!name.endsWith(".bfn"))
            name += ".bfn";
        _readFrom(name);
    }
}

void MainWindow::on_pushButton_save_clicked()
{
    QString name = QFileDialog::getSaveFileName(NULL, tr("Save font"), "", tr("Binary font file (*.bfn)"));
    if(!name.isEmpty())
    {
        ui->widgetGlyph->setGlyph(0);
        if(!name.endsWith(".bfn"))
            name += ".bfn";
        _saveTo(name);
        _readFrom(name);
    }
}

// Fit integers

void MainWindow::on_lineEdit_symbol_editingFinished()
{
    QString fit = fitInteger(ui->lineEdit_symbol->text());
    ui->lineEdit_symbol->setText(fit);
    ui->widgetGlyph->update();
}

void MainWindow::on_lineEdit_width_editingFinished()
{
    QString fit = ui->lineEdit_width->text();
    QTextStream str(&fit);
    str >> gw;
    if(gw < 2)
        gw = 2;
    fit.clear();
    str << gw;
    ui->lineEdit_width->setText(fit);

    resizeGlyphs(gw, gh);
}

void MainWindow::on_lineEdit_height_editingFinished()
{
    QString fit = ui->lineEdit_height->text();
    QTextStream str(&fit);
    str >> gh;
    if(gh < 2)
        gh = 2;
    fit.clear();
    str << gh;
    ui->lineEdit_height->setText(fit);

    resizeGlyphs(gw, gh);
}

void MainWindow::on_lineEdit_offset_editingFinished()
{
    QString fit = ui->lineEdit_height->text();
    QTextStream str(&fit);
    int32_t off;
    str >> off;
    fit.clear();
    str << off;
    ui->lineEdit_height->setText(fit);

    ui->widgetGlyph->getGlyph()->offset = off;
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    int i;
    uint32_t code;
    QString text = item->text();
    QTextStream str(&text);
    str >> code;

    for(i = 0; i < glyphs.size(); ++i)
    {
        if(glyphs[i].code() == code)
        {
            ui->widgetGlyph->setGlyph(&glyphs[i]);
            break;
        }
    }
    ui->widgetGlyph->update();
}
