/*
 * Quaternion.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef QUATERNION_HPP
#define QUATERNION_HPP
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "Matrix.hpp"
#include "Vector.hpp"
using namespace std;


/**
 * @ingroup data
 * @brief
 *     Encapsulation of a rotation that avoids gimbal lock.
 */
class Quaternion {
	
	public:
		
		Quaternion();
		Matrix getMatrix() const;
		Quaternion operator*(const Quaternion &B);
		void print();
		void set(float angle,
		         float x,
		         float y,
		         float z);
		string toString();
	
	private :
		
		float s;
		Vector v;
		
		static float PI;
		
		void normalize();
		static float radians(float degrees);
};

#endif
