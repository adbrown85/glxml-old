/*
 * UniformFloat.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_UNIFORMFLOAT_HPP
#define GLXML_UNIFORMFLOAT_HPP
#include "Uniform.hpp"
using namespace std;

/** @brief Container for GLSL floating-point uniform variables.
 * 
 * @ingroup shading
 */
class UniformFloat : public Uniform {
public:
	UniformFloat(const Tag &tag);
	virtual string toString() const;
// Preparation
	virtual void associate();
// Traversal
	virtual void apply();
// Getters and setters
	virtual bool setAttribute(pair<string,string> attribute);
private:
	GLfloat value;
};

#endif
