/*
 * UniformSampler.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef UNIFORMSAMPLER_HPP
#define UNIFORMSAMPLER_HPP
#include "Uniform.hpp"
using namespace std;


/** @brief Container for GLSL sampler uniform variables.
 * @ingroup basic
 */
class UniformSampler : public Uniform {
public:
	UniformSampler(const Tag &tag);
	virtual void associate();
	virtual void apply();
	virtual string toString() const;
	virtual void verify();
public:    // Accessors
	virtual GLint getValue() const;
private:   // Data
	GLint value;
};

/** @return texture unit the sampler points to. */
inline GLint UniformSampler::getValue() const {return value;}


#endif