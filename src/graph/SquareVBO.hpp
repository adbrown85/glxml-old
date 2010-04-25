/*
 * SquareVBO.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SQUAREVBO_HPP
#define SQUAREVBO_HPP
#include <iostream>
#include <GL/glut.h>
#include <sstream>
#include "Shape.hpp"
#include "Program.hpp"
#include "Tag.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief
 *     2D square shape that can be drawn by %Display.
 */
class SquareVBO : public Shape {
	
	public:
		
		SquareVBO(const Tag &tag);
		virtual void associate();
		virtual void finalize();
		virtual void draw() const;
	
	protected:
		
		Program *program;
		GLint coordsLoc, normalsLoc, pointsLoc;
		static bool loaded;
		static GLfloat coords[4][3], normals[4][3], points[4][3];
		static GLint coordsOffset, normalsOffset, pointsOffset;
		static GLuint dataBuffer, indicesBuffer;
		static GLushort indices[4];
		
		virtual void initBuffers();
		virtual void initCoords();
		virtual void initIndices();
		virtual void initNormals();
		virtual void initPoints();
};


#endif