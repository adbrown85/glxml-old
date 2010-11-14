/*
 * Box.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_BOX_HPP
#define GLXML_BOX_HPP
#include "glxml_common.h"
#include "Hexahedron.hpp"
using namespace std;

/** @brief Six-sided shape with 2D texture coordinates for each face.
 * 
 * @ingroup geometry
 */
class Box : public Hexahedron {
public:
	Box(const Tag &tag) : Hexahedron(tag,getTraits()) {};
protected:
	virtual void updateBufferCoords();
};


#endif
