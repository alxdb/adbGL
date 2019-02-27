#include "Texture.hpp"
#include "stb_image.h"

namespace adbgl {

Texture::Texture(std::string filename) {
  int width, height, nChan;
  stbi_set_flip_vertically_on_load(1);
  unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nChan, 0);

  if (data == nullptr) {
    throw std::runtime_error("failed to load image: " + filename);
  }

  checkGlError();
  glGenTextures(1, &handle);
  glBindTexture(GL_TEXTURE_2D, handle);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  checkGlError();

  stbi_image_free(data);
}

} // namespace adbgl
