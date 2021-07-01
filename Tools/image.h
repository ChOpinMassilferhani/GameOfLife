#ifndef BINARY_H_
#define BINARY_H_

# include <err.h>
# include <math.h>
# include "pixel_operations.h"


void init_sdl();

SDL_Surface *load_image(char *path);

SDL_Surface *display_image(SDL_Surface *img);

void wait_for_keypressed();

#endif