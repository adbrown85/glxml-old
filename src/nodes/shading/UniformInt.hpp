/*
 * UniformInt.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_UNIFORMINT_HPP
#define GLXML_UNIFORMINT_HPP
#include "Uniform.hpp"
using namespace std;

/** @brief Container for GLSL integer uniform variables.
 * @ingroup basic
 */
class UniformInt : public Uniform {
public:
	UniformInt(const Tag &tag);
	virtual string toString() const;
// Traversal
	virtual void apply();
// Getters and setters
	virtual void setValue(GLint value);
private:
	GLint value;
};

inline void UniformInt::setValue(GLint value) {this->value = value;}

#endif
