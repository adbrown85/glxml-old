/*
 * Translate.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_TRANSLATE_HPP
#define GLXML_TRANSLATE_HPP
#include "glxml_common.h"
#include <edo/Tag.hpp>
#include <gloop/Matrix.hpp>
#include <gloop/Vec4.hpp>
#include "Transform.hpp"
using namespace std;


/** @brief %Node that moves items in the scene.
 * @ingroup basic
 */
class Translate : public Transform {
public:
	Translate(const Tag &tag);
	virtual string toString() const;
	void add(const Vec4 &B);
// Traversal
	virtual void apply();
	virtual void remove();
	virtual void applyTo(Matrix &matrix);
// Getters and setters
	virtual bool setAttribute(pair<string,string> attribute);
	Matrix getMatrix() const;
	virtual Vec4 getValue() const;
private:
	Vec4 value;
};

inline Vec4 Translate::getValue() const {return value;}

inline Matrix Translate::getMatrix() const {
	return Matrix(1.0, 0.0, 0.0,  +value.x,
	              0.0, 1.0, 0.0,  +value.y,
	              0.0, 0.0, 1.0,  +value.z,
	              0.0, 0.0, 0.0, 1.0);
}


#endif
