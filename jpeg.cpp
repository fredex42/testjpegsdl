/*
 * jpeg.cpp
 *
 *  Created on: 15 Jul 2016
 *      Author: andy
 */

#include <stdio.h>
#include <jpeglib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_surface.h>

#define READ_LINE_SIZE 1
#define WRITE_LINE_SIZE 1

void write_jpeg_file(char *filename, SDL_Surface *surface)
{
	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	FILE *fp;
	Uint32 rmask, gmask, bmask, amask;
	JSAMPROW row_pointer[WRITE_LINE_SIZE];
	int row_stride;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    fp = fopen(filename,"wb");
    jpeg_stdio_dest(&cinfo,fp);
    cinfo.image_width = surface->w;
    cinfo.image_height = surface->h;
    cinfo.input_components = surface->pitch/surface->w;
    cinfo.in_color_space = JCS_RGB;

    printf("Writing jpeg image %dx%d, with %d channels\n",cinfo.image_height,cinfo.image_width,cinfo.input_components);

    jpeg_set_defaults(&cinfo);

    jpeg_start_compress(&cinfo, FALSE);

    row_stride = cinfo.image_width * 3;

    SDL_LockSurface(surface);
    unsigned char *buf=(unsigned char *)surface->pixels;
    while(cinfo.next_scanline < cinfo.image_height){
    	row_pointer[0] = & buf[cinfo.next_scanline * row_stride];
    	jpeg_write_scanlines(&cinfo,row_pointer,WRITE_LINE_SIZE);
    }

    SDL_UnlockSurface(surface);
    jpeg_finish_compress(&cinfo);
    fclose(fp);
}

SDL_Surface *load_jpeg_file(char *filename)
{
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	SDL_Surface *surface;
	FILE *fp;
	Uint32 rmask, gmask, bmask, amask;
	long pixindex=0;
	JSAMPARRAY *buffer;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

	fp=fopen(filename,"rb");
	if(fp==NULL){
		fprintf(stderr,"Unable to open %s.\n",filename);
		return NULL;
	}

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo,fp);
	jpeg_read_header(&cinfo,TRUE);
	jpeg_start_decompress(&cinfo);

	printf("Reading jpeg image %dx%d, with %d channels",cinfo.output_width,
			cinfo.output_height,cinfo.output_components);
	surface = SDL_CreateRGBSurface(0,cinfo.output_width,cinfo.output_height,
			cinfo.output_components*8,rmask,gmask,bmask,amask);

	if(surface==NULL){
		fprintf(stderr,"Unable to create surface\n");
		return NULL;
	}

	//buffer = (JSAMPARRAY *)malloc(READ_LINE_SIZE*cinfo.output_width*cinfo.output_components*sizeof(JSAMPROW));

	SDL_LockSurface(surface);
	unsigned char *readptr = (unsigned char *)surface->pixels;
	int row_stride = cinfo.image_width * cinfo.output_components;

	while(cinfo.output_scanline < cinfo.output_height){
		//jpeg_read_scanlines(&cinfo,&buffer,READ_LINE_SIZE);
		//memcpy(surface->pixels+pixindex,&buffer,READ_LINE_SIZE*cinfo.output_width*cinfo.output_components);
		//pixindex+=READ_LINE_SIZE*cinfo.output_width*cinfo.output_components;
		jpeg_read_scanlines(&cinfo,&readptr,READ_LINE_SIZE);
		readptr += row_stride;
	}
	SDL_UnlockSurface(surface);
	jpeg_finish_decompress(&cinfo);
	fclose(fp);


	return surface;
}
