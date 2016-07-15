/*
 * main.cpp
 *
 *  Created on: 15 Jul 2016
 *      Author: andy
 */

#include <stdio.h>
#include <jpeglib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>

#include "jpeg.h"
#include "text.h"

int main(int argc,char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	puts("hello there");

	SDL_Surface *img_surface=load_jpeg_file("/usr/lib/eclipse/features/org.eclipse.help_1.4.1.dist-8v7nFQYFCmSPZXHoT2597H/eclipse_update_120.jpg");

	SDL_Surface *text_surface=draw_text("hello there",NULL,72,2,img_surface->w);

	SDL_Window *w = SDL_CreateWindow("Image test",SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,img_surface->w,img_surface->h,0);


	SDL_Surface *window_surface = SDL_GetWindowSurface(w);
	SDL_BlitSurface(img_surface,NULL,window_surface,NULL);
	SDL_BlitSurface(text_surface,NULL,window_surface,NULL);

	SDL_UpdateWindowSurface(w);
	SDL_Delay(3000);

	TTF_Quit();
	SDL_Quit();
}

