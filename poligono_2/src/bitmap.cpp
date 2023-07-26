#include "bitmap.h"
#include <fstream>

void writeBMP(const std::string& filename, const std::vector<Color>& framebuffer, int width, int height) {
    std::ofstream bmp(filename, std::ios::binary);

    char header[54] = {
        'B', 'M',           // BMP identifier
        0, 0, 0, 0,         // file size
        0, 0,               // reserved
        0, 0,               // reserved
        54, 0, 0, 0,        // offset
        40, 0, 0, 0,        // DIB header size
        0, 0, 0, 0,         // width
        0, 0, 0, 0,         // height
        1, 0,               // color planes
        24, 0,              // bits per pixel
        0, 0, 0, 0,         // compression method
        0, 0, 0, 0,         // image size
        0, 0, 0, 0,         // horizontal resolution
        0, 0, 0, 0,         // vertical resolution
        0, 0, 0, 0,         // colors in color table
        0, 0, 0, 0          // important color count
    };

    // Encode width, height, and size
    *(int*)&header[2] = 54 + width * height * 3;  // File size
    *(int*)&header[18] = width;
    *(int*)&header[22] = height;
    *(int*)&header[34] = width * height * 3;  // Image size

    bmp.write(header, sizeof(header));

    for(int y = height - 1; y >= 0; --y) {
        for(int x = 0; x < width; ++x) {
            Color color = framebuffer[y * width + x];
            bmp.write((char*)&color.b, 1);
            bmp.write((char*)&color.g, 1);
            bmp.write((char*)&color.r, 1);
        }
    }

    bmp.close();
}
