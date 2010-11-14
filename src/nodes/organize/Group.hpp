/*
 * Group.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_GROUP_HPP
#define GLXML_GROUP_HPP
#include "glxml_common.h"
#include "Node.hpp"
#include "NodeInterfaces.hpp"
using namespace std;

/** @brief Collection of nodes.
 * 
 * @ingroup organize
 */
class Group : public Node, public Nameable {
public:
	Group(const Tag &tag);
	virtual string toString() const;
// Preparation
	virtual void verify();
// Traversal
	virtual bool areChildrenTraversable() const;
	virtual bool areChildrenPreparable() const;
};

inline bool Group::areChildrenTraversable() const {return false;}
inline bool Group::areChildrenPreparable() const {return false;}

#endif
