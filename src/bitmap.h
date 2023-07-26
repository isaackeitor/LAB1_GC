#pragma once
#include "framebuffer.h"

void writeBMP(const std::string& filename, const std::vector<Color>& framebuffer, int width, int height);
