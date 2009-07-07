/*
 * Translation.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef _TRANSLATION_HPP_
#define _TRANSLATION_HPP_
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include "Node.hpp"
#include "Vector.hpp"



class Translation : public Node, public Vector {
	
	
	public :
		
		Translation();
		Translation(float x, float y, float z);
		
		void apply();
		void restore();
};


#endif
