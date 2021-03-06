/*
 * Disk.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_DISK_HPP
#define GLXML_DISK_HPP
#include "glxml_common.h"
#include <gloop/Math.hpp>               // Calculating circle
#include "Shape.hpp"                    // Base class
using namespace std;


/** @brief Circular disk made from a triangle fan.
 * 
 * @ingroup geometry
 */
class Disk : public Shape {
public:
	Disk(const Tag &tag) : Shape(tag,getTraits()) {}
protected:
	static ShapeTraits getTraits();
	virtual void updateBuffer();
	virtual void updateBufferPoints();
	virtual void updateBufferNormals();
};


#endif
