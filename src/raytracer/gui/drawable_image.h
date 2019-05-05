#ifndef RAYTRACER_DRAWABLE_IMAGE_H
#define RAYTRACER_DRAWABLE_IMAGE_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "raytracer/image/image.h"

namespace raytracer {

class DrawableImage : public sf::Sprite {
 public:
  DrawableImage() noexcept;
  explicit DrawableImage(Image&& _img) noexcept;
  DrawableImage(size_t x, size_t y) noexcept;

  DrawableImage(const DrawableImage& other) noexcept;
  DrawableImage(DrawableImage&& other) noexcept;

  DrawableImage& operator=(const DrawableImage& other) noexcept;
  DrawableImage& operator=(DrawableImage&& other) noexcept;

  inline const Image& Get() const {
    return this->img;
  }

  inline Image& Get() {
    return this->img;
  }

  inline void Update() const {
    texture.update(img.data.data());
  }

 protected:
  Image img;
  mutable sf::Texture texture;
};

}

#endif //RAYTRACER_DRAWABLE_IMAGE_H
