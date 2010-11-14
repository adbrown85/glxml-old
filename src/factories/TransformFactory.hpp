/*
 * TransformFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_TRANSFORMFACTORY_HPP
#define GLXML_TRANSFORMFACTORY_HPP
#include "glxml_common.h"
#include "Factory.hpp"
#include "Rotate.hpp"
#include "Scale.hpp"
#include "Translate.hpp"
using namespace std;

/** @brief %Factory for creating nodes that perform transformations.
 * 
 * @ingroup factories
 */
class TransformFactory {
public:
	static void install();
	static Node* createRotate(const Tag &tag);
	static Node* createScale(const Tag &tag);
	static Node* createTranslate(const Tag &tag);
private:
	static bool installed;
};

#endif
