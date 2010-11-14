/*
 * Uniform.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_UNIFORM_HPP
#define GLXML_UNIFORM_HPP
#include "glxml_common.h"
#include <iomanip>
#include <set>
#include <edo/Tag.hpp>
#include <edo/Text.hpp>
#include <gloop/Matrix.hpp>
#include "Node.hpp"
#include "NodeInterfaces.hpp"
#include "Program.hpp"
#include "Texture.hpp"
#include "Scout.hpp"
using namespace std;

/** @brief Abstract base class for GLSL uniform variables.
 * 
 * @ingroup shading
 */
class Uniform : public Node,
                public Applicable, public Suppressable, public Nameable {
public:
	Uniform(const Tag &tag);
	virtual string toString() const;
// Preparation
	virtual void verify();
	virtual void associate();
	virtual void finalize();
	virtual bool wasSuppressed() const;
// Traversal
	virtual void apply() = 0;
	virtual void remove() {};
// Getters and setters
	string getLink() const;
	bool hasLink() const;
	GLint getLocation() const;
	bool hasLocation() const;
	void setLocation(GLint location);
	Program* getProgram() const;
	void setProgram(Program *program);
	string getType() const;
// Utilities
	static bool isMatrixType(GLenum type);
private:
	GLint location;
	Program *program;
	string link, type;
};

inline string Uniform::getLink() const {return link;}
inline bool Uniform::hasLink() const {return !link.empty();}
inline GLint Uniform::getLocation() const {return location;}
inline bool Uniform::hasLocation() const {return location != -1;}
inline void Uniform::setLocation(GLint location) {this->location = location;}
inline Program* Uniform::getProgram() const {return program;}
inline void Uniform::setProgram(Program *program) {this->program = program;}
inline string Uniform::getType() const {return type;}

#endif
