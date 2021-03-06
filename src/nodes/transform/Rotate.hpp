/*
 * Rotate.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_ROTATE_HPP
#define GLXML_ROTATE_HPP
#include "glxml_common.h"
#include <iomanip>
#include <gloop/Quaternion.hpp>
#include <gloop/Vec4.hpp>
#include "Transform.hpp"
using namespace std;

/** @brief %Node that reorients items in the scene.
 * 
 * @ingroup transform
 */
class Rotate : public Transform {
public:
	Rotate(const Tag &tag);
	virtual string toString() const;
// Traversal
	virtual void apply();
	virtual void applyTo(Matrix &matrix);
	virtual void remove();
private:
	float angle;
	Vec4 axis;
	Quaternion quaternion;
};


#endif
