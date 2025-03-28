#ifndef IMAGE_H
#define IMAGE_H

#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

// A simple image class templated over the pixel type T.
// An image is a rectangular array with
// row r, 0 <= r < height
// column c, 0<= c < width
template <typename T>
class Image
{
public:
  // Construct an image given height and width
  Image(std::size_t height = 0, std::size_t width = 0);

  // get the width of the image
  std::size_t width() const;

  // get the height of the image
  std::size_t height() const;

  // get a reference to pixel r,c
  // r < height or an exception is thrown
  // c < width or an exception is thrown
  T &operator()(std::size_t r, std::size_t c);

  // get a copy of pixel r,c
  // r < height or an exception is thrown
  // c < width or an exception is thrown
  T operator()(std::size_t r, std::size_t c) const;

private:
  std::size_t _width, _height;
  std::vector<T> _data;
};

// define an RGBA pixel
struct Pixel
{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint8_t alpha;
};

// define some common colors
static const Pixel BLACK = {0, 0, 0, 255};
static const Pixel WHITE = {255, 255, 255, 255};
static const Pixel RED = {255, 0, 0, 255};
static const Pixel GREEN = {0, 255, 0, 255};
static const Pixel BLUE = {0, 0, 255, 255};
static const Pixel YELLOW = {255, 255, 0, 255};

// equality comparisons for Pixel
bool operator==(const Pixel &a, const Pixel &b);
bool operator!=(const Pixel &a, const Pixel &b);

// read an Image of RGBA pixels from the PNG formatted file fname
// throws std::runtime_error on failure
Image<Pixel> readFromFile(std::string fname);

// write an Image of RGBA pixels from the PNG formatted file fname
// throws std::runtime_error on failure
void writeToFile(const Image<Pixel> &im, std::string fname);

// ----------------------------------------------------------------------------
// IMPLEMENTATION of Image below
// ----------------------------------------------------------------------------

template <typename T>
Image<T>::Image(std::size_t height, std::size_t width)
    : _height(height), _width(width)
{

  _data.resize(_height * _width);
}

template <typename T>
std::size_t Image<T>::width() const { return _width; }

template <typename T>
std::size_t Image<T>::height() const { return _height; }

template <typename T>
T &Image<T>::operator()(std::size_t r, std::size_t c)
{

  if ((r >= _height) || (c >= _width))
    throw std::out_of_range("Image: Invalid location in operator()");

  return _data[r * _width + c];
}

template <typename T>
T Image<T>::operator()(std::size_t r, std::size_t c) const
{

  if ((r >= _height) || (c >= _width))
    throw std::out_of_range("Image: Invalid location in operator()");

  return _data[r * _width + c];
}

#endif // IMAGE_H
