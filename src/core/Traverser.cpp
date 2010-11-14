/*
 * Traverser.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Traverser.hpp"

Traverser::Traverser(Scene *scene) {
	
	this->scene = scene;
}

void Traverser::onApplicable(Node *node, Applicable *applicable) {
	
	// Apply, do children, then remove
	applicable->apply();
	traverseChildren(node);
	applicable->remove();
}

void Traverser::onDrawable(Node *node, Drawable *drawable) {
	
	// Check if excluded
	if (drawable->isExcluded()) {
		return;
	}
	
	// Do children then draw it
	traverseChildren(node);
	if (drawable->isVisible())
		drawable->draw();
}

void Traverser::start() {
	
	traverseNode(scene->getRoot());
}

/** Recursively traverses the children of a node.
 * 
 * This functionality is implemented as a separate function, as opposed to 
 * incorporating it directly into <i>paint</i>, because some nodes need to 
 * traverse their children at different times.
 * 
 * @param node Pointer to the parent node.
 */
void Traverser::traverseChildren(Node *node) {
	
	Node::iterator it;
	
	// Stop if sealed
	if (!node->areChildrenTraversable())
		return;
	
	// Traverse each child
	for (it=node->begin(); it!=node->end(); ++it) {
		traverseNode(*it);
	}
}

/** Recursively traverses a node.
 * 
 * Automatically takes care of performing different actions depending on what 
 * type of interfaces the node supports.
 * 
 * @param node Pointer to the Node to traverse.
 */
void Traverser::traverseNode(Node *node) {
	
	Applicable *applicable;
	Drawable *drawable;
	
	// Determine if node is applicable or drawable
	if ((applicable = dynamic_cast<Applicable*>(node))) {
		onApplicable(node, applicable);
	} else if ((drawable = dynamic_cast<Drawable*>(node))) {
		onDrawable(node, drawable);
	} else {
		traverseChildren(node);
	}
}
