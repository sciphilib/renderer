#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "model.h"

Model::Model(const char* filename) :  verts_(), faces_() {
  std::ifstream in;
  in.open(filename, std::ifstream::in);
  if (in.fail()) return;
  std::string line;
  
  while (!in.eof()) {
    std::getline(in, line);
    std::istringstream iss(line.c_str());
    char trash, check;
    if (!line.compare(0, 2, "v ")) {
      iss >> trash;
      Vec3f v;
      for (int i = 0; i < 3; ++i) iss >> v.raw[i];
      verts_.push_back(v);
    }
    else if (!line.compare(0, 2, "f ")) {
      std::vector<int> f;
      int itrash, idx;
      // checking if texture coordinates are missing in face elements
      iss >> trash >> itrash >> trash;
      check = iss.peek();
      iss.seekg(0);
      iss >> trash;
      if (check == '/')
	while (iss >> idx >> trash >> trash >> itrash) {
	  // in wavefront obj all indices start at 1, not 0
	  idx--;
	  f.push_back(idx);
	}
      else 
	while (iss >> idx >> trash >> itrash >> trash >> itrash) {
	  // in wavefront obj all indices start at 1, not 0
	  idx--;
	  f.push_back(idx);
	}
      faces_.push_back(f);
    }
  }
  std::cerr << "# v# " << verts_.size() << " f# " << faces_.size() << std::endl;
}

int Model::nfaces() { return static_cast<int>(faces_.size()); }

int Model::nverts() { return static_cast<int>(verts_.size()); }

std::vector<int> Model::face(int idx) { return faces_[idx]; }

Vec3f Model::vert(int i) { return verts_[i]; }
