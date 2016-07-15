/*
 * text.cpp
 *
 *  Created on: 15 Jul 2016
 *      Author: andy
 */

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "text.h"

SDL_Surface *draw_text(const char *text,const char *fontname,
		int max_size,int min_size,int img_width)
{
	if(fontname==NULL) fontname = DEFAULT_FONT;
	TTF_Font *font = NULL;
	SDL_Color color = {0xFF,0xFF,0xFF};
	int target_w,target_h;

	for(int font_size=max_size;font_size>=min_size;--font_size){
		font = TTF_OpenFont(fontname,font_size);
		if(!font){
			throw FontNotFound(fontname);
		}
		TTF_SizeText(font, text, &target_w, &target_h);
		if(target_w<img_width){
			cout << "Final text size is "<< font_size << " for pixel width of " << target_w << endl;
			break;
		}
		TTF_CloseFont(font);
		font = NULL;
	}

	if(font==NULL) return NULL;
	SDL_Surface *surface = TTF_RenderText_Blended(font,text,color);
	if(surface==NULL) throw TTFError();

	return surface;
}

enum justify TextSurface::getJustify() const {
	return h_justify;
}

void TextSurface::setJustify(enum justify j) {
	h_justify = j;
}

int TextSurface::getImageHeight() const {
	return image_height;
}

void TextSurface::setImageHeight(int imageHeight) {
	image_height = imageHeight;
}

int TextSurface::getImageWidth() const {
	return image_width;
}

void TextSurface::setImageWidth(int imageWidth) {
	image_width = imageWidth;
}

int TextSurface::getMarginBottom() const {
	return margin_bottom;
}

void TextSurface::setMarginBottom(int marginBottom) {
	margin_bottom = marginBottom;
}

int TextSurface::getMarginLeft() const {
	return margin_left;
}

void TextSurface::setMarginLeft(int marginLeft) {
	margin_left = marginLeft;
}

int TextSurface::getMarginRight() const {
	return margin_right;
}

void TextSurface::setMarginRight(int marginRight) {
	margin_right = marginRight;
}

int TextSurface::getMarginTop() const {
	return margin_top;
}

void TextSurface::setMarginTop(int marginTop) {
	margin_top = marginTop;
}

int TextSurface::getMaxPointSize() const {
	return max_point_size;
}

void TextSurface::setMaxPointSize(int maxPointSize) {
	max_point_size = maxPointSize;
}

int TextSurface::getMinPointSize() const {
	return min_point_size;
}

void TextSurface::setMinPointSize(int minPointSize) {
	min_point_size = minPointSize;
}

const SDL_Surface* TextSurface::getSurface() const {
	return (const SDL_Surface *)surface;
}

enum justify TextSurface::getJustify() {
	return v_justify;
}

