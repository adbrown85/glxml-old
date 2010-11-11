/*
 * ShaderFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ShaderFactory.hpp"
bool ShaderFactory::installed=false;
map<string,ShaderFactory::kind_t> ShaderFactory::kinds;


void ShaderFactory::install() {
	
	// Check if already called
	if (installed)
		return;
	installed = true;
	
	// Tags
	Factory::install("program", &createProgram);
	Factory::install("shader", &createShader);
	Factory::install("uniform", &createUniform);
	
	// Map uniform types back to kinds
	kinds["int"] = INT;
	kinds["float"] = FLOAT;
	kinds["float[]"] = FLOAT_ARRAY;
	kinds["mat3"] = MATRIX;
	kinds["mat4"] = MATRIX;
	kinds["sampler1d"] = SAMPLER;
	kinds["sampler2d"] = SAMPLER;
	kinds["sampler3d"] = SAMPLER;
	kinds["usampler1d"] = SAMPLER;
	kinds["usampler2d"] = SAMPLER;
	kinds["usampler3d"] = SAMPLER;
	kinds["sampler2dshadow"] = SAMPLER;
	kinds["vec3"] = VECTOR;
	kinds["vec4"] = VECTOR;
}

Node* ShaderFactory::createProgram(const Tag &tag) {return new Program(tag);}

Node* ShaderFactory::createShader(const Tag &tag) {return new Shader(tag);}

Node* ShaderFactory::createUniform(const Tag &tag) {
	
	kind_t kind;
	map<string,kind_t>::iterator it;
	string type;
	
	// Get type
	tag.get("type", type);
	it = kinds.find(type);
	if (it == kinds.end()) {
		BasicException e(tag);
		e << "[ShaderFactory] Uniform type '" << type << "' not supported.";
		throw e;
	}
	
	// Create based on kind
	kind = it->second;
	switch (kind) {
	case INT:
		return new UniformInt(tag);
	case FLOAT:
		return new UniformFloat(tag);
	case FLOAT_ARRAY:
		return new UniformFloatArray(tag);
	case MATRIX:
		return new UniformMatrix(tag);
	case SAMPLER:
		return new UniformSampler(tag);
	case VECTOR:
		return new UniformVector(tag);
	default:
		NodeException e(tag);
		e << "[BasicFactory] Unexpected error making uniform.";
		throw e;
	}
}

