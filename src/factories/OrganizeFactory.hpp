/*
 * OrganizeFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_ORGANIZEFACTORY_HPP
#define GLXML_ORGANIZEFACTORY_HPP
#include "glxml_common.h"
#include "Factory.hpp"
#include "Branch.hpp"
#include "Choose.hpp"
#include "Clone.hpp"
#include "Group.hpp"
#include "Instance.hpp"
#include "Placeholder.hpp"
#include "Replacement.hpp"
#include "Replica.hpp"
#include "Sort.hpp"
using namespace std;

/** @brief %Factory for creating nodes that alter the structure of the scene.
 * 
 * @ingroup advanced
 */
class OrganizeFactory {
public:
	static void install();
	static Node* createBranch(const Tag &tag);
	static Node* createChoose(const Tag &tag);
	static Node* createClone(const Tag &tag);
	static Node* createGroup(const Tag &tag);
	static Node* createInstance(const Tag &tag);
	static Node* createPlaceholder(const Tag &tag);
	static Node* createReplacement(const Tag &tag);
	static Node* createReplica(const Tag &tag);
	static Node* createSort(const Tag &tag);
private:
	static bool installed;
};

#endif
