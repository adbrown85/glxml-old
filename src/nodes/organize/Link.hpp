/*
 * Link.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_LINK_HPP
#define GLXML_LINK_HPP
#include "glxml_common.h"
#include "Group.hpp"
#include "Scout.hpp"
using namespace std;

/** @brief Simple connection to a %Group.
 * 
 * @ingroup organize
 */
class Link : public Node {
public:
	Link(const Tag &tag);
	virtual string toString() const;
	virtual void establish();
	virtual void relink();
// Traversal
	virtual bool areChildrenDestroyable() const;
	virtual bool areChildrenPrintable() const;
// Getters and setters
	virtual void setTo(const string &to);
private:
	Group *group;
	string to;
};

inline bool Link::areChildrenDestroyable() const {return false;}
inline bool Link::areChildrenPrintable() const {return false;}
inline void Link::setTo(const string &to) {this->to = to;}

#endif
