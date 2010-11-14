/*
 * Resources.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_RESOURCES_HPP
#define GLXML_RESOURCES_HPP
#include "glxml_common.h"
using namespace std;

/** @brief Utility for retrieving resources.
 * @ingroup gui
 */
class Resources {
public:
	static string get(const string &filename);
};

#endif
