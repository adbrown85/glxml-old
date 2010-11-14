/*
 * BasicFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_BASICFACTORY_HPP
#define GLXML_BASICFACTORY_HPP
#include "glxml_common.h"
#include "Factory.hpp"
#include "Blend.hpp"
#include "Clear.hpp"
#include "Cull.hpp"
#include "Depth.hpp"
#include "Wireframe.hpp"
using namespace std;

/** @brief %Factory for creating nodes of basic OpenGL functions.
 * 
 * @ingroup factories
 */
class BasicFactory : public Factory {
public:
	static void install();
	static Node* createBlend(const Tag &tag);
	static Node* createClear(const Tag &tag);
	static Node* createCull(const Tag &tag);
	static Node* createDepth(const Tag &tag);
	static Node* createWireframe(const Tag &tag);
private:
	static bool installed;
};

#endif
