/*
 * Shader.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_SHADER_HPP
#define GLXML_SHADER_HPP
#include "glxml_common.h"
#include <gloop/ShaderFactory.hpp>
#include "Node.hpp"
#include "NodeInterfaces.hpp"
#include "Program.hpp"
#include "Scout.hpp"
using namespace std;

/** @brief GLSL shader with loading and compiling capabilities.
 * 
 * <b>XML Name</b>
 *   - shader
 * 
 * <b>XML attributes</b>
 * <table border="1" cellpadding="2">
 * <tr>
 *   <td><i>type</i></td>
 *   <td>Either <i>fragment</i> or <i>vertex</i></td>
 * </tr>
 * <tr>
 *   <td><i>file</i></td>
 *   <td>Path to the file containing source code for the shader</td>
 * </tr>
 * </table>
 * 
 * <b>XML example</b>
 * <pre>
 *   &lt;program>
 *     &lt;shader file="color.vert" />
 *     &lt;shader file="color.frag" />
 *   &lt;/program>
 * </pre>
 * 
 * @ingroup shading
 */
class Shader : public Node, public Fileable {
public:
	Shader(const Tag &tag);
	virtual string toString() const;
// Preparation
	virtual void associate();
// Getters and setters
	GLuint getHandle() const;
	string getType() const;
protected:
	void guessType();
private:
	GLuint handle;
	string type;
};

/** @return Internal OpenGL identifier for the shader. */
inline GLuint Shader::getHandle() const {return handle;}

/** @return Either "fragment" or "vertex". */
inline string Shader::getType() const {return type;}

#endif
