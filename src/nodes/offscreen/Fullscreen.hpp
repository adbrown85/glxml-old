/*
 * Fullscreen.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_FULLSCREEN_HPP
#define GLXML_FULLSCREEN_HPP
#include "glxml_common.h"
#include "Shape.hpp"

/** @brief Rectangle that takes up the entire window.
 * 
 * Automatically adds a uniform that sets the modelviewprojection matrix in 
 * the program to the identity matrix.
 * 
 * @ingroup advanced
 */
class Fullscreen : public Shape {
public:
	Fullscreen(const Tag &tag);
// Getters and setters
	virtual bool isSelectable() const;
protected:
	static ShapeTraits getTraits();
	virtual void updateBuffer();
	virtual void updateBufferCoords();
	virtual void updateBufferNormals();
	virtual void updateBufferPoints();
};

inline bool Fullscreen::isSelectable() const {return false;}

#endif
