/*
 * Bind.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_BIND_HPP
#define GLXML_BIND_HPP
#include "glxml_common.h"
#include "Node.hpp"                     // Base class
#include "Attachment.hpp"               // Look up attachment location
#include "Outputs.hpp"                  // Add attachment, look up position
#include "Program.hpp"                  // Bind location in current program
#include "Scout.hpp"
using namespace std;

/** @brief Binds a fragment shader output variable to location in a framebuffer.
 * 
 * Although the built-in <i>gl_FragData</i> array can be used to render to 
 * framebuffer attachments directly by their index, it has been deprecated in 
 * GLSL 1.3 and will eventually be removed.  User-defined <i>out</i> variables 
 * in the fragment shader take their place.
 * 
 * A %Bind node sets the value of one of these variables in a Program above it
 * to the index of a named framebuffer attachment in the current outputs 
 * list.  The variable is set during the <i>associate</i> stage before the 
 * program is linked and is not touched again.
 * 
 * <b>XML Name</b>
 *   - bind
 * 
 * <b>XML attributes</b>
 * <table border="1" cellpadding="2">
 * <tr>
 *   <td><i>name</i></td>
 *   <td>Name of the output variable in the fragment shader.</td>
 * </tr>
 * <tr>
 *   <td><i>to</i></td>
 *   <td>Name of the attachment to link to.</td>
 * </tr>
 * </table>
 * 
 * <b>XML example</b>
 * <pre>
 *   &lt;texture name="layer0">
 *   &lt;texture name="layer1">
 *     &lt;framebuffer>
 *       &lt;target link="layer0" />
 *       &lt;target link="layer1" />
 *       &lt;program>
 *         &lt;shader file="layers.vert" />
 *         &lt;shader file="layers.frag" />
 *         &lt;outputs>
 *           &lt;bind name="Layer0" to="layer0" />
 *           &lt;bind name="Layer1" to="layer1" />
 *         &lt;/outputs>
 *         &lt;uniform type="mat4" name="MVPMatrix" as="modelviewprojection" />
 *         &lt;cube />
 *       &lt;/program>
 *     &lt;/framebuffer>
 *   &lt;/texture>
 *   &lt;/texture>
 * </pre>
 * 
 * @ingroup offscreen
 * @see Framebuffer
 * @see Attachment
 * @see Target
 * @see Outputs
 */
class Bind : public Node {
public:
	Bind(const Tag &tag);
	virtual string toString() const;
// Preparation
	virtual void associate();
	virtual void finalize();
// Getters and setters
	virtual GLint getIndex() const;
protected:
	void findAttachment();
	void findOutputs();
	void findProgram();
private:
	string name, to;
	GLint index;
	Attachment *attachment;
	Outputs *outputs;
	Program *program;
};

/** @return Index of the target in the outputs list. */
inline GLint Bind::getIndex() const {return index;}

#endif
