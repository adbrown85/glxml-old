/*
 * Outputs.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Outputs.hpp"

/** Clears the @e locations array. */
Outputs::Outputs(const Tag &tag) : Node(tag) {
	
	locations = NULL;
	n = 0;
}

/** Deletes the @e locations array. */
Outputs::~Outputs() {
	
	if (locations != NULL) {
		delete[] locations;
	}
}

/** Adds an attachment so it will be available for output. 
 * 
 * @return Position of the attachment in list (-1 if couldn't be added).
 */
GLint Outputs::addAttachment(Attachment *attachment) {
	
	list<Attachment*>::iterator it;
	
	// First check if it's already there
	it = find(attachments.begin(), attachments.end(), attachment);
	if (it != attachments.end()) {
		return distance(attachments.begin(), it);
	}
	
	// Otherwise try to add it
	if (attachments.size() == Configuration::getMaxDrawBuffers()) {
		return -1;
	} else {
		attachments.push_back(attachment);
		return attachments.size() - 1;
	}
}

/** Directs OpenGL to use the attachments of the bound output variables. */
void Outputs::apply() {
	
	glDrawBuffers(n, locations);
}

/** Makes sure there's a framebuffer.
 * 
 * @throw NodeException if no Bind children were found.
 */
void Outputs::associate() {
	
	// Find framebuffer
	framebuffer = Scout<Framebuffer>::locate(getParent());
	if (framebuffer == NULL) {
		NodeException e(tag);
		e << "[Outputs] Could not find Framebuffer.";
		throw e;
	}
}

/** Fills the @e locations array. */
void Outputs::finalize() {
	
	int i;
	list<Attachment*>::iterator it;
	
	// Validate
	if (attachments.empty()) {
		NodeException e(tag);
		e << "[Outputs] No attachments were added.";
		throw e;
	}
	
	// Initialize array
	n = Configuration::getMaxDrawBuffers();
	locations = new GLenum[n];
	for (int i=0; i<n; ++i) {
		locations[i] = GL_NONE;
	}
	
	// Fill array
	for (it=attachments.begin(); it!=attachments.end(); ++it) {
		i = distance(attachments.begin(), it);
		locations[i] = (*it)->getLocation();
	}
}

/** @return String comprised of the object's attributes. */
string Outputs::toString() const {
	
	int i;
	list<Attachment*>::const_iterator it;
	ostringstream stream;
	
	stream << Node::toString();
	stream << " locations='";
	for (it=attachments.begin(); it!=attachments.end(); ++it) {
		i = distance(attachments.begin(), it);
		stream << locations[i] - GL_COLOR_ATTACHMENT0;
		if (*it != attachments.back()) {
			stream << " ";
		}
	}
	stream << "'";
	return stream.str();
}
