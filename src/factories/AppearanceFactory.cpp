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
	Factory::install("light", &createLight);
	Factory::install("shadow", &createShadow);
	Factory::install("texture", &createTexture);
	Factory::install("wireframe", &createWireframe);
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
