/*
 * Branch.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_BRANCH_HPP
#define GLXML_BRANCH_HPP
#include "glxml_common.h"
#include "Node.hpp"
#include "NodeInterfaces.hpp"
using namespace std;

/** @brief One possible result of a conditional.
 * 
 * @ingroup organize
 */
class Branch : public Node, public Nameable {
public:
	Branch(const Tag &tag);
	virtual string toString() const;
// Traversal
	virtual bool areChildrenTraversable() const;
// Getters and setters
	virtual void setFollow(bool follow);
private:
	bool follow;
};

/** @return True if the branch should be followed. */
inline bool Branch::areChildrenTraversable() const {return follow;}

/** Determine whether the branch should be followed. */
inline void Branch::setFollow(bool follow) {this->follow = follow;}

#endif
