/*
 * Sort.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_SORT_HPP
#define GLXML_SORT_HPP
#include "glxml_common.h"
#include <algorithm>                    // For sort
#include <gloop/State.hpp>
#include "Node.hpp"
#include "Translate.hpp"
using namespace std;

/** @brief Sorts translate children based on their depth.
 * 
 * @ingroup organize
 */
class Sort : public Node, public Applicable {
public:
	Sort(const Tag &tag) : Node(tag) {}
// Preparation
	virtual void associate();
// Traversal
	virtual void apply();
	virtual void remove() {}
private:
	list<Translate*> translates;
	Matrix view;
	Vec4 position;
};

#endif
