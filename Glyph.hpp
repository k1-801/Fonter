#ifndef GLYPH_HPP
#define GLYPH_HPP

// C
#include <stdint.h>
// Qt
#include <QTextStream>
#include <QVector>

class Glyph
{
    private:
        uint32_t _code;
        QVector<QVector<uint8_t> > _bitmap;

    public:
        int32_t offset;
        Glyph();
        Glyph(uint32_t, uint32_t, uint32_t);
        void resize(uint32_t, uint32_t);
        uint8_t& pixel(uint32_t, uint32_t);
        bool  check(uint32_t, uint32_t) const;
        uint32_t code() const;
        uint32_t width() const;
        uint32_t height() const;

        friend QTextStream& operator >> (QTextStream&, Glyph&);
        friend QTextStream& operator << (QTextStream&, const Glyph&);
        friend bool operator < (const Glyph&, const Glyph&);
};

#endif // GLYPH_HPP
