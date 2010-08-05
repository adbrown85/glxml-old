/*
 * Instance.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef INSTANCE_HPP
#define INSTANCE_HPP
#include "common.h"
#include "Link.hpp"
#include "Shape.hpp"
using namespace std;


/** @brief Simple reuse of a group.
 * 
 * @warning Should only be used when the group itself includes the only program 
 * needed by the nodes in the group, or if all instances will be under the 
 * same program.  Otherwise, use Clone or Replica.
 * 
 * @see Clone
 * @see Replica
 * 
 * @ingroup basic
 */
class Instance : public Node, public Applicable {
public:
	Instance(const Tag &tag);
	virtual void apply();
	virtual bool areChildrenSelectable() const;
	virtual void associate();
	virtual void finalize();
	virtual void remove();
	virtual string toString() const;
protected:
	void findExclusions();
	Link* getLink();
private:
	string only;
	list<Shape*> exclusions;
	bool selectable;
	Link *link;
	string of;
};

inline bool Instance::areChildrenSelectable() const {return selectable;}
inline Link* Instance::getLink() {return link;}


#endif
