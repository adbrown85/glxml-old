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
	virtual GLint addAttachment(Attachment *attachment);
	virtual void apply();
	virtual void remove() {}
	virtual string toString() const;
protected:
	virtual void associate();
	virtual void finalize();
private:
	list<Attachment*> attachments;
	Framebuffer *framebuffer;
	GLenum *locations;
	GLsizei n;
};


#endif
