/*
 * Hexahedron.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_HEXAHEDRON_HPP
#define GLXML_HEXAHEDRON_HPP
#include "glxml_common.h"
#include "Shape.hpp"
using namespace std;


/** @brief Six-sided shape.
 * 
 * %Hexahedron is an abstract base class for a six-sided shape.  It provides 
 * points and normals, but no texture coordinates.
 * 
 * The following diagram depicts which vertices correspond to which points and 
 * faces.
 * <pre>
 *       front            left               top
 *     +-------+        9-------+         17-----16
 *    /|      /|       /|      /|        /|      /|
 *   1-------0 |      8-------+ |       18-----19 |
 *   | +-----|-+      | 10----|-+       | +-----|-+
 *   |/      |/       |/      |/        |/      |/
 *   2-------3        11------+         +-------+
 * 
 *       back             right            bottom
 *     4-------5        +------12        +-------+
 *    /|      /|       /|      /|       /|      /|
 *   +-------+ |      +------13 |      +-------+ |
 *   | 7-----|-6      | +-----|15      | 22----|23
 *   |/      |/       |/      |/       |/      |/
 *   +-------+        +------14        21-----20
 * </pre>
 * 
 * @ingroup basic
 */
class Hexahedron : public Shape {
public:
	Hexahedron(const Tag &tag, ShapeTraits traits);
protected:
	static ShapeTraits getTraits();
	static void load();
	static void toArray(float array[24][3], const Vec4 &l, const Vec4 &u);
	static void toNormals(GLfloat array[24][3]);
	virtual void updateBuffer();
	virtual void updateBufferPoints();
	virtual void updateBufferNormals();
	virtual void updateBufferCoords() = 0;
protected:
	static bool loaded;
	static int indices[8][3];
};


#endif
