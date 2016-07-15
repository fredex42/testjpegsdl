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

void TextSurface::basic_init() {
	surface = NULL;
	text = string("");
	fontfile = string(DEFAULT_FONT);
	max_point_size=72;
	min_point_size=2;
	image_height=-1;
	image_width=-1;
	margin_left=0;
	margin_right=0;
	margin_top=0;
	margin_bottom=0;

	h_justify = J_MIDDLE;
	v_justify = J_BOTTOM;
}

TextSurface::TextSurface() {
	basic_init();
}

TextSurface::TextSurface(string& text) {
	basic_init();
	this->text = text;
}

TextSurface::TextSurface(string& text, string& fontfile) {
	basic_init();
	this->text = string(text);
	this->fontfile = string(fontfile);
}

TextSurface::~TextSurface() {
	if(surface) SDL_FreeSurface(surface);
}

void TextSurface::render() {
	TTF_Font *font = NULL;
	SDL_Color color = {0xFF,0xFF,0xFF};
	int target_w,target_h;

	for(int font_size=max_point_size;font_size>=min_point_size;--font_size){
		//cout << "Testing font size of " << font_size << endl;
		font = TTF_OpenFont(fontfile.c_str(),font_size);
		if(!font){
			throw FontNotFound(fontfile.c_str());
		}
		TTF_SizeText(font, text.c_str(), &target_w, &target_h);
		if(target_w<image_width){
			cout << "Final text size is "<< font_size << " for pixel width of " << target_w << endl;
			break;
		}
		TTF_CloseFont(font);
		font = NULL;
	}

	if(font==NULL){
		throw GeneralError("Could not find an appropriate font size");
	}

	surface = TTF_RenderText_Blended(font,text.c_str(),color);
	TTF_CloseFont(font);
	if(surface==NULL) throw TTFError();
}

void TextSurface::blitToSurface(SDL_Surface *target)
{
	SDL_Rect dest_blit_rect;
	if(!surface) throw GeneralError("you must render before calling bitToSurface");

	switch(h_justify){
	case J_TOP:
		dest_blit_rect.x = 0;
		break;
	case J_MIDDLE:
		dest_blit_rect.x = target->w/2.0 - surface->w/2.0;
		break;
	case J_BOTTOM:
		dest_blit_rect.x = target->w - surface->w;
		break;
	}

	switch(v_justify){
	case J_TOP:
		dest_blit_rect.y = 0;
		break;
	case J_MIDDLE:
		dest_blit_rect.y = target->h/2.0 - surface->h/2.0;
		break;
	case J_BOTTOM:
		dest_blit_rect.y = target->h - surface->h;
		break;
	}

	dest_blit_rect.w = surface->w;
	dest_blit_rect.h = surface->h;

	SDL_BlitSurface(surface,NULL,target,&dest_blit_rect);
}

enum justify TextSurface::getJustify() const {
	return h_justify;
}

void TextSurface::setHJustify(enum justify j) {
	h_justify = j;
}

void TextSurface::setVJustify(enum justify j) {
	v_justify = j;
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

enum justify TextSurface::getJustify() {
	return v_justify;
}

