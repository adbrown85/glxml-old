/*
 * UniformSampler.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_UNIFORMSAMPLER_HPP
#define GLXML_UNIFORMSAMPLER_HPP
#include "Uniform.hpp"
using namespace std;

/** @brief Container for GLSL sampler uniform variables.
 * 
 * @ingroup shading
 */
class UniformSampler : public Uniform {
public:
	UniformSampler(const Tag &tag);
	virtual string toString() const;
// Preparation
	virtual void verify();
	virtual void associate();
// Traversal
	virtual void apply();
// Getters and setters
	virtual GLint getValue() const;
private:
	GLint value;
};

/** @return texture unit the sampler points to. */
inline GLint UniformSampler::getValue() const {return value;}

#endif
