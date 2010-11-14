/*
 * Calculator.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_CALCULATOR_HPP
#define GLXML_CALCULATOR_HPP
#include "glxml_common.h"
#include <gloop/State.hpp>
#include "Shape.hpp"
#define HALF_BOUNDING_BOX_DIAGONAL 0.866025404
using namespace std;

/* Enumeration of different calculations. */
class Calculation {
public:
	enum {NONE, DISTRIBUTION_Z};
};

/** @brief Utility for calculating values from a set of shapes.
 * 
 * @ingroup geometry
 */
class Calculator {
public:
	Calculator(set<Shape*> shapes);
	static GLint getCalculationFor(const string &name);
	void run(GLint calculation, GLsizei count, float *values);
protected:
	void runDistributionZ(GLsizei count, float *values);
private:
	set<Shape*> shapes;
};


#endif
