#include "image.h"

// for file I/O
#include "lodepng.h"

Image<Pixel> readFromFile(std::string fname)
{
  std::vector<unsigned char> raw;
  unsigned h, w;

  // decode the png
  unsigned error = lodepng::decode(raw, w, h, fname.c_str());

  if (error)
    throw std::runtime_error(lodepng_error_text(error));

  Image<Pixel> im(h, w);
  std::size_t idx = 0;
  for (std::size_t r = 0; r < im.height(); r++)
    for (std::size_t c = 0; c < im.width(); c++)
    {
      im(r, c).red = raw[idx++];
      im(r, c).green = raw[idx++];
      im(r, c).blue = raw[idx++];
      im(r, c).alpha = raw[idx++];
    }

  return im;
}

void writeToFile(const Image<Pixel> &im, std::string fname)
{

  std::vector<unsigned char> raw(4 * im.width() * im.height());

  std::size_t idx = 0;
  for (std::size_t r = 0; r < im.height(); r++)
    for (std::size_t c = 0; c < im.width(); c++)
    {
      raw[idx++] = im(r, c).red;
      raw[idx++] = im(r, c).green;
      raw[idx++] = im(r, c).blue;
      raw[idx++] = im(r, c).alpha;
    }

  // encode the image
  unsigned error = lodepng::encode(fname.c_str(), raw, im.width(), im.height());

  if (error)
    throw std::runtime_error(lodepng_error_text(error));
}

bool operator==(const Pixel &a, const Pixel &b)
{
  return (a.red == b.red) && (a.green == b.green) && (a.blue == b.blue) &&
         (a.alpha == b.alpha);
}

bool operator!=(const Pixel &a, const Pixel &b) { return !(a == b); }
