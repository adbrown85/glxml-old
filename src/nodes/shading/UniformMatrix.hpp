/*
 * UniformMatrix.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_UNIFORMMATRIX_HPP
#define GLXML_UNIFORMMATRIX_HPP
#include "Uniform.hpp"
#include <gloop/State.hpp>
#include "Light.hpp"
#define DEFAULT_MODEL_MATRIX_NAME "MMatrix"
#define DEFAULT_MODELVIEW_MATRIX_NAME "MVMatrix"
#define DEFAULT_PROJECTION_MATRIX_NAME "PMatrix"
#define DEFAULT_MODELVIEW_PROJECTION_MATRIX_NAME "MVPMatrix"
#define DEFAULT_NORMAL_MATRIX_NAME "NormalMatrix"
#define DEFAULT_IDENTITY_MATRIX_NAME "IdentityMatrix"
#define DEFAULT_LIGHT_MATRIX_NAME "MCtoLightMatrix"
using namespace std;

/* Enumeration of matrix types. */
enum MatrixType{MODEL,
                MODELVIEW,
                PROJECTION,
                MODELVIEW_PROJECTION,
                NORMAL,
                IDENTITY,
                LIGHT};

/** @brief Container for GLSL matrix uniform variables.
 * 
 * <b>XML Name</b>
 *   - uniform
 * 
 * <b>XML attributes</b>
 * <table border="1" cellpadding="2">
 * <tr>
 *   <td><i>type</i></td>
 *   <td><tt>mat4</tt></td>
 * </tr>
 * <tr>
 *   <td><i>name</i></td>
 *   <td>Name of the variable in the shader program</td>
 * </tr>
 * <tr>
 *   <td><i>as</i></td>
 *   <td>Use OpenGL transformation state as the value</td>
 * </tr>
 * </table>
 * 
 * <b>Valid values for <i>as</i> attribute</b>
 *   - modelview
 *   - projection
 *   - modelviewprojection
 *   - normal
 *   - identity
 * 
 * In addition, %UniformMatrix will automatically apply an 'as' attribute 
 * for several default names if it is not explicitly set in the scene file by 
 * the user.  The names in the following list correspond to the values in the 
 * previous list.
 * 
 * <b>Example</b>
 * <pre>
 *   &lt;program>
 *     &lt;shader file="shader.vert" />
 *     &lt;shader file="shader.frag" />
 *     &lt;uniform type="mat4" name="MVPMatrix" />
 *     &lt;cube />
 *   &lt;/program>
 * </pre>
 * 
 * <b>Default names</b>
 *   - MVMatrix
 *   - PMatrix
 *   - MVPMatrix
 *   - NormalMatrix
 *   - IdentityMatrix
 * 
 * @ingroup shading
 */
class UniformMatrix : public Uniform {
public:
	UniformMatrix(const Tag &tag);
	virtual string toString() const;
// Preparation
	virtual void associate();
// Traversal
	virtual void apply();
// Utilities
	static bool hasChild(Node *node, const string &name);
	static bool isDefault(const string &name, GLenum type);
	static bool isDefaultName(const string &name);
protected:
	void findLight();
	void setTypeFromAs();
	void setTypeFromName();
private:
	GLfloat value[16];
	MatrixType matrixType;
	string as, of;
	Light *light;
};

#endif
