/*
 * GeometryFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GEOMETRYFACTORY_HPP
#define GEOMETRYFACTORY_HPP
#include "glxml_common.h"
#include "Factory.hpp"
#include "BooleanAnd.hpp"
#include "BooleanXor.hpp"
#include "Box.hpp"
#include "Cone.hpp"
#include "Cube.hpp"
#include "Disk.hpp"
#include "Line.hpp"
#include "Square.hpp"
using namespace std;


/** @brief %Factory for creating geometry-related objects.
 * 
 * @ingroup factories
 */
class GeometryFactory {
public:
	static void install();
	static Node* createBoolean(const Tag &tag);
	static Node* createBox(const Tag &tag);
	static Node* createCone(const Tag &tag);
	static Node* createCube(const Tag &tag);
	static Node* createDisk(const Tag &tag);
	static Node* createLine(const Tag &tag);
	static Node* createSquare(const Tag &tag);
private:
	static bool installed;
};


#endif
