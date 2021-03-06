/*
 * UniformSampler.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "UniformSampler.hpp"

/** Creates a new uniform sampler. */
UniformSampler::UniformSampler(const Tag &tag) : Uniform(tag) {

}

/** Sets the value in the program. */
void UniformSampler::apply() {
	
	if (hasLocation())
		glUniform1i(getLocation(), value);
}

/** Finds the correct texture and then sets @e value to its unit. */
void UniformSampler::associate() {
	
	Texture *texture;
	
	// Program
	Uniform::associate();
	
	// Get unit of linked texture
	texture = Scout<Texture>::locate(getParent(), getLink());
	if (texture == NULL) {
		NodeException e(tag);
		e << "[UniformSampler] Could not find texture '" << getLink() << "'";
		throw e;
	}
	value = texture->getUnit();
}

/** @return String comprised of the node's attributes. */
string UniformSampler::toString() const {
	
	ostringstream stream;
	
	stream << Uniform::toString();
	stream << " value='" << value << "'";
	return stream.str();
}

/** @throw NodeException if @e link attribute is not specified. */
void UniformSampler::verify() {
	
	Uniform::verify();
	
	if (!hasLink()) {
		NodeException e(getTag());
		e << "[UniformSampler] Sampler types require link to texture.";
		throw e;
	}
}
