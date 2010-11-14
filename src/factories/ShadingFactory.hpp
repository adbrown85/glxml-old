/*
 * ShadingFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_SHADINGFACTORY_HPP
#define GLXML_SHADINGFACTORY_HPP
#include "glxml_common.h"
#include "Factory.hpp"
#include "Light.hpp"
#include "Program.hpp"
#include "Shader.hpp"
#include "Shadow.hpp"
#include "Texture.hpp"
#include "UniformInt.hpp"
#include "UniformFloat.hpp"
#include "UniformFloatArray.hpp"
#include "UniformMatrix.hpp"
#include "UniformSampler.hpp"
#include "UniformVector.hpp"
using namespace std;

/** @brief %Factory for creating nodes related to shading.
 * 
 * @ingroup factories
 */
class ShadingFactory {
public:
	static void install();
	static Node* createLight(const Tag &tag);
	static Node* createProgram(const Tag &tag);
	static Node* createShader(const Tag &tag);
	static Node* createShadow(const Tag &tag);
	static Node* createTexture(const Tag &tag);
	static Node* createUniform(const Tag &tag);
private:
	enum kind_t {INT, FLOAT, FLOAT_ARRAY, MATRIX, SAMPLER, VECTOR};
	static bool installed;
	static map<string,kind_t> kinds;
};

#endif
