/*
 * Shader.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Shader.hpp"

/** Creates a new %Shader from an XML tag.
 * 
 * @param tag XML tag with "type" and "file" attributes.
 */
Shader::Shader(const Tag &tag) : Node(tag), Fileable(tag) {
	
	// Initialize attributes
	handle = 0;
	tag.get("type", type, false);
	
	// Check filename
	if (!hasFilename()) {
		NodeException e(getTag());
		e << "[Shader] Must have file attribute.";
		throw e;
	}
	
	// Check type or try to guess
	if (!type.empty()) {
		type = Text::toLower(type);
	} else {
		guessType();
	}
}

/** Loads the shader and attaches it to the program.
 * 
 * @throw NodeException if program cannot be found.
 * @throw NodeException from ShaderFactory::create().
 */
void Shader::associate() {
	
	Program *program;
	GLenum typeEnum;
	
	// Find program
	program = Scout<Program>::locate(parent);
	if (program == NULL) {
		NodeException e(getTag());
		e << "[Shader] Cannot find program to attach to.";
		throw e;
	}
	
	// Determine type
	if (type == "fragment") {
		typeEnum = GL_FRAGMENT_SHADER;
	} else if (type == "vertex") {
		typeEnum = GL_VERTEX_SHADER;
	} else {
		NodeException e(getTag());
		e << "[Shader] Type must be 'vertex' or 'fragment'.";
		throw e;
	}
	
	// Load and attach
	handle = ShaderFactory::create(typeEnum, getFilename());
	glAttachShader(program->getHandle(), handle);
}

/** Guesses the shader's type by the file's extension.
 * 
 * @throw NodeException if extension not recognized as a type.
 */
void Shader::guessType() {
	
	string extension;
	
	extension = Text::toLower(Path::getExtension(getFilename()));
	if (extension == "frag") {
		type = "fragment";
	} else if (extension == "vert") {
		type = "vertex";
	} else {
		NodeException e(getTag());
		e << "[Shader] Extension '" << extension << "' not a valid type.";
		throw e;
	}
}

/** Forms a string from the object's attributes. */
string Shader::toString() const {
	
	ostringstream stream;
	
	// Build string
	stream << Node::toString();
	stream << Fileable::toString();
	stream << " type='" << type << "'"
	       << " handle='" << handle << "'";
	return stream.str();
}
