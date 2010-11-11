/*
 * TransformFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "TransformFactory.hpp"
bool TransformFactory::installed=false;

void TransformFactory::install() {
	
	// Check if already called
	if (installed)
		return;
	installed = true;
	
	// Tags
	Factory::install("rotate", &createRotate);
	Factory::install("scale", &createScale);
	Factory::install("translate", &createTranslate);
}

Node* TransformFactory::createRotate(const Tag &tag) {
	return new Rotate(tag);
}

Node* TransformFactory::createScale(const Tag &tag) {
	return new Scale(tag);
}

Node* TransformFactory::createTranslate(const Tag &t) {
	return new Translate(t);
}

