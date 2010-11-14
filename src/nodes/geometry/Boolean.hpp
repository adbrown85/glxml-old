/*
 * Boolean.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_BOOLEAN_HPP
#define GLXML_BOOLEAN_HPP
#include "glxml_common.h"
#include <limits>                       // Calculating result
#include <vector>                       // Storing shapes and extents
#include <gloop/State.hpp>
#include "Group.hpp"
#include "Shape.hpp"
#include "Transform.hpp"
#include "Hexahedron.hpp"
#include "Factory.hpp"
#include "Uniform.hpp"
#include "Suppressor.hpp"
using namespace std;

/** @brief Combines shapes in different ways to create a new one.
 * 
 * To create a concrete operation, subclass %Boolean and implement 
 * isTangible() and updateAttributes().  Of course, make sure to pass the 
 * right number of vertices and all the attribute names in the constructor.
 * 
 * @ingroup advanced
 */
class Boolean : public Hexahedron {
public:
	Boolean(const Tag &tag, ShapeTraits traits);
	virtual ~Boolean();
	virtual string toString() const;
// Preparation
	virtual void associate();
	virtual void finalize();
// Traversal
	virtual void draw() const;
// Event handling
	virtual void onNodeEvent(NodeEvent &event);
protected:
	void applyUniforms() const;
	void applyUniforms(int i) const;
	void associateUniforms();
	void calculate();
	void calculateExtents();
	void calculateExtents(Node *node);
	void calculateOverlap();
	virtual void calculateTangible() = 0;
	void finalizeUniforms();
	void findGroup();
	void findShapes();
	void findTransforms();
	void findUniforms();
	bool isOverlapped() const;
	static bool isSubstantial(const Extent &extent);
	virtual void updateBuffer();
protected:
	static float FLT_INF;
	bool tangible;
	Extent overlap;
	Group *group;
	vector<Shape*> shapes;
	vector<Extent> extents;
	list<Uniform*> uniforms[2];
	Matrix modelMatrix;
	string of, operation;
	Suppressor suppressor;
};


#endif
