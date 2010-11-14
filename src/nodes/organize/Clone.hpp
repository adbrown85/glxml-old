/*
 * Clone.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_CLONE_HPP
#define GLXML_CLONE_HPP
#include "glxml_common.h"
#include "Instance.hpp"
#include "Uniform.hpp"
#include "Shape.hpp"
#include "Suppressor.hpp"
using namespace std;

/* State of a shape. */
struct ShapeSnapshot {
	Program *program;
	list<VertexAttribute> attributes;
};

/* State of a uniform. */
struct UniformSnapshot {
	Program *program;
	int location;
};

/** @brief Smart instance of a group that can handle different programs.
 * 
 * @warning Default uniforms on shapes in a clone may not work correctly.
 * 
 * @see Instance
 * @see Replica
 * 
 * @ingroup organize
 */
class Clone : public Instance {
public:
	Clone(const Tag &tag);
	virtual string toString() const;
// Preparation
	virtual void associate();
	virtual void associateAfter();
	virtual void finalize();
	virtual void finalizeAfter();
// Traversal
	virtual void apply();
// Utilities
	static Clone* search(Node *node);
protected:
	void findShapes();
	void findUniforms();
	void restoreShapes();
	void restoreUniforms();
	void saveShapes();
	void saveUniforms();
private:
	map<Shape*,ShapeSnapshot> shapes;
	map<Uniform*,UniformSnapshot> uniforms;
	bool suppress;
	Suppressor suppressor;
};

#endif
