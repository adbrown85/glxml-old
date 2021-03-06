/*
 * Framebuffer.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Framebuffer.hpp"

/** Initializes the chains in the framebuffer. */
Framebuffer::Framebuffer(const Tag &tag) : Node(tag) {
	
	Chain chain;
	
	// Basics
	this->handle = 0;
	this->capacity = Configuration::getMaxColorAttachments();
	
	// Chains
	chain.base = GL_COLOR_ATTACHMENT0;
	chain.max = capacity;
	chains["color"] = chain;
	chain.base = GL_DEPTH_ATTACHMENT;
	chain.max = 1;
	chains["depth"] = chain;
}

/** Deletes the underlying OpenGL framebuffer object. */
Framebuffer::~Framebuffer() {
	
	glDeleteFramebuffers(1, &handle);
}

/** Binds the framebuffer object. */
void Framebuffer::apply() {
	
	glBindFramebuffer(GL_FRAMEBUFFER, handle);
}

/** Generates the underlying OpenGL framebuffer object. */
void Framebuffer::associate() {
	
	glGenFramebuffers(1, &handle);
}

/** Attaches each attachment in a chain of attachments. */
void Framebuffer::attach(Chain &chain) {
	
	GLint index;
	list<Attachable*>::iterator it;
	
	index = 0;
	for (it=chain.attachables.begin(); it!=chain.attachables.end(); ++it) {
		(*it)->setIndex(index);
		(*it)->setLocation(chain.base + index);
		(*it)->attach();
		++index;
	}
}

/** Enqueues an attachable item to be attached.
 * 
 * @param type Either @e color or @e depth.
 * @param item Item to be attached.
 * @throw NodeException if type not supported.
 * @throw NodeException if maximum attachments for a slot will be exceeded.
 */
void Framebuffer::enqueue(const string &type, Attachable *item) {
	
	Chain *chain;
	
	// Add to list in slot
	chain = getChain(type);
	chain->attachables.push_back(item);
	
	// Check if the maximum was exceeded
	if (chain->attachables.size() > chain->max) {
		NodeException e(tag);
		e << "[Framebuffer] Maximum amount of attachable items exceeded.";
		throw e;
	}
}

/** Attaches all the attachments and checks if the framebuffer is complete.
 * 
 * @throw NodeException if framebuffer is not complete.
 */
void Framebuffer::finalize() {
	
	map<string,Chain>::iterator it;
	
	// Make sure the framebuffer is bound
	glBindFramebuffer(GL_FRAMEBUFFER, handle);
	
	// Attach all the chains
	for (it=chains.begin(); it!=chains.end(); ++it) {
		attach(it->second);
	}
	
	// Verify
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		NodeException e(tag);
		e << "[Framebuffer] Needs attachments to be complete.";
		throw e;
	}
	
	// Restore default framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/** @return Structure holding state for one type of attachment. 
 * 
 * @throw NodeException if type not supported.
 */
Chain* Framebuffer::getChain(const string &name) {
	
	map<string,Chain>::iterator it;
	
	it = chains.find(name);
	if (it != chains.end()) {
		return &(it->second);
	} else {
		NodeException e(tag);
		e << "[Framebuffer] Unsupported attachment type '" << name << "'.";
		throw e;
	}
}

/** Unbinds the %Framebuffer. */
void Framebuffer::remove() {
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/** Forms a string from the object's attributes. */
string Framebuffer::toString() const {
	
	ostringstream stream;
	
	// Insert attributes
	stream << Node::toString()
	       << " handle='" << handle << "'"
	       << " capacity='" << capacity << "'";
	return stream.str();
}
