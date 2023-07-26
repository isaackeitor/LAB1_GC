#include "framebuffer.h"
#include <fstream>
#include <iostream>
#include <algorithm>

std::vector<std::vector<Color>> framebuffer(800, std::vector<Color>(600, Color(0, 0, 0)));

void clear(Color clearColor) {
    for(auto& row: framebuffer)
    {
        for(auto& pixel: row)
        {
            pixel = clearColor;
        }
    }
}

void drawLine(Vertex2 v1, Vertex2 v2, Color color) {
    int dx = abs(v2.x - v1.x), sx = v1.x < v2.x ? 1 : -1;
    int dy = -abs(v2.y - v1.y), sy = v1.y < v2.y ? 1 : -1; 
    int err = dx + dy, e2;

    while(true){
        drawPixel(v1.x, v1.y, color);
        if (v1.x == v2.x && v1.y == v2.y) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; v1.x += sx; }
        if (e2 <= dx) { err += dx; v1.y += sy; }
    }
}

void drawPixel(int x, int y, const Color& color) {
    if(x >= 0 && x < 800 && y >= 0 && y < 600) {
        framebuffer[x][y] = color;
    }
}

void fillPolygon(const std::vector<Vertex2>& vertices, const Color& color) {
    int minY = vertices[0].y;
    int maxY = vertices[0].y;
    for (const Vertex2& vertex : vertices) {
        minY = std::min(minY, vertex.y);
        maxY = std::max(maxY, vertex.y);
    }

    for (int y = minY; y <= maxY; ++y) {
        std::vector<int> intersections;
        for (int i = 0; i < vertices.size(); ++i) {
            Vertex2 v1 = vertices[i];
            Vertex2 v2 = vertices[(i + 1) % vertices.size()];
            if ((v1.y <= y && y < v2.y) || (v2.y <= y && y < v1.y)) {
                float x = v1.x + (v2.x - v1.x) * float(y - v1.y) / float(v2.y - v1.y);
                intersections.push_back(int(x));
            }
        }

        std::sort(intersections.begin(), intersections.end());

        for (int i = 0; i + 1 < intersections.size(); i += 2) {
            int xStart = intersections[i];
            int xEnd = intersections[i + 1];
            for (int x = xStart; x <= xEnd; ++x) {
                drawPixel(x, y, color);
            }
        }
    }
}

void saveToFile() {
    std::ofstream file("out.bmp", std::ios::binary);

    if (!file) {
        std::cerr << "Could not open the file to write.\n";
        return;
    }

    int width = framebuffer.size();
    int height = framebuffer[0].size();
    int fileSize = 54 + 3 * width * height;  // w*h*3 + 54 (header size)
    int padding = (4 - (width * 3) % 4) % 4;

    unsigned char bmpFileHeader[14] = {
        'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0
    };

    unsigned char bmpInfoHeader[40] = {
        40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0
    };

    bmpFileHeader[2] = (unsigned char)(fileSize);
    bmpFileHeader[3] = (unsigned char)(fileSize >> 8);
    bmpFileHeader[4] = (unsigned char)(fileSize >> 16);
    bmpFileHeader[5] = (unsigned char)(fileSize >> 24);

    bmpInfoHeader[4] = (unsigned char)(width);
    bmpInfoHeader[5] = (unsigned char)(width >> 8);
    bmpInfoHeader[6] = (unsigned char)(width >> 16);
    bmpInfoHeader[7] = (unsigned char)(width >> 24);

    bmpInfoHeader[8] = (unsigned char)(height);
    bmpInfoHeader[9] = (unsigned char)(height >> 8);
    bmpInfoHeader[10] = (unsigned char)(height >> 16);
    bmpInfoHeader[11] = (unsigned char)(height >> 24);

    file.write((const char*)bmpFileHeader, 14);
    file.write((const char*)bmpInfoHeader, 40);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Color color = framebuffer[j][i];

            file.write((const char*)&color.b, 1);
            file.write((const char*)&color.g, 1);
            file.write((const char*)&color.r, 1);
        }
        file.write("\0\0\0", padding);
    }
    file.close();
}
