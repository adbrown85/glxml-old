/*
 * Cull.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_CULL_HPP
#define GLXML_CULL_HPP
#include "glxml_common.h"
#include "Node.hpp"
#include "NodeInterfaces.hpp"
using namespace std;

/** @brief Removes back or front-facing polygons.
 * @ingroup advanced
 */
class Cull : public Node, public Applicable {
public:
	Cull(const Tag &tag);
	string toString() const;
// Traversal
	void apply();
	void remove();
private:
	bool enabled;
	GLenum faces;
	string facesString;
};

#endif
