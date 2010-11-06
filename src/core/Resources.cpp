/*
 * Resources.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Resources.hpp"


string Resources::get(const string &filename) {
	
	ostringstream stream;
	
	stream << GLXML_DATA_DIR << '/' << filename;
	return stream.str();
}

