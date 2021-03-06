/*
 * Cube.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_CUBE_HPP
#define GLXML_CUBE_HPP
#include "glxml_common.h"
#include "Hexahedron.hpp"
using namespace std;

/** @brief Six-sided shape with 3D texture coordinates.
 * 
 * @ingroup geometry
 */
class Cube : public Hexahedron {
public:
	Cube(const Tag &tag) : Hexahedron(tag,getTraits()) {};
protected:
	virtual void updateBufferCoords();
};


#endif
