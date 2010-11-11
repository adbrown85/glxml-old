/*
 * BasicFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "BasicFactory.hpp"
bool BasicFactory::installed=false;

void BasicFactory::install() {
	
	// Check if already called
	if (installed)
		return;
	installed = true;
	
	// Tags
	Factory::install("blend", &createBlend);
	Factory::install("clear", &createClear);
	Factory::install("cull", &createCull);
	Factory::install("depth", &createDepth);
	Factory::install("wireframe", &createWireframe);
}

Node* BasicFactory::createBlend(const Tag &t) {
	return new Blend(t);
}

Node* BasicFactory::createClear(const Tag &t) {
	return new Clear(t);
}

Node* BasicFactory::createCull(const Tag &tag) {
	return new Cull(tag);
}

Node* BasicFactory::createDepth(const Tag &t) {
	return new Depth(t);
}

Node* BasicFactory::createWireframe(const Tag &t) {
	return new Wireframe(t);
}
