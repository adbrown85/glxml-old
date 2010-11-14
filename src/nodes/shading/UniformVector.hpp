/*
 * UniformVector.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_UNIFORMVECTOR_HPP
#define GLXML_UNIFORMVECTOR_HPP
#include "Uniform.hpp"
using namespace std;


/** @brief Container for GLSL vector uniform variables.
 * @ingroup basic
 */
class UniformVector : public Uniform, public NodeNotifier {
public:
	UniformVector(const Tag &tag);
	virtual string toString() const;
// Preparation
	virtual void associate();
// Traversal
	virtual void apply();
private:
	GLfloat value[4];
	GLint size;
	Transformable *transformable;
};


#endif
