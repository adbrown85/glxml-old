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
 * @ingroup basic
 */
class UniformFloat : public Uniform {
public:
	UniformFloat(const Tag &tag);
	virtual void apply();
	virtual void associate();
	virtual bool setAttribute(pair<string,string> attribute);
	virtual string toString() const;
private:
	GLfloat value;
};


#endif
