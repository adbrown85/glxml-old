/*
 * Uniform.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Uniform.hpp"

/** Initialize attributes.
 * 
 * @throw NodeException if name not specified.
 */
Uniform::Uniform(const Tag &tag) : Node(tag), Nameable(tag) {
	
	// From tag
	tag.get("type", type);
	tag.get("link", link, false, false);
	
	// Other
	program = NULL;
	location = 0;
}

/** Validates the node was created correctly. */
void Uniform::verify() {
	
	// Check
	if (!hasName()) {
		NodeException e(getTag());
		e << "[Uniform] Must have name.";
		throw e;
	}
}

/** Finds a Program node that is an ancestor of this node.
 * 
 * @throw NodeException if program cannot be found.
 */
void Uniform::associate() {
	
	// Look for a Program ancestor
	program = Scout<Program>::locate(parent);
	if (program == NULL) {
		NodeException e(tag);
		e << "[Uniform] Program for '" << getName() << "' cannot be found.";
		throw e;
	}
}

/** Finds the variable's location in the program.
 * 
 * @throw NodeException if location for uniform cannot be found
 */
void Uniform::finalize() {
	
	// Look up location
	location = glGetUniformLocation(program->getHandle(), getName().c_str());
	if (location == -1 && !isSuppressed()) {
		NodeException e(tag);
		e << "[Uniform] Location for '" << getName() << "' cannot be found.";
		throw e;
	}
}

/** @return True if the type is @e mat2, @e mat3, or @e mat3. */
bool Uniform::isMatrixType(GLenum type) {
	
	switch (type) {
	case GL_FLOAT_MAT2:
	case GL_FLOAT_MAT3:
	case GL_FLOAT_MAT4:
		return true;
	default:
		return false;
	}
}

/** Forms a string from the object's attributes. */
string Uniform::toString() const {
	
	ostringstream stream;
	
	// Build string
	stream << Node::toString();
	stream << Nameable::toString();
	stream << " location='" << location << "'";
	if (hasLink()) {
		stream << " link='" << link << "'";
	}
	return stream.str();
}

/** @return True if the uniform was suppressed. */
bool Uniform::wasSuppressed() const {
	
	return (location == -1) && isSuppressed();
}
