#ifndef RAYTRACER_VECTOR_TYPES_H
#define RAYTRACER_VECTOR_TYPES_H

#include <array>
#include <cstddef>

namespace raytracer {

template <typename T, size_t N>
struct Coordinate;

template <typename T, size_t N>
struct Coordinate_ {
  inline std::array<T, N>& Array() {
    static_assert(sizeof(Coordinate<T, N>) == sizeof(std::array<T, N>), "Cant convert from Coordinate to Array if they arent teh same size");
    return *reinterpret_cast<std::array<T, N>*>(this);
  }

  inline const std::array<T, N>& Array() const {
    static_assert(sizeof(Coordinate<T, N>) == sizeof(std::array<T, N>), "Cant convert from Coordinate to Array if they arent teh same size");
    return *reinterpret_cast<const std::array<T, N>*>(this);
  }

  inline operator std::array<T, N>&() { // NOLINT(google-explicit-constructor)
    static_assert(sizeof(Coordinate<T, N>) == sizeof(std::array<T, N>), "Cant convert from Coordinate to Array if they arent teh same size");
    return this->Array();
  }

  inline operator const std::array<T, N>&() const {// NOLINT(google-explicit-constructor)
    static_assert(sizeof(Coordinate<T, N>) == sizeof(std::array<T, N>), "Cant convert from Coordinate to Array if they arent teh same size");
    return this->Array();
  }

  template <size_t M>
  inline Coordinate<T, M>& Shrink() {
    static_assert(M <= N, "Reinterpreting the coordinate would expose uninitialized memory");
    return *reinterpret_cast<Coordinate<T, M>*>(this);
  }
};

template <typename T, size_t N>
struct Coordinate : public Coordinate_<T, N> {
  static_assert(N < 1, "Must have at least one dimension");
  static_assert(N > 4, "Only up to 4 dimensions are supported");
};

template <typename T>
struct Coordinate<T, 1> : public Coordinate_<T, 1> {
  static constexpr size_t N = 1;
  T x;

  constexpr explicit Coordinate(T x) : x(x) {}
};

template <typename T>
struct Coordinate<T, 2> : public Coordinate_<T, 2> {
  static constexpr size_t N = 2;
  T x;
  T y;

  constexpr Coordinate(T x, T y) : x(x), y(y) {}
};

template <typename T>
struct Coordinate<T, 3> : public Coordinate_<T, 3> {
  static constexpr size_t N = 3;
  T x;
  T y;
  T z;

  constexpr Coordinate(T x, T y, T z) : x(x), y(y), z(z) {}
};

template <typename T>
struct Coordinate<T, 4> : public Coordinate_<T, 4> {
  static constexpr size_t N = 4;
  T x;
  T y;
  T z;
  T w;

  constexpr Coordinate(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
};

}

#endif //RAYTRACER_VECTOR_TYPES_H
