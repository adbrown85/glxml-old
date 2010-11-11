/*
 * ShaderFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SHADERFACTORY_HPP
#define SHADERFACTORY_HPP
#include "glxml_common.h"
#include "Factory.hpp"
#include "Program.hpp"
#include "Shader.hpp"
#include "UniformInt.hpp"
#include "UniformFloat.hpp"
#include "UniformFloatArray.hpp"
#include "UniformMatrix.hpp"
#include "UniformSampler.hpp"
#include "UniformVector.hpp"
using namespace std;


/** @brief %Factory for creating nodes related to shaders.
 * 
 * @ingroup factories
 */
class ShaderFactory {
public:
	static void install();
	static Node* createProgram(const Tag &tag);
	static Node* createShader(const Tag &tag);
	static Node* createUniform(const Tag &tag);
private:
	enum kind_t {INT, FLOAT, FLOAT_ARRAY, MATRIX, SAMPLER, VECTOR};
	static bool installed;
	static map<string,kind_t> kinds;
};


#endif
