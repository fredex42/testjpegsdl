/*
 * jpeg.h
 *
 *  Created on: 15 Jul 2016
 *      Author: andy
 */

#ifndef JPEG_H_
#define JPEG_H_

SDL_Surface *load_jpeg_file(char *filename);
void write_jpeg_file(char *filename, SDL_Surface *surface);

#endif /* JPEG_H_ */
