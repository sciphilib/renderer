#include <cmath>

#include "tgaimage.h"
#include "model.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
// output picture size
const int width  = 3000;
const int height = 3000;
// variables to adjusting the ouput image
float scale   = 3.0f;
float xoffset = 2.0f; // move the model by x
float yoffset = 0.1f; // move the model by y
// model's path
const char* filename = "obj/tree.obj";
const char* output   = "output/tree.tga";

// simplified Bresenham`s line algorithm
// TODO:
// 1) asserts and other validation
void line(int x0, int y0, int x1, int y1, TGAImage& image, const TGAColor& color) {

  // if line is steer (heigh bigger than width)
  // swap coordinates to compute 't' correctly then
  // using x and y in image.set vice versa
  bool steep = false;
  if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
    std::swap(x0, y0);
    std::swap(x1, y1);
    steep = true;
  }
  
  // symmetry test: it's necessaty to draw the same line, regardless
  // of the order of the coordinates of its points
  // line(x0, y0, x1, y1) and line(x1, y1, x0, y0) are the same
  if (x0 > x1) {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }

  const int dx = x1 - x0;
  const int dy = y1 - y0;
  const int derror = std::abs(dy) * 2;
  int error = 0;
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
  Model* pmodel = new Model(filename);
  TGAImage image(width, height, TGAImage::RGB);
  
  for (int i = 0; i < pmodel->nfaces(); ++i) {
    std::vector<int> face = pmodel->face(i);

    // count of vertices in the current face line
    int n = face.size();

    for (int j = 0; j < n; ++j) {
      Vec3f v0 = pmodel->vert(face[j]);
      Vec3f v1 = pmodel->vert(face[(j + 1)%n]);
      int x0 = (v0.x + xoffset) * width/scale;
      int y0 = (v0.y + yoffset) * height/scale;
      int x1 = (v1.x + xoffset) * width/scale;
      int y1 = (v1.y + yoffset) * height/scale;
      line(x0, y0, x1, y1, image, white);
    }
  }

  delete pmodel;
  // make the origin at the left bottom corner of the image
  image.flip_vertically();
  image.write_tga_file(output);
  return 0;
}
