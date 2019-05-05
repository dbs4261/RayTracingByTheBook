#ifndef RAYTRACER_UTILITY_TYPES_H
#define RAYTRACER_UTILITY_TYPES_H

namespace raytracer {

enum class ChannelType : char {
  GRAY,
  RGB,
  RGBA,
};

constexpr inline size_t Channels(ChannelType type) {
  switch (type) {
    case ChannelType::GRAY:
      return 1;
    case ChannelType::RGB:
      return 3;
    case ChannelType::RGBA:
      return 4;
  }
}

}

#endif //RAYTRACER_UTILITY_TYPES_H
