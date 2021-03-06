/*
 * Square.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Square.hpp"

ShapeTraits Square::getTraits() {
	
	ShapeTraits traits;
	
	traits.count = 4;
	traits.mode = GL_QUADS;
	traits.usage = GL_STATIC_DRAW;
	traits.attributes.push_back("MCVertex");
	traits.attributes.push_back("MCNormal");
	traits.attributes.push_back("TexCoord0");
	return traits;
}

void Square::updateBuffer() {
	
	updateBufferPoints();
	updateBufferNormals();
	updateBufferCoords();
}

void Square::updateBufferPoints() {
	
	GLfloat points[4][3] = {{+0.5,+0.5,0.0},
	                        {-0.5,+0.5,0.0},
	                        {-0.5,-0.5,0.0},
	                        {+0.5,-0.5,0.0}};
	
	setBufferData("MCVertex", points);
}

void Square::updateBufferNormals() {
	
	GLfloat normals[4][3] = {{0.0,0.0,+1.0},
	                         {0.0,0.0,+1.0},
	                         {0.0,0.0,+1.0},
	                         {0.0,0.0,+1.0}};
	
	setBufferData("MCNormal", normals);
}

void Square::updateBufferCoords() {
	
	GLfloat coords[4][3] = {{1.0,1.0,0.0},
	                        {0.0,1.0,0.0},
	                        {0.0,0.0,0.0},
	                        {1.0,0.0,0.0}};
	
	setBufferData("TexCoord0", coords);
}
