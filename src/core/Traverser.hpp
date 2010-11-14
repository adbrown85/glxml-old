/*
 * Traverser.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_TRAVERSER_HPP
#define GLXML_TRAVERSER_HPP
#include "glxml_common.h"
#include <edo/BasicException.hpp>
#include "Node.hpp"
#include "NodeInterfaces.hpp"
#include "Scene.hpp"
using namespace std;


/** @brief Utility to walk through nodes.
 * @ingroup scene
 */
class Traverser {
public:
	Traverser(Scene *scene);
	virtual ~Traverser() {}
	virtual void start();
protected:
	virtual void onApplicable(Node *node, Applicable *applicable);
	virtual void onDrawable(Node *node, Drawable *drawable);
	void traverseChildren(Node *node);
	void traverseNode(Node *node);
private:
	Scene *scene;
};


#endif
