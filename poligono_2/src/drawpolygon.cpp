#include <vector>
#include "vertex2.h"
#include "color.h"
#include "drawpolygon.h"
#include "framebuffer.h"
#include <iostream>

void drawPolygon(const std::vector<Vertex2>& vertices, std::vector<Color>& framebuffer, const Color& outlineColor, const Color& fillColor, int width) {
    // Clear the framebuffer with black color.
    std::cout << "Starting to draw polygon..." << std::endl;
    clear(Color(0, 0, 0));

    std::cout << "After initial setup..." << std::endl;
    // Draw the filled polygon.
    fillPolygon(vertices, fillColor);

    std::cout << "After first part of drawing..." << std::endl;
    // Draw the outline of the polygon.
    for (size_t i = 0; i < vertices.size(); ++i) {
        drawLine(vertices[i], vertices[(i+1) % vertices.size()], outlineColor);
    }

    std::cout << "After finishing drawing..." << std::endl;
    // Save the framebuffer to file.
    saveToFile();
}
