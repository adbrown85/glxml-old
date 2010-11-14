/*
 * Program.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_PROGRAM_HPP
#define GLXML_PROGRAM_HPP
#include "glxml_common.h"
#include <cstring>
#include <vector>
#include "Node.hpp"
#include "NodeInterfaces.hpp"
#include "NodeEvent.hpp"
#include "Scout.hpp"
using namespace std;

/** @brief GLSL program that %Shaders and %Uniform variables are connected to.
 * @ingroup basic
 */
class Program : public Node, public Applicable {
public:
	Program(const Tag& tag);
	virtual string toString() const;
	virtual void addListener(NodeListener *listener, int type);
// Preparation
	virtual void associate();
	virtual void finalize();
// Traversal 
	virtual void apply();
	virtual void remove();
// Getters and setters
	virtual void log() const;
	static Program* getCurrent();
	virtual GLuint getHandle() const;
private:
	GLint linked;
	GLuint handle;
	static Program* current;
	NodeNotifier notifier;
	Program *previous;
};

/** @return Integer OpenGL identifies the program with. */
inline GLuint Program::getHandle() const {return handle;}

/** @return Pointer to the active program */
inline Program* Program::getCurrent() {return current;}

#endif
