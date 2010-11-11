/*
 * GeometryFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GeometryFactory.hpp"
bool GeometryFactory::installed=false;

void GeometryFactory::install() {
	
	// Check if already called
	if (installed)
		return;
	installed = true;
	
	// Tags
	Factory::install("boolean", &createBoolean);
	Factory::install("box", &createBox);
	Factory::install("cone", &createCone);
	Factory::install("cube", &createCube);
	Factory::install("disk", &createDisk);
	Factory::install("line", &createLine);
	Factory::install("square", &createSquare);
}

/** @throw NodeException if boolean operation not supported. */
Node* GeometryFactory::createBoolean(const Tag &tag) {
	
	string operation;
	
	tag.get("operation", operation);
	if (operation == "and") {
		return new BooleanAnd(tag);
	} else if (operation == "xor") {
		return new BooleanXor(tag);
	} else {
		BasicException e;
		e << "[GeometryFactory] Boolean operation not supported.";
		throw e;
	}
}

Node* GeometryFactory::createBox(const Tag &tag) {return new Box(tag);}

Node* GeometryFactory::createCone(const Tag &tag) {return new Cone(tag);}

Node* GeometryFactory::createCube(const Tag &tag) {return new Cube(tag);}

Node* GeometryFactory::createDisk(const Tag &tag) {return new Disk(tag);}

Node* GeometryFactory::createLine(const Tag &tag) {return new Line(tag);}

Node* GeometryFactory::createSquare(const Tag &tag) {return new Square(tag);}

