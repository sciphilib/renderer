#include "tgaimage.h"
#include <cmath>
#include <iostream>


const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

// simplified Bresenham`s line algorithm
// TODO:
// 1) asserts and other validation
// 2) optimization
void line(int x0, int y0, int x1, int y1, TGAImage& image, const TGAColor& color) {

  // symmetry test: it's necessaty to draw the same line, regardless
  // of the order of the coordinates of its points
  // line(x0, y0, x1, y1) and line(x1, y1, x0, y0) are the same
  if (x0 > x1) {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }

  // if line is steer (heigh bigger than width)
  // swap coordinates to compute 't' correctly then
  // using x and y in image.set vice versa
  bool steep = false;
  if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
    std::swap(x0, y0);
    std::swap(x1, y1);
    steep = true;
  }

  // optimization:
  // 1. each division has the same divisor
  //    so take it out of the loop 
  const int dx = x1 - x0;
  const int dy = y1 - y0;

  // optimization
  // 2. get rid of all float variables
  // the error stores the distance to the ideal line from current pixel (x, y)
  int error = 0;
  const int derror = std::abs(dy) * 2;
  int y = y0;

  for (int x = x0; x <= x1; ++x) {

    if (steep)
      image.set(y, x, color);
    else
      image.set(x, y, color);
    error += derror;

    if (error > dx) {
      y += (y1 > y0 ? 1 : -1);
      error -= dx * 2;
    }
  }
}

int main() {
  TGAImage image(100, 100, TGAImage::RGB);
  for (int i = 0; i <= 1000000; ++i) {
  line(80, 40, 13, 20, image, red);
  line(13, 20, 80, 40, image, white);
  line(20, 13, 40, 80, image, red);
  }
  // make the origin at the left bottom corner of the image
  image.flip_vertically();
  image.write_tga_file("output.tga");
  return 0;
}
