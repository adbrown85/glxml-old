/*
 * OffscreenFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_OFFSCREENFACTORY_HPP
#define GLXML_OFFSCREENFACTORY_HPP
#include "glxml_common.h"
#include "Factory.hpp"
#include "Bind.hpp"
#include "Framebuffer.hpp"
#include "Fullscreen.hpp"
#include "Outputs.hpp"
#include "Renderbuffer.hpp"
#include "Screen.hpp"
#include "Target.hpp"
using namespace std;


/** @brief %Factory for creating framebuffer-related objects.
 * 
 * @ingroup factories
 */
class OffscreenFactory {
public:
	static void install();
	static Node* createBind(const Tag &tag);
	static Node* createFramebuffer(const Tag &tag);
	static Node* createFullscreen(const Tag &tag);
	static Node* createOutputs(const Tag &tag);
	static Node* createRenderbuffer(const Tag &tag);
	static Node* createScreen(const Tag &tag);
	static Node* createTarget(const Tag &tag);
private:
	static bool installed;
};


#endif
