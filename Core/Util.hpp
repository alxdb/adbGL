//
// Created by alxdb on 09/01/19.
//

#ifndef ADBGL_UTIL_HPP
#define ADBGL_UTIL_HPP

#include <string>

#define GL_FUNC(body) checkGlError(); body checkGlError();

std::string read_whole_file(const std::string &filename);
void checkGlError();

#endif //ADBGL_UTIL_HPP
