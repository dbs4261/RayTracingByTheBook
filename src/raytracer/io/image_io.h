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
bool ReadPGM(const std::string& fname, Image& img) {
  std::ifstream infile(fname);
  if (not infile.is_open()) {
    infile.open(fname);
  }

  if (infile.is_open()) {
    std::string magic;
    infile >> magic;
    if (magic == "P2") {
      size_t size_x, size_y, max;
      infile >> size_x >> size_y >> max;
      img.SetSize(size_x, size_y);
      if (max <= std::numeric_limits<unsigned char>::max()) {
        std::cerr << "Maximum value in the PGM, " << max << " is greater than the container can hold" << std::endl;
        return false;
      }
      size_t max_index = size_x * size_y;
      int temp_val;
      size_t index = 0;
      while (index < max_index) {
        infile >> temp_val;
        img.data.at(index) = static_cast<unsigned char>(temp_val);
        if (infile.eof()) {
          std::cerr << "Was unable to read all the data from the file" << std::endl;
          return false;
        }
        index++;
      }
      if (index != max_index) {
        std::cerr << "Not all pixels read: " << index << " out of " << max_index << std::endl;
        return false;
      }
    } else {
      std::cerr << "Header " << magic << " is not valid" << std::endl;
      return false;
    }
  } else {
    std::cerr << "File " << fname << " unreadable" << std::endl;
    return false;
  }
  return true;
};

bool WritePGM(const std::string& fname, Image& img, bool rescale = false) {
  std::ofstream outfile(fname);
  if (not outfile.is_open()) {
    outfile.open(fname);
  }

  if (outfile.is_open()) {
    outfile << "P2 ";
    outfile << img.GetX() << " " << img.GetY() << '\n';
    if (rescale) {
      outfile << (unsigned int) * std::max_element(img.data.begin(), img.data.end()) << '\n';
    } else {
      outfile << "255\n";
    }
    for (size_t y = 0; y < img.GetY(); y++) {
      std::copy(img.data.data() + (y * img.GetX()),
          img.data.data() + ((y + 1) * img.GetX()),
          std::ostream_iterator<unsigned int>(outfile, " "));
      outfile << '\n';
    }
    return not outfile.fail();
  } else {
    return false;
  }
};

}

#endif //CORONAXL_IMAGE_IO_H
