#include "drawable_image.h"

namespace raytracer {

DrawableImage::DrawableImage() noexcept
    : img(), texture(), sf::Sprite(this->texture) {
  this->texture.create(img.GetSize().x, img.GetSize().y);
  this->Update();
}

DrawableImage::DrawableImage(Image&& _img) noexcept
    : img(_img), texture(), sf::Sprite(this->texture) {
  this->texture.create(img.GetSize().x, img.GetSize().y);
  this->Update();
}

DrawableImage::DrawableImage(size_t x, size_t y) noexcept
    : img(x, y), texture(), sf::Sprite(this->texture) {
  this->texture.create(img.GetSize().x, img.GetSize().y);
  this->Update();
}

DrawableImage::DrawableImage(const DrawableImage& other) noexcept
    : img(other.img), texture(), sf::Sprite(this->texture) {
  this->texture.create(img.GetSize().x, img.GetSize().y);
  this->Update();
}

DrawableImage::DrawableImage(DrawableImage&& other) noexcept
    : img(std::move(other.img)), texture(), sf::Sprite(this->texture) {
  this->texture.create(img.GetSize().x, img.GetSize().y);
  this->Update();
}

DrawableImage& DrawableImage::operator=(const DrawableImage& other) noexcept {
  this->img = other.img;
  this->Update();
  return *this;
}

DrawableImage& DrawableImage::operator=(DrawableImage&& other) noexcept {
  this->img = std::move(other.img);
  this->Update();
  return *this;
}

}
