/*
 * OffscreenFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "OffscreenFactory.hpp"
bool OffscreenFactory::installed=false;

void OffscreenFactory::install() {
	
	// Check if already called
	if (installed)
		return;
	installed = true;
	
	// Tags
	Factory::install("bind", &createBind);
	Factory::install("framebuffer", &createFramebuffer);
	Factory::install("fullscreen", &createFullscreen);
	Factory::install("outputs", &createOutputs);
	Factory::install("renderbuffer", &createRenderbuffer);
	Factory::install("screen", &createScreen);
	Factory::install("target", &createTarget);
}

Node* OffscreenFactory::createBind(const Tag &t) {
	return new Bind(t);
}

Node* OffscreenFactory::createFramebuffer(const Tag &t) {
	return new Framebuffer(t);
}

Node* OffscreenFactory::createFullscreen(const Tag &t) {
	return new Fullscreen(t);
}

Node* OffscreenFactory::createOutputs(const Tag &t) {
	return new Outputs(t);
}

Node* OffscreenFactory::createRenderbuffer(const Tag &t) {
	return new Renderbuffer(t);
}

Node* OffscreenFactory::createScreen(const Tag &t) {
	return new Screen(t);
}

Node* OffscreenFactory::createTarget(const Tag &t) {
	return new Target(t);
}

