/*
 * Scale.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_SCALE_HPP
#define GLXML_SCALE_HPP
#include "glxml_common.h"
#include <gloop/Vec4.hpp>
#include "Transform.hpp"
using namespace std;


/** @brief %Node that resizes items in the scene.
 * @ingroup basic
 */
class Scale : public Transform,
              public Vec4 {
public:
	Scale(const Tag &tag);
	virtual void add(const Vec4 &B);
	virtual void apply();
	virtual void applyTo(Matrix &matrix);
	virtual void remove();
	virtual bool setAttribute(pair<string,string> attribute);
	virtual string toString() const;
protected:
	Matrix getMatrix() const;
private:
	float value;
};

inline Matrix Scale::getMatrix() const {
	return Matrix( x , 0.0, 0.0, 0.0,
	              0.0,  y , 0.0, 0.0,
	              0.0, 0.0,  z , 0.0,
	              0.0, 0.0, 0.0, 1.0);
}


#endif