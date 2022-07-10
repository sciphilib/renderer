#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
  for (float t = 0.0f; t < 1.0f; t+= 0.01f) {
    int x = x0*(1.0f - t) + x1*t;
    int y = y0*(1.0f - t) + y1*t;
    image.set(x, y, color);
  }
}

int main() {
  TGAImage image(100, 100, TGAImage::RGB);
  line(10, 70, 30, 10, image, white);
  image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
  image.write_tga_file("output.tga");
  return 0;
}
