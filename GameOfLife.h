#ifndef __GAME_H_
#define __GAME_H_

struct Tray
{
    int height;
    int width;
    int *mat;
    int size;
    SDL_Surface *image;
};

void draw(struct Tray *cur);

struct Tray *init_Tray(int height, int width, int size);

int is_alive(struct Tray *cur, int i, int j);

int alive(struct Tray *cur, int i, int j);

void update(struct Tray *cur);

void printblack(struct Tray *cur, int i, int j);

void printwhite(struct Tray *cur, int i, int j);

#endif
