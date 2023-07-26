#ifndef DRAWPOLYGON_H
#define DRAWPOLYGON_H

#include <vector>
#include "vertex2.h"
#include "color.h"

void drawPolygon(const std::vector<Vertex2>& vertices, std::vector<Color>& framebuffer, const Color& outlineColor, const Color& fillColor, int width);

#endif  // DRAWPOLYGON_H
