/*
 * Instance.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_INSTANCE_HPP
#define GLXML_INSTANCE_HPP
#include "glxml_common.h"
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
 * @ingroup organize
 */
class Instance : public Node, public Applicable {
public:
	Instance(const Tag &tag);
	virtual string toString() const;
// Traversal
	virtual void apply();
	virtual void remove();
	virtual bool areChildrenSelectable() const;
// Preparation
	virtual void associate();
	virtual void finalize();
// Getters and setters
	virtual string getOf() const;
	virtual void setOf(const string &of);
protected:
	void findExclusions();
	Link* getLink();
private:
	string of, only;
	list<Shape*> exclusions;
	bool selectable;
	Link *link;
};

inline bool Instance::areChildrenSelectable() const {return selectable;}
inline Link* Instance::getLink() {return link;}
inline string Instance::getOf() const {return of;}
inline void Instance::setOf(const string &of) {this->of = of; link->setTo(of);}

#endif
