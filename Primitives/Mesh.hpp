//
// Created by alxdb on 31/01/19.
//

#ifndef ADBGL_OBJECT_HPP
#define ADBGL_OBJECT_HPP

#include <vector>

#include <GL/glew.h>

class Mesh {
protected:
	std::vector<GLfloat> points;
	std::vector<GLfloat> colours;
	std::vector<GLfloat> tex_coords;

public:
	Mesh(std::vector<GLfloat> points, );
};


#endif //ADBGL_OBJECT_HPP
