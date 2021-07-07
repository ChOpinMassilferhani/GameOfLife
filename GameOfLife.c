#include <stdio.h>
#include <unistd.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Tools/pixel_operations.h"
#include "Tools/image.h"
#include "GameOfLife.h"

void printblack(struct Tray *cur, int i, int j)
{
    int x = i * cur->size;
    int y = j * cur->size;
    for (int k = 0; k < cur->size; k++)
    {
        for (int w = 0; w < cur->size; w++)
        {
            Uint32 pixel = SDL_MapRGB(cur->image->format, 0, 0, 0);
            put_pixel(cur->image, x + k, y + w, pixel);
        }
    }
}
//test
void print_hori(struct Tray *cur, int i)
{
    int lenght = cur->height*cur->size;
    for (int w = 0; w < lenght; w++)
    {
        Uint32 pixel = SDL_MapRGB(cur->image->format, 0, 0, 0);
        put_pixel(cur->image, i, w, pixel);
    }
}

void print_verti(struct Tray *cur, int j)
{
    int lenght = cur->width*cur->size;
    for (int w = 0; w < lenght; w++)
    {
        Uint32 pixel = SDL_MapRGB(cur->image->format, 0, 0, 0);
        put_pixel(cur->image, w, j, pixel);
    }
}

void printwhite(struct Tray *cur, int i, int j)
{
    int x = i * cur->size;
    int y = j * cur->size;
    for (int k = 0; k < cur->size; k++)
    {
        for (int w = 0; w < cur->size; w++)
        {
            Uint32 pixel = SDL_MapRGB(cur->image->format, 255, 255, 255);
            put_pixel(cur->image, x + k, y + w, pixel);
        }
    }
}

void draw(struct Tray *cur)
{
    for (int i = 0; i < cur->height; i++)
        for (int j = 0; j < cur->width; j++)
            (cur->mat[i * cur->width + j]) ? printblack(cur, i, j) : printwhite(cur, i, j);
}

struct Tray *init_Tray(int height, int width, int size)
{
    struct Tray *cur = calloc(1, sizeof(struct Tray));
    cur->height = height;
    cur->width = width;
    cur->size = size;
    cur->mat = calloc(height * width, sizeof(int));
    cur->image = SDL_CreateRGBSurface(0, width * size, height * size, 32, 0, 0, 0, 0);

    return cur;
}

int is_alive(struct Tray *cur, int i, int j)
{
    if (i == -1 || i == cur->height || j == -1 || j == cur->width)
        return 0;
    return cur->mat[i * cur->width + j];
}

int alive(struct Tray *cur, int i, int j)
{
    int neibour = 0;
    neibour += is_alive(cur, i - 1, j - 1);
    neibour += is_alive(cur, i - 1, j);
    neibour += is_alive(cur, i - 1, j + 1);
    neibour += is_alive(cur, i, j - 1);
    neibour += is_alive(cur, i, j + 1);
    neibour += is_alive(cur, i + 1, j - 1);
    neibour += is_alive(cur, i + 1, j);
    neibour += is_alive(cur, i + 1, j + 1);
    return (cur->mat[i * cur->width + j] && neibour == 2) || (!cur->mat[i * cur->width + j] && neibour == 3);
}

void update(struct Tray *cur)
{
    int *mat = calloc(cur->width * cur->height, sizeof(int));

    for (int i = 0; i < cur->height; i++)
        for (int j = 0; j < cur->width; j++)
            mat[i * cur->width + j] = alive(cur, i, j);

    for (int i = 0; i < cur->height; i++)
        for (int j = 0; j < cur->width; j++)
            cur->mat[i * cur->width + j] = mat[i * cur->width + j];
    free(mat);
}

void set_mat(int *mat)
{
    FILE *file = fopen("./set.txt","r");
    char *line = malloc(20 * sizeof(char));
    for(int i = 0; i < 10; i++)
    {
        size_t n;
        getline(&line,&n,file);
        for(int j = 0; j < 10; j++)
            mat[i + j*10] = (line[j] == '1');
    }
}

int over(struct Tray *cur)
{
    for (int i = 0; i < cur->size; i++)
        if(cur->mat[i] == 1)
            return 0;
    return 1;
}



int main()
{
    struct Tray *cur = init_Tray(10, 10, 100);

    SDL_Surface *screen_surface = display_image(cur->image);
    set_mat(cur->mat);
    int  i = 10;
    while (i-- && !over(cur))
    {

        draw(cur);
        for (int i = 0; i < 10; i++)
        {
            print_hori(cur,cur->size*i);
            print_verti(cur,cur->size*i);
        }
        update_surface(screen_surface, cur->image);
        usleep(500000);
        update(cur);
    }
    free(cur->mat);
    SDL_FreeSurface(cur->image);
    SDL_FreeSurface(screen_surface);
    free(cur);

    exit(EXIT_SUCCESS);
}
