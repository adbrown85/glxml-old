/*
 * UniformFloatArray.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_UNIFORMFLOATARRAY_HPP
#define GLXML_UNIFORMFLOATARRAY_HPP
#include "glxml_common.h"
#include <gloop/ProgramAnalyzer.hpp>
#include "Uniform.hpp"
#include "Group.hpp"
#include "Shape.hpp"
#include "Calculator.hpp"
using namespace std;

/** @brief Array of uniforms capable of calculating values.
 * 
 * @ingroup shading
 */
class UniformFloatArray : public Uniform, public NodeNotifier {
public:
	UniformFloatArray(const Tag &tag);
	virtual ~UniformFloatArray();
	virtual string toString() const;
// Preparation
	virtual void associate();
	virtual void finalize();
// Traversal
	virtual void apply();
// Getters and setters
	virtual GLsizei getCount() const;
	virtual GLfloat* getValues() const;
	static set<UniformFloatArray*> search(Node *node);
protected:
	void findGroup();
	void findShapes();
private:
	GLfloat *values;
	string as, of;
	GLsizei count;
	Group *group;
	int calculation;
	set<Shape*> shapes;
	Calculator *calculator;
};

inline GLsizei UniformFloatArray::getCount() const {return count;}
inline GLfloat* UniformFloatArray::getValues() const {return values;}

#endif
