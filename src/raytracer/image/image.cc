#include "image.h"

namespace raytracer {

Image::Image() noexcept : Image(1, 1) {}

Image::Image(size_t x, size_t y) noexcept :
    size({.x=x, .y=y}), data(x * y * RGBA::channels),
    color_data(*reinterpret_cast<std::vector<RGBA>*>(&this->data)) {
}

Image::Image(const Image& other) noexcept :
    size(other.size), data(other.data),
    color_data(*reinterpret_cast<std::vector<RGBA>*>(&this->data)) {
}

Image::Image(Image&& other) noexcept :
    size(std::move(other.size)), // NOLINT(performance-move-const-arg)
    data(std::move(other.data)),
    color_data(*reinterpret_cast<std::vector<RGBA>*>(&this->data)) {
}

Image& Image::operator=(const Image& other) noexcept {
  this->size = other.size;
  this->data = other.data;
  this->color_data = *reinterpret_cast<std::vector<RGBA>*>(&this->data);
  return *this;
}

Image& Image::operator=(Image&& other) noexcept {
  this->size = std::move(other.size); // NOLINT(performance-move-const-arg)
  this->data = std::move(other.data);
  this->color_data = *reinterpret_cast<std::vector<RGBA>*>(&this->data);
  return *this;
}

const Coordinate<size_t, 2>& Image::GetSize() const {
  return this->size;
}

void Image::SetSize(const Coordinate<size_t, 2>& new_size)  {
  this->size = new_size;
  this->data.resize(new_size.x * new_size.y * RGBA::channels);
  this->color_data = *reinterpret_cast<std::vector<RGBA>*>(&this->data);
}

}