/*
 * Outputs.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_OUTPUTS_HPP
#define GLXML_OUTPUTS_HPP
#include "glxml_common.h"
#include <algorithm>                    // Finding attachments
#include <gloop/Configuration.hpp>      // Max draw buffers
#include "Attachment.hpp"
using namespace std;

/** @brief Activates framebuffer attachments.
 * @ingroup advanced
 */
class Outputs : public Node, public Applicable {
public:
	Outputs(const Tag &tag);
	virtual ~Outputs();
	virtual string toString() const;
	virtual GLint addAttachment(Attachment *attachment);
// Preparation
	virtual void associate();
	virtual void finalize();
// Traversal
	virtual void apply();
	virtual void remove() {}
private:
	list<Attachment*> attachments;
	Framebuffer *framebuffer;
	GLenum *locations;
	GLsizei n;
};

#endif
