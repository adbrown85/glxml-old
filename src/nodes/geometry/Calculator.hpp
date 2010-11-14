/*
 * Calculator.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_CALCULATOR_HPP
#define GLXML_CALCULATOR_HPP
#include "glxml_common.h"
#include "Shape.hpp"
#define HALF_BOUNDING_BOX_DIAGONAL 0.866025404
using namespace std;


/* Enumeration of different calculations. */
class Calculation {
public:
	enum {NONE, DISTRIBUTION_Z};
};

/** @brief Utility for calculating values from a set of shapes.
 * @ingroup basic
 */
class Calculator {
public:
	Calculator(set<Shape*> shapes);
	static GLint getCalculationFor(const string &name);
	void run(GLint calculation, GLsizei count, float *values);
	void setCamera(Camera *camera);
protected:
	void checkCamera();
	void runDistributionZ(GLsizei count, float *values);
private:
	Camera *camera;
	set<Shape*> shapes;
};

/** Sets the camera if it is required by the calculation. */
inline void Calculator::setCamera(Camera *camera) {this->camera = camera;}


#endif
