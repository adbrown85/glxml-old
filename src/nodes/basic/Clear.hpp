/*
 * Clear.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_CLEAR_HPP
#define GLXML_CLEAR_HPP
#include "glxml_common.h"
#include "Node.hpp"
#include "NodeInterfaces.hpp"
using namespace std;

/** @brief %Clear a framebuffer.
 * 
 * Although actually one of the most mundane operations, most of the time clear 
 * is not directly needed by the user because the display loop will it do 
 * automatically.  However, when working with framebuffer objects, it does 
 * sometimes become necessary when doing multiple passes.
 * 
 * <b>OpenGL Functions</b>
 *   - glClear
 *   - glClearColor
 *   - glClearDepth
 * 
 * @ingroup advanced
 */
class Clear : public Node, public Applicable {
public:
	Clear(const Tag &tag);
	virtual string toString() const;
// Traversal
	virtual void apply();
	virtual void remove() {}
private:
	GLbitfield mask;
	bool hasColor, hasDepth;
	float depth;
	Vec4 color;
};

#endif
