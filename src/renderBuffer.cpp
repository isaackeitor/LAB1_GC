#include <fstream>
#include "renderBuffer.h"

void renderBuffer(const std::vector<Color>& framebuffer, int width, int height) {
    std::ofstream file("out.bmp", std::ios::out | std::ios::binary);

    // BMP file header
    unsigned char fileHeader[14] = {
        'B', 'M', // magic
        0, 0, 0, 0, // size in bytes
        0, 0, // app data
        0, 0, // app data
        40 + 14, 0, 0, 0 // start of data offset
    };

    // BMP info header
    unsigned char infoHeader[40] = {
        40, 0, 0, 0, // info hd size
        0, 0, 0, 0, // width
        0, 0, 0, 0, // heigth
        1, 0, // number color planes
        24, 0, // bits per pixel
        0, 0, 0, 0, // compression is none
        0, 0, 0, 0, // image bits size
        0x13, 0x0B, 0, 0, // horz resolution in pixel / m
        0x13, 0x0B, 0, 0, // vert resolution (0x03C3 = 96 dpi, a good value)
        0, 0, 0, 0, // #colors in palette
        0, 0, 0, 0, // #important colors
    };

    // BMP file size
    int fileSize = 54 + 3 * width * height;
    fileHeader[2] = (unsigned char)(fileSize);
    fileHeader[3] = (unsigned char)(fileSize >> 8);
    fileHeader[4] = (unsigned char)(fileSize >> 16);
    fileHeader[5] = (unsigned char)(fileSize >> 24);

    // width and height
    infoHeader[4] = (unsigned char)(width);
    infoHeader[5] = (unsigned char)(width >> 8);
    infoHeader[6] = (unsigned char)(width >> 16);
    infoHeader[7] = (unsigned char)(width >> 24);
    infoHeader[8] = (unsigned char)(height);
    infoHeader[9] = (unsigned char)(height >> 8);
    infoHeader[10] = (unsigned char)(height >> 16);
    infoHeader[11] = (unsigned char)(height >> 24);

    file.write(reinterpret_cast<char*>(fileHeader), 14);
    file.write(reinterpret_cast<char*>(infoHeader), 40);

    // write the data
    for (int i = 0; i < height * width; ++i) {
        Color c = framebuffer[i];
        file.write(reinterpret_cast<const char*>(&c.b), 1);
        file.write(reinterpret_cast<const char*>(&c.g), 1);
        file.write(reinterpret_cast<const char*>(&c.r), 1);
    }

    file.close();
}
