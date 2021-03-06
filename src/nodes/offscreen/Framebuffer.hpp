/*
 * Framebuffer.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_FRAMEBUFFER_HPP
#define GLXML_FRAMEBUFFER_HPP
#include "glxml_common.h"
#include <gloop/Configuration.hpp>
#include "Node.hpp"
#include "Texture.hpp"

/* Group of similar framebuffer attachments. */
struct Chain {
	GLenum base;                        // GL_COLOR_ATTACHMENT0, etc.
	GLuint max;                         // Maximum amount of items
	list<Attachable*> attachables;      // Attached items
};

/** @brief Container for offscreen rendering targets.
 * 
 * Replaces the default framebuffer with an external framebuffer object 
 * comprised of a number of attachments.  When the framebuffer is active, 
 * rendering will be redirected to these attachments instead of the screen.  
 * Thus framebuffer can be used to render in multiple passes or to perform 
 * general-purpose computations.
 * 
 * %Framebuffer cannot be used by itself.  Make sure to place one or more 
 * Attachment nodes under the framebuffer, such as Target.  Also, you will 
 * need to use Outputs and Bind to direct fragments to the correct location.
 * 
 * <b>XML Name</b>
 *   - framebuffer
 * 
 * <b>OpenGL functions</b>
 *   - <tt>glGenFramebuffers</tt>
 *   - <tt>glDeleteFramebuffers</tt>
 *   - <tt>glBindFramebuffer</tt>
 *   - <tt>glCheckFramebufferStatus</tt>
 * 
 * <b>XML Example</b>
 * <pre>
 *   &lt;framebuffer>
 *     &lt;attachment />
 *     &lt;attachment />
 *   &lt;/framebuffer>
 *   &lt;clear />
 * </pre>
 * 
 * @note Clear is usually needed directly after the ending framebuffer tag
 * @note Screen can be used to temporarily disable the framebuffer
 * 
 * @ingroup offscreen
 * @see Attachment
 * @see Target
 * @see Outputs
 * @see Bind
 * @see Clear
 * @see Screen
 */
class Framebuffer : public Node, public Applicable {
public:
	Framebuffer(const Tag &tag);
	virtual ~Framebuffer();
	virtual string toString() const;
	virtual void enqueue(const string &type, Attachable *item);
// Preparation
	virtual void associate();
	virtual void finalize();
// Traversal
	virtual void apply();
	virtual void remove();
	virtual bool areChildrenSelectable() const;
// Getters and setters
	virtual GLuint getHandle() const;
protected:
	virtual void attach(Chain &chain);
	virtual Chain* getChain(const string &name);
private:
	GLuint handle, capacity;
	map<string,Chain> chains;
};

/** Disables trying to pick children drawn into a framebuffer. */
inline bool Framebuffer::areChildrenSelectable() const {return false;}

/** @return Integer identifying the underlying OpenGL framebuffer object. */
inline GLuint Framebuffer::getHandle() const {return handle;}

#endif
