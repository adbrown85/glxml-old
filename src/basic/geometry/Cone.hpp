/*
 * Cone.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CONE_HPP
#define CONE_HPP
#include "glxml_common.h"
#include <gloop/Math.hpp>               // Calculating circle
#include "Shape.hpp"                    // Base class
using namespace std;


/** @brief Tapered cylinder made from triangles.
 * @ingroup basic
 */
class Cone : public Shape {
public:
	Cone(const Tag &tag) : Shape(tag,getTraits()) {}
protected:
	static ShapeTraits getTraits();
	virtual void updateBuffer();
	virtual void updateBufferPoints();
	virtual void updateBufferNormals();
};


#endif
