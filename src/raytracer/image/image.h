#ifndef RAYTRACER_IMAGE_H
#define RAYTRACER_IMAGE_H

#include <array>
#include <vector>

#include "raytracer/utilities/utility_types.h"
#include "raytracer/utilities/vector_types.h"

namespace raytracer {

struct RGBA {
  static constexpr ChannelType type = ChannelType::RGBA;
  static constexpr size_t channels = 4;

  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
};

class Image {
 public:
  static constexpr ChannelType type = RGBA::type;
  static constexpr size_t channels = RGBA::channels;

  Image() noexcept;
  Image(size_t x, size_t y) noexcept;
  Image(const Image& other) noexcept;
  Image(Image&& other) noexcept;

  Image& operator=(const Image& other) noexcept;
  Image& operator=(Image&& other) noexcept;

  inline const Coordinate<size_t, 2>& GetSize() const {
    return this->size;
  }

  void SetSize(const Coordinate<size_t, 2>& new_size);

  std::vector<unsigned char> data;
  std::vector<RGBA>& color_data;
 protected:
  Coordinate<size_t, 2> size;
};

}

#endif //RAYTRACER_IMAGE_H
