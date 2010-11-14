/*
 * SimpleTransformable.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_SIMPLETRANSFORMABLE_HPP
#define GLXML_SIMPLETRANSFORMABLE_HPP
#include "glxml_common.h"
#include <cfloat>
#include "Node.hpp"
#include "NodeInterfaces.hpp"
#include "NodeEvent.hpp"
#include "Transform.hpp"
using namespace std;

/** @brief Simple implementation of %Transformable.
 * 
 * @ingroup geometry
 */
class SimpleTransformable : public Node,
                            public Transformable,
                            public NodeListener {
public:
	SimpleTransformable(const Tag &tag);
// Preparation
	virtual void associate();
// Getters and setters
	virtual Extent getExtent();
	virtual Vec4 getPosition();
	virtual Matrix getTransformation();
	virtual Matrix getTransformationInverse();
// Event handling
	virtual void onNodeEvent(NodeEvent &event);
protected:
	void updatePositionExtent();
private:
	bool valid;
	list<Transform*> transforms;
	Extent extent;
	Vec4 position;
	Matrix transformation;
};

/** Invalidates the position when a transform changes. */
inline void SimpleTransformable::onNodeEvent(NodeEvent &event) {valid = false;}

#endif
