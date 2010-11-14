/*
 * Placeholder.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_PLACEHOLDER_HPP
#define GLXML_PLACEHOLDER_HPP
#include "glxml_common.h"
#include "Node.hpp"
#include "NodeInterfaces.hpp"
#include "Group.hpp"
using namespace std;

/** @brief %Node that can be replaced in groups.
 * 
 * @ingroup organize
 */
class Placeholder : public Node, public Nameable {
public:
	Placeholder(const Tag &tag);
	virtual string toString() const;
	virtual void check();
	virtual void clear();
	virtual void mimic(Node *node);
// Traversal
	virtual bool areChildrenDestroyable() const;
};

/** Makes sure any leftover children aren't destroyed twice. */
inline bool Placeholder::areChildrenDestroyable() const {return false;}

/** Clears the placeholder's children. */
inline void Placeholder::clear() {children.clear();}

#endif
