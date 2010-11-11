/*
 * AppearanceFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "AppearanceFactory.hpp"
bool AppearanceFactory::installed=false;

void AppearanceFactory::install() {
	
	// Check if already called
	if (installed)
		return;
	installed = true;
	
	// Tags
	Factory::install("blend", &createBlend);
	Factory::install("clear", &createClear);
	Factory::install("cull", &createCull);
	Factory::install("depth", &createDepth);
}

Node* AppearanceFactory::createBlend(const Tag &t) {
	return new Blend(t);
}

Node* AppearanceFactory::createClear(const Tag &t) {
	return new Clear(t);
}

Node* AppearanceFactory::createCull(const Tag &tag) {
	return new Cull(tag);
}

Node* AppearanceFactory::createDepth(const Tag &t) {
	return new Depth(t);
}
