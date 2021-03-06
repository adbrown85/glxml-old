/*
 * Target.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_TARGET_HPP
#define GLXML_TARGET_HPP
#include "glxml_common.h"
#include "Attachment.hpp"               // Base class
#include "Texture.hpp"                // Backer
using namespace std;

/** @brief Offscreen render location backed by a texture.
 * 
 * Attaches itself to a color attachment of a Framebuffer.  When the 
 * framebuffer is active, any rendering done to that attachment will be stored 
 * in the Texture referenced by the target.  Thus, results of one rendering 
 * pass can be referenced in a later one.
 * 
 * Multiple targets can be added to one framebuffer.  The framebuffer will 
 * assign them sequential indices ranging from 0 to 
 * <i>GL_MAX_COLOR_ATTACHMENTS</i>.  The built-in (but deprecated)
 * <i>gl_FragData</i> array references these attachments directly, but Bind 
 * can be used to assign user-defined <i>out</i> variables to the attachments.
 * 
 * <b>XML Name</b>
 *   - target
 * 
 * <b>XML Attributes</b>
 * <table border="1" cellpadding="2">
 * <tr>
 *   <td><i>name</i></td>
 *   <td>User-defined name that can be referenced by other nodes.</td>
 * </tr>
 * <tr>
 *   <td><i>link</i></td>
 *   <td>Name of the texture that backs the render target.</td>
 * </tr>
 * </table>
 * 
 * <b>XML Example</b>
 * <pre>
 *   &lt;texture name="layer0" >
 *   &lt;texture name="layer1" >
 *     &lt;framebuffer>
 *       &lt;target link="layer0" />
 *       &lt;target link="layer1" />
 *     &lt;/framebuffer>
 *   &lt;/texture>
 *   &lt;/texture>
 * </pre>
 * 
 * <b>Notes</b>
 *   - If <i>name</i> is not set explicitly it will be set to <i>link</i>.
 * 
 * @ingroup offscreen
 * @see Framebuffer
 * @see Attachment
 * @see Bind
 */
class Target : public Attachment {
public:
	Target(const Tag &tag);
	virtual string toString() const;
	virtual void attach();
// Preparation
	void associate();
// Getters and setters
	virtual string getLink() const;
	virtual void setLink(const string &link);
	virtual int getSize() const;
private:
	Texture *texture;
	string link;
};

/** @return Width of the texture backing the render target. */
inline int Target::getSize() const {return texture->getSize();}

/** @return Name of the texture to render to. */
inline string Target::getLink() const {return link;}

/** Sets the name of the texture to render to. */
inline void Target::setLink(const string &link) {this->link = link;}

#endif
