#include "vertex2.h"
#include "color.h"
#include "framebuffer.h"
#include <vector>
#include <iostream>

// Define a function to draw a polygon.
void drawPolygon(const std::vector<Vertex2>& vertices, const Color& fillColor, const Color& outlineColor, int width) {
    std::cout << "Start drawing polygon..." << std::endl;

    // Fill the polygon.
    fillPolygon(vertices, fillColor);

    std::cout << "After first part of drawing..." << std::endl;

    // Draw the polygon outline.
    for (size_t i = 0; i < vertices.size(); ++i) {
        Vertex2 v1 = vertices[i];
        Vertex2 v2 = vertices[(i + 1) % vertices.size()];
        drawLine(v1, v2, outlineColor);
    }

    std::cout << "After second part of drawing..." << std::endl;
    // Save the drawn image into a file.
    saveToFile();

    std::cout << "Finished drawing polygon..." << std::endl;
}

int main() {
    const Color white(255, 255, 255);
    const Color yellow(255, 255, 0);
    const Color blue(0, 0, 255);
    const Color red(255, 0, 0);
    const Color green(0, 255, 0);
    const Color black(0,0,0);
    
    std::vector<Vertex2> polygonVertices1 = {
        Vertex2(165, 380),
        Vertex2(185, 360),
        Vertex2(180, 330),
        Vertex2(207, 345),
        Vertex2(233, 330),
        Vertex2(230, 360),
        Vertex2(250, 380),
        Vertex2(220, 385),
        Vertex2(205, 410),
        Vertex2(193, 383)
    };
  
    std::vector<Vertex2> polygonVertices2 = {
        Vertex2(321, 335),
        Vertex2(288, 286),
        Vertex2(339, 251),
        Vertex2(374, 302)
    };
  
    std::vector<Vertex2> polygonVertices3 = {
        Vertex2(377, 249),
        Vertex2(411, 197),
        Vertex2(436, 249)
    };
  
    std::vector<Vertex2> polygonVertices4 = {
        Vertex2(413, 177),
        Vertex2(448, 159),
        Vertex2(502, 88),
        Vertex2(553, 53),
        Vertex2(535, 36),
        Vertex2(676, 37),
        Vertex2(660, 52),
        Vertex2(750, 145),
        Vertex2(761, 179),
        Vertex2(672, 192),
        Vertex2(659, 214),
        Vertex2(615, 214),
        Vertex2(632, 230),
        Vertex2(580, 230),
        Vertex2(597, 215),
        Vertex2(552, 214),
        Vertex2(517, 144),
        Vertex2(466, 180)
    };

    std::vector<Vertex2> polygonVertices5 = {
        Vertex2(682, 175),
        Vertex2(708, 120),
        Vertex2(735, 148),
        Vertex2(739, 170)
    };
  
    // Set the dimensions of the frame buffer (i.e., the size of the image).
    const int width = 800;
    const int height = 600;

    // Clear the framebuffer with black color.
    clear(Color(0, 0, 0));

    // Draw the polygon.
    drawPolygon(polygonVertices1, yellow, white, width);
    drawPolygon(polygonVertices2, blue, white, width);
    drawPolygon(polygonVertices3, red, white, width);
    drawPolygon(polygonVertices4, green, white, width);
    drawPolygon(polygonVertices5, black, white, width);

    return 0;
}
