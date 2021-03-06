/*
 * Screen.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_SCREEN_HPP
#define GLXML_SCREEN_HPP
#include "glxml_common.h"
#include "Framebuffer.hpp"
using namespace std;

/** @brief Temporarily disables a framebuffer in order to render to the screen.
 * 
 * <b>XML name</b>
 *   - <i>screen</i>
 * 
 * <b>OpenGL functions</b>
 *   - <i>glBindFramebuffer</i>
 * 
 * @ingroup offscreen
 * @see Framebuffer
 */
class Screen : public Node, public Applicable {
public:
	Screen(const Tag &tag);
// Preparation
	virtual void associate();
// Traversal
	virtual void apply();
	virtual void remove();
private:
	Framebuffer *framebuffer;
};

#endif
