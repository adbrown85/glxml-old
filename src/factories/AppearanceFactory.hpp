/*
 * AppearanceFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef APPEARANCEFACTORY_HPP
#define APPEARANCEFACTORY_HPP
#include "glxml_common.h"
#include "Factory.hpp"
#include "Blend.hpp"
#include "Clear.hpp"
#include "Cull.hpp"
#include "Depth.hpp"
#include "Light.hpp"
#include "Shadow.hpp"
#include "Texture.hpp"
#include "Wireframe.hpp"
using namespace std;


/** @brief %Factory for creating nodes that modify appearance.
 * 
 * @ingroup factories
 */
class AppearanceFactory : public Factory {
public:
	static void install();
	static Node* createBlend(const Tag &tag);
	static Node* createClear(const Tag &tag);
	static Node* createCull(const Tag &tag);
	static Node* createDepth(const Tag &tag);
	static Node* createLight(const Tag &tag);
	static Node* createShadow(const Tag &tag);
	static Node* createTexture(const Tag &tag);
	static Node* createWireframe(const Tag &tag);
private:
	static bool installed;
};


#endif
