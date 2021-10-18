#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
	unsigned char r, g, b, a;

	Color() : r(0), g(0), b(0), a(1)
	{
	};

	Color(unsigned char _r, unsigned char _g, unsigned char _b) : r(_r), g(_g), b(_b), a(255)
	{
	};

	Color(float _r, float _g, float _b, float _a) : r((unsigned char)(_r * 255)), g((unsigned char)(_g * 255)), b((unsigned char)(_b * 255)), a((unsigned char)(_a * 255))
	{
	};

	~Color()
	{
	};
};

#endif