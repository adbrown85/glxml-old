/*
 * Square.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_SQUARE_HPP
#define GLXML_SQUARE_HPP
#include "glxml_common.h"
#include "Shape.hpp"                    // Base class
using namespace std;

/** @brief Four-sided, 2D shape with equal width and height.
 * 
 * @ingroup geometry
 */
class Square : public Shape {
public:
	Square(const Tag &tag) : Shape(tag,getTraits()) {}
protected:
	static ShapeTraits getTraits();
	virtual void updateBuffer();
	virtual void updateBufferPoints();
	virtual void updateBufferNormals();
	virtual void updateBufferCoords();
};

#endif
