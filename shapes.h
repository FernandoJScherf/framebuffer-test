#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

//If I want to port to DOS:
//http://www.brackeen.com/vga/index.html
//(Also talks about Primitive Shapes and Lines!

// lineas:
//https://www.freecodecamp.org/news/how-to-code-your-first-algorithm-draw-a-line-ca121f9a1395/
//http://members.chello.at/easyfilter/bresenham.html

// triangles:
//      http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html#algo1
// https://www.joshbeam.com/articles/triangle_rasterization/

// mas sofisticado, con gradientes y texturas:
// http://www-users.mat.uni.torun.pl/~wrona/3d_tutor/tri_fillers.html
// http://www.salomonsson.se/devlog/math5.html
    // http://www.hugi.scene.org/online/coding/hugi%2017%20-%20cotriang.htm

// Later I could implement some "other types" of triangles: textured, gourald?, noise, etc.

typedef struct Point {
    float x, y;
} Point;

enum basicColor {RED = 0xFFFF0000, GREEN = 0xFF00FF00, BLUE = 0xFF0000FF};

//Let's try to do it better:
//http://www.hugi.scene.org/online/coding/hugi%2017%20-%20cotriang.htm

void TriangleFlat(Point v1, Point v2, Point v3, uint32_t argb, SDL_Surface* surface);
//static void DrawSegment( int topY, int bottomY, float leftX, float rightX,
//                    float left_dXdY, float right_dXdY, uint32_t argb, SDL_Surface* surface);

void LineBresenham( uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1,
                    uint32_t argb, SDL_Surface* surface);

void PolyFlat(const Point** points, uint16_t nPoitns, uint32_t argb, SDL_Surface* surface);

#endif // SHAPES_H_INCLUDED
