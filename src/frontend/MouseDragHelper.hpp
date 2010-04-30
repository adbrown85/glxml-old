/*
 * MouseDragHelper.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef MOUSEDRAGHELPER_HPP
#define MOUSEDRAGHELPER_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <map>
#include <vector>
#include "Binding.hpp"
#include "Delegate.hpp"
#include "Manipulator.hpp"
#include "MouseData.hpp"
#include "MouseHelper.hpp"
#include "Vector.hpp"
#include "Window.hpp"
using namespace std;


/**
 * @ingroup frontend
 * @brief
 *     Handles mouse dragging actions for %Mouse.
 */
class MouseDragHelper : public MouseHelper {
	
	public:
		
		MouseDragHelper(Delegate *delegate,
		                Scene *scene);
		void onDrag(int x,
		            int y);
		void setBindings(multimap<int,Binding> bindings);
	
	protected:
		
		void decideAxis();
		void tryBinding(Binding *binding);
		void tryBindings();
		bool useConstrained();
	
	private:
		
		Vector axis, direction, movement;
		static char directions[2];
};


#endif
