#ifndef RAYTRACER_SATURATION_CONVERSIONS_H
#define RAYTRACER_SATURATION_CONVERSIONS_H

#include <limits>
#include <type_traits>

namespace raytracer {

template <typename A, typename B>
using wider_t = std::conditional_t<(std::numeric_limits<A>::digits > std::numeric_limits<B>::digits), A, B>;

template <typename OUT, typename IN>
constexpr std::enable_if_t<std::is_integral_v<OUT>, OUT> saturate_cast(IN in, std::enable_if_t<std::is_integral_v<IN>, bool> = true) noexcept {
  if constexpr (std::is_unsigned_v<OUT>) {
    return std::min(static_cast<wider_t<OUT, IN>>(std::max(in, static_cast<IN>(0))), static_cast<wider_t<OUT, IN>>(std::numeric_limits<OUT>::max()));
  } else {
    return std::min(static_cast<wider_t<OUT, IN>>(in), static_cast<wider_t<OUT, IN>>(std::numeric_limits<OUT>::max()));
  }
}

template <typename OUT, typename IN>
constexpr std::enable_if_t<std::is_integral_v<OUT>, OUT> saturate_cast(IN in, std::enable_if_t<std::is_floating_point_v<IN>, bool> = true) noexcept {
  if constexpr (std::is_unsigned_v<OUT>) {
    return std::max(in, static_cast<IN>(0)) * std::numeric_limits<OUT>::max();
  } else {
    return in * std::numeric_limits<OUT>::max();
  }
}

template <typename OUT, typename IN>
constexpr std::enable_if_t<std::is_floating_point_v<OUT>, OUT> saturate_cast(IN in, std::enable_if_t<std::is_integral_v<IN>, bool> = true) noexcept {
  return static_cast<OUT>(in) / static_cast<OUT>(std::numeric_limits<IN>::max());
}

template <typename OUT, typename IN>
constexpr std::enable_if_t<std::is_floating_point_v<OUT>, OUT> saturate_cast(IN in, std::enable_if_t<std::is_floating_point_v<IN>, bool> = true) noexcept {
  return in;
}

template <typename OUT, typename IN>
constexpr std::enable_if_t<std::is_integral_v<OUT>, OUT> normalize_cast(IN in, std::enable_if_t<std::is_integral_v<IN>, bool> = true) noexcept {
  if constexpr (std::numeric_limits<OUT>::digits > std::numeric_limits<IN>::digits) {
    if constexpr (std::is_unsigned_v<OUT>) {
      return std::max(static_cast<OUT>(in), static_cast<OUT>(0)) * static_cast<OUT>(1 << (std::numeric_limits<OUT>::digits - std::numeric_limits<IN>::digits));
    } else {
      return static_cast<OUT>(in) * static_cast<OUT>(1 << (std::numeric_limits<OUT>::digits - std::numeric_limits<IN>::digits));
    }
  } else {
    if constexpr (std::is_unsigned_v<OUT>) {
      return std::max(in, static_cast<IN>(0)) / (std::numeric_limits<IN>::digits - std::numeric_limits<OUT>::digits);
    } else {
      return in / (std::numeric_limits<IN>::digits - std::numeric_limits<OUT>::digits);
    }
  }
}

template <typename OUT, typename IN>
constexpr std::enable_if_t<std::is_integral_v<OUT>, OUT> normalize_cast(IN in, std::enable_if_t<std::is_floating_point_v<IN>, bool> = true) noexcept {
  if constexpr (std::is_unsigned_v<OUT>) {
    return std::numeric_limits<OUT>::max() * std::max(in, static_cast<IN>(0));
  } else {
    return std::numeric_limits<OUT>::max() * in;
  }
}

template <typename OUT, typename IN>
constexpr std::enable_if_t<std::is_floating_point_v<OUT>, OUT> normalize_cast(IN in, std::enable_if_t<std::is_integral_v<IN>, bool> = true) noexcept {
  return static_cast<OUT>(in) / static_cast<OUT>(std::numeric_limits<IN>::max());
}

template <typename OUT, typename IN>
constexpr std::enable_if_t<std::is_floating_point_v<OUT>, OUT> normalize_cast(IN in, std::enable_if_t<std::is_floating_point_v<IN>, bool> = true) noexcept {
  return in;
}

}

#endif //RAYTRACER_SATURATION_CONVERSIONS_H
