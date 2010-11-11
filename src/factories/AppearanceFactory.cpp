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
	Factory::install("light", &createLight);
	Factory::install("shadow", &createShadow);
	Factory::install("wireframe", &createWireframe);
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

Node* AppearanceFactory::createLight(const Tag &t) {
	return new Light(t);
}

Node* AppearanceFactory::createShadow(const Tag &t) {
	return new Shadow(t);
}

Node* AppearanceFactory::createTexture(const Tag &tag) {
	return new Texture(tag);
}

Node* AppearanceFactory::createWireframe(const Tag &t) {
	return new Wireframe(t);
}
