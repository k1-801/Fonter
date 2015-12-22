#include "Glyph.hpp"

#include <QDebug>

Glyph::Glyph(){}

Glyph::Glyph(uint32_t c, uint32_t w, uint32_t h)
{
    _code = c;
    offset = 0;
    resize(w, h);
}

bool& Glyph::pixel(uint32_t x, uint32_t y)
{
    return _bitmap[x][y];
}

bool Glyph::check(uint32_t x, uint32_t y) const
{
    return _bitmap[x][y];
}

void Glyph::resize(uint32_t w, uint32_t h)
{
    _bitmap.resize(w);
    for(uint32_t i = 0; i < w; ++i)
    {
        _bitmap[i].resize(h);
    }
}

uint32_t Glyph::code() const
{
    return _code;
}

uint32_t Glyph::width() const
{
    return _bitmap.size();
}

uint32_t Glyph::height() const
{
    if(_bitmap.isEmpty())
        return 0;
    return _bitmap[0].size();
}

QTextStream& operator >> (QTextStream& str, Glyph& g)
{
    QIODevice* dev = str.device();
    dev->read((char*)(&g._code), 4);
    dev->read((char*)(&g.offset), 4);
    uint32_t i, j;
    char raw = 0;
    for(i = 0; i < g.height(); ++i)
    {
        for(j = 0; j < g.width(); ++j)
        {
            if(!(j % 8)) dev->read(&raw, 1);
            g._bitmap[j][i] = (raw >> (j % 8)) & 1;
        }
    }
    return str;
}

QTextStream& operator << (QTextStream& str, const Glyph& g)
{
    QIODevice* dev = str.device();
    dev->write((char*)(&g._code), 4);
    dev->write((char*)(&g.offset), 4);
    uint32_t i, j;
    char raw = 0;
    for(i = 0; i < g.height(); ++i)
    {
        for(j = 0; j < g.width(); ++j)
        {
            raw |= g._bitmap[j][i] << (j % 8);
            if((j % 8) == 7)
            {
                dev->write(&raw, 1); raw = 0;
            }
        }
        if(j % 8)
            dev->write(&raw, 1);
    }
    return str;
}

bool operator < (const Glyph& a, const Glyph& b)
{
    return a._code < b._code;
}
