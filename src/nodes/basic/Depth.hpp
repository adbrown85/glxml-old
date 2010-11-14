/*
 * Depth.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_DEPTH_HPP
#define GLXML_DEPTH_HPP
#include "glxml_common.h"
#include "Node.hpp"
#include "NodeInterfaces.hpp"
using namespace std;

/** @brief Modifies the depth function.
 * 
 * <b>XML Name</b>
 *   - depth
 * 
 * <b>XML attributes</b>
 * <table border="1" cellpadding="2">
 * <tr>
 *   <td><i>mode</i></td>
 *   <td>Comparison to determine if incoming fragment passes depth test.</td>
 * </tr>
 * </table>
 * 
 * <b><i>mode</i> values</b>
 *   - never
 *   - less
 *   - equal
 *   - lequal
 *   - greater
 *   - notequal
 *   - gequal
 *   - always
 * 
 * <b>OpenGL Functions</b>
 *   - glDepthFunc
 * 
 * <b>Example</b>
 * <pre>
 *   &lt;depth mode="gequal">
 *     &lt;cube />
 *   &lt;/depth>
 * </pre>
 * 
 * @ingroup basic
 */
class Depth : public Node, public Applicable {
public:
	Depth(const Tag &tag);
	virtual string toString() const;
// Traversal
	virtual void apply();
	virtual void remove();
private:
	GLenum mode;
};

#endif
