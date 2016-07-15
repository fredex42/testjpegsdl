/*
 * text.h
 *
 *  Created on: 15 Jul 2016
 *      Author: andy
 */

#ifndef TEXT_H_
#define TEXT_H_

#include <iostream>
#include <exception>
#include <sstream>
using namespace std;

#define DEFAULT_FONT "/usr/share/fonts/truetype/freefont/FreeSans.ttf"
SDL_Surface *draw_text(const char *text,const char *fontname,
		int max_size,int min_size,int img_width);

class FontNotFound : public std::exception
{
public:
	FontNotFound(const char *name="") : fontname(name) {};
	virtual const char* what() const throw()
	{
		stringstream s;
		s << "Font file '" << fontname << "' could not be opened";
		return s.str().c_str();
	}

private:
	const char *fontname;
};

class TTFError : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return (const char *)TTF_GetError();
	}
};

enum justify {
	J_TOP=1,
	J_MIDDLE,
	J_BOTTOM
};

class TextSurface
{
public:
	TextSurface();
	TextSurface(string& text);
	TextSurface(string& text,string& fontfile);

	virtual ~TextSurface();

	enum justify getJustify();
	void setJustify(enum justify j);
	int getImageHeight() const;
	void setImageHeight(int imageHeight);
	int getImageWidth() const;
	void setImageWidth(int imageWidth);
	int getMarginBottom() const;
	void setMarginBottom(int marginBottom);
	int getMarginLeft() const;
	void setMarginLeft(int marginLeft);
	int getMarginRight() const;
	void setMarginRight(int marginRight);
	int getMarginTop() const;
	void setMarginTop(int marginTop);
	int getMaxPointSize() const;
	void setMaxPointSize(int maxPointSize);
	int getMinPointSize() const;
	void setMinPointSize(int minPointSize);
	const SDL_Surface* getSurface() const;
	enum justify getJustify() const;

private:
	SDL_Surface *surface;
	string text;
	int max_point_size;
	int min_point_size;
	int image_height;
	int image_width;
	int margin_left;
	int margin_right;
	int margin_top;
	int margin_bottom;

	enum justify h_justify;
	enum justify v_justify;
};
#endif /* TEXT_H_ */
