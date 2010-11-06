/*
 * NodeException.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef NODEEXCEPTION_HPP
#define NODEEXCEPTION_HPP
#include "glxml_common.h"
#include <edo/BasicException.hpp>
#include <edo/Tag.hpp>
using namespace std;


/** @brief %Exception thrown from a node.
 * 
 * Automatically initializes the exception's message to the tag's location.
 * 
 * @ingroup scene
 */
class NodeException : public BasicException {
public:
	NodeException(const Tag &tag);
};


#endif
