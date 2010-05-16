/*
 * Target.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Target.hpp"


/** Initializes the @e link and @e name attributes. */
Target::Target(const Tag &tag) : Attachment(tag,"color") {
	
	tag.get("link", link, true, false);
	if (getName().empty())
		setName(link);
}


/** Finds the framebuffer and texture to use.
 * 
 * @throws NodeException if cannot find texture with correct name.
 * @throws NodeException from Attachment::associate().
 */
void Target::associate() {
	
	// Find the texture
	texture = Texture2D::find(this, link);
	if (texture == NULL) {
		NodeException e(tag);
		e << "[Target] Could not find texture with name '" << link << "'.";
		throw e;
	}
	
	// Find framebuffer and enqueue
	Attachment::associate();
}


/** Attaches the target's texture to the framebuffer.
 * 
 * @note Assumes the framebuffer is already bound.
 */
void Target::attach() {
	
	glFramebufferTexture2D(GL_FRAMEBUFFER,
	                       getLocation(),
	                       GL_TEXTURE_2D,
	                       texture->getHandle(),
	                       0);
}


/** @return String comprised of the object's name and attributes. */
string Target::toString() const {
	
	ostringstream stream;
	
	stream << Attachment::toString()
	       << " link='" << link << "'"
	       << " size='" << texture->getSize() << "'"
	       << " texture='" << texture->getHandle() << "'";
	return stream.str();
}

