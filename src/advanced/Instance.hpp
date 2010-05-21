/*
 * Instance.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef INSTANCE_HPP
#define INSTANCE_HPP
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <map>
#include <queue>
#include <GL/glut.h>
#include "Node.hpp"
#include "Group.hpp"
#include "Uniform.hpp"
#include "Shape.hpp"
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

/**
 * @ingroup advanced
 * @brief Redraws all the nodes of a group with different characteristics.
 */
class Instance : public Applicable {
public:
	Instance(const Tag &tag);
	virtual void apply();
	virtual bool areChildrenDestroyable() const;
	virtual bool areChildrenPrintable() const;
	virtual void associate();
	virtual void associateAfter();
	virtual void finalize();
	virtual void finalizeAfter();
	virtual void remove() {}
	virtual string toString() const;
protected:
	void assignParents();
	void findChildren();
	void findGroup();
	void findShapes();
	void findUniforms();
	void restoreShapes();
	void restoreUniforms();
	void storeShapes();
	void storeUniforms();
private:
	Group *group;
	string of;
	map<Shape*,ShapeSnapshot> shapes;
	map<Uniform*,UniformSnapshot> uniforms;
};

inline bool Instance::areChildrenDestroyable() const {return false;}
inline bool Instance::areChildrenPrintable() const {return false;}


#endif
