/*
 * Translate.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TRANSLATE_HPP
#define TRANSLATE_HPP
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
	void add(const Vector &B);
	virtual void apply();
	virtual void applyTo(Matrix &matrix);
	virtual Vector getValue() const;
	virtual void remove();
	virtual bool setAttribute(pair<string,string> attribute);
	virtual string toString() const;
protected:
	Matrix getMatrix() const;
private:
	Vector value;
};

inline Vector Translate::getValue() const {return value;}

inline Matrix Translate::getMatrix() const {
	return Matrix(1.0, 0.0, 0.0,  +value.x,
	              0.0, 1.0, 0.0,  +value.y,
	              0.0, 0.0, 1.0,  +value.z,
	              0.0, 0.0, 0.0, 1.0);
}


#endif
