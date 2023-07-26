#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <vector>
#include "color.h"
#include "vertex2.h"

extern std::vector<std::vector<Color>> framebuffer;

void drawLine(Vertex2 v1, Vertex2 v2, Color c);
void clear(Color c);
void fillPolygon(const std::vector<Vertex2>& vertices, const Color& color);
void saveToFile();
void drawPixel(int x, int y, const Color& color);

#endif // FRAMEBUFFER_H
