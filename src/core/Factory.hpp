/*
 * Factory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef FACTORY_HPP
#define FACTORY_HPP
#include "glxml_common.h"
#include <vector>
#include <edo/Parser.hpp>
#include <edo/Path.hpp>
#include <edo/Tag.hpp>
#include "Node.hpp"
#include "NodeException.hpp"
using namespace std;


/* Creator function. */
typedef Node* (*creator_t)(const Tag &tag);


/** @brief Creates nodes from XML tags.
 * @ingroup scene
 */
class Factory {
public:
	static void check(const Tag &tag);
	static Node* copy(Node *node, int line);
	static Node* create(const Tag &tag, const string &xmlFilename="");
	static Node* create(const string &text, const string &xmlFilename="");
	static void error(const Tag &tag);
	static void install(const string &name, creator_t creator);
	static bool isInstalled(const string &name);
protected:
	static Tag filter(Tag tag, const string &xmlFilename);
private:
	static map<string,creator_t> creators;
};


#endif
