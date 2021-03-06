/*
 * Transform.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_TRANSFORM_HPP
#define GLXML_TRANSFORM_HPP
#include "glxml_common.h"
#include <gloop/Matrix.hpp>
#include <gloop/State.hpp>
#include "Node.hpp"
#include "NodeInterfaces.hpp"
#include "NodeEvent.hpp"


/** @brief Operation that changes size, position, or orientation of objects.
 * 
 * @ingroup transform
 */
class Transform : public Node,
                  public Applicable, public NodeNotifier {
public:
	Transform(const Tag &tag) : Node(tag) {}
// Traversal
	virtual void apply() = 0;
	virtual void remove() = 0;
	virtual void applyTo(Matrix &matrix) = 0;
// Utilities
	static void search(Node *node, list<Transform*> &L);
	static void findAll(Node *node, list<Transform*> &L);
};


#endif
