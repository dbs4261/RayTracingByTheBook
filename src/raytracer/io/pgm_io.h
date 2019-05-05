#ifndef CORONAXL_IMAGE_IO_H
#define CORONAXL_IMAGE_IO_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include "raytracer/image/image.h"

namespace raytracer {

/**
 * @brief Reads an image from a grayscale PGM
 * @param fname The file to read.
 * @param size The size of the image.
 * @param data The image data.
 * @return If the read was successful.
 * @warning THIS DOES NOT DEAL WITH COMMENTS. THEY WILL FUCK EVERYTHING UP ROYALLY.
 */
bool ReadPGM(const std::string& fname, Image& img);

bool WritePGM(const std::string& fname, Image& img, bool rescale = false);

}

#endif //CORONAXL_IMAGE_IO_H
