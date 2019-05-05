#ifndef RAYTRACER_TONE_GENERATOR_H
#define RAYTRACER_TONE_GENERATOR_H

#include "raytracer/image/image.h"
#include "raytracer/image/saturation_conversions.h"

namespace raytracer {

inline bool CheckerBoard(unsigned int x, unsigned int y) {
  return ((x % 2 == 0 and y % 2 == 0) or (x % 2 == 1 and y % 2 == 1));
}

template <ChannelType C, typename T, typename S>
void Checkerboard(T* data, S width, S height, S check_size) {
  for (S x = 0; x < width; x++) {
    for (S y = 0;y < height; y++) {
      data[(y * width + x) * RGBA::channels + 0] = normalize_cast<T>(CheckerBoard(x / check_size, y / check_size));
      if constexpr (C == ChannelType::RGB or C == ChannelType::RGBA) {
        data[(y * width + x) * RGBA::channels + 1] = normalize_cast<T>(CheckerBoard(x / check_size, y / check_size));
        data[(y * width + x) * RGBA::channels + 2] = normalize_cast<T>(CheckerBoard(x / check_size, y / check_size));
      }
      if constexpr (C == ChannelType::RGBA) {
        data[(y * width + x) * RGBA::channels + 3] = normalize_cast<T>(true);
      }
    }
  }
}

template void Checkerboard<ChannelType::RGBA, unsigned char, size_t>(unsigned char*, size_t, size_t, size_t);

inline void Checkerboard(Image& img, size_t check_size) {
  Checkerboard<Image::type>(img.data.data(), img.GetSize().x, img.GetSize().y, check_size);
}

template <ChannelType C, typename T, typename S>
void ColorBars(T* data, S width, S height) {
  static_assert(C != ChannelType::GRAY, "Doesnt make sense to generate bars for gray image");
  memset(data, 0, sizeof(std::decay_t<T>) * width * height * Channels(C));
  const S bottom = height * 0.67;
  const S crenelation = height * 0.75;
  for (unsigned int y = 0; y < height; y++) {
    for (unsigned int x = 0; x < width; x++) {
      if constexpr (C == ChannelType::RGBA) {
        data[(y * width + x) * 4 + 3] = static_cast<unsigned char>(255);
      }
      if (y < crenelation) { // EIA Bars
        if (x < width / 7.0) { // White
          if (y < bottom) {
            data[(y * width + x) * 4 + 0] = normalize_cast<T>(0.75);
            data[(y * width + x) * 4 + 1] = normalize_cast<T>(0.75);
          }
          data[(y * width + x) * 4 + 2] = normalize_cast<T>(0.75);
        } else if (x < 2.0 * width / 7.0) { // Yellow
          if (y < bottom) {
            data[(y * width + x) * 4 + 0] = normalize_cast<T>(0.75);
            data[(y * width + x) * 4 + 1] = normalize_cast<T>(0.75);
          }
        } else if (x < 3.0 * width / 7.0) { // Teal
          if (y < bottom) {
            data[(y * width + x) * 4 + 1] = normalize_cast<T>(0.75);
          } else {
            data[(y * width + x) * 4 + 0] = normalize_cast<T>(0.75);
          }
          data[(y * width + x) * 4 + 2] = normalize_cast<T>(0.75);
        } else if (x < 4.0 * width / 7.0) { // Green
          if (y < bottom) {
            data[(y * width + x) * 4 + 1] = normalize_cast<T>(0.75);
          }
        } else if (x < 5.0 * width / 7.0) { // Magenta
          if (y < bottom) {
            data[(y * width + x) * 4 + 0] = normalize_cast<T>(0.75);
          } else {
            data[(y * width + x) * 4 + 1] = normalize_cast<T>(0.75);
          }
          data[(y * width + x) * 4 + 2] = normalize_cast<T>(0.75);
        } else if (x < 6.0 * width / 7.0) { // Red
          if (y < bottom) {
            data[(y * width + x) * 4 + 0] = normalize_cast<T>(0.75);
          }
        } else { // Blue
          data[(y * width + x) * 4 + 2] = normalize_cast<T>(0.75);
          if (y >= bottom) {
            data[(y * width + x) * 4 + 0] = normalize_cast<T>(0.75);
            data[(y * width + x) * 4 + 1] = normalize_cast<T>(0.75);
          }
        }
      } else {
        data[(y * width + x) * 4 + 0] = normalize_cast<T>((double)x / (double)width);
        data[(y * width + x) * 4 + 1] = normalize_cast<T>((double)x / (double)width);
        data[(y * width + x) * 4 + 2] = normalize_cast<T>((double)x / (double)width);
      }
    }
  }
}

template void ColorBars<ChannelType::RGBA, unsigned char, size_t>(unsigned char*, size_t, size_t);


inline void ColorBars(Image& img) {
  ColorBars<Image::type>(img.data.data(), img.GetSize().x, img.GetSize().y);
}

}

#endif //RAYTRACER_TONE_GENERATOR_H
