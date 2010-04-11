/*
 * Painter.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef PAINTER_HPP
#define PAINTER_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "Applicable.hpp"          // Apply modifications to scene
#include "Box.hpp"                 // Outline selected items
#include "Drawable.hpp"            // Drawing items in scene
#include "Framebuffer.hpp"         // Disable manipulators
#include "Manipulator.hpp"         // Drawing manipulators for selection
#include "Matrix.hpp"              // Rotating camera
#include "Node.hpp"                // Traversing the scene graph
#include "Program.hpp"             // Disable GLSL for outlines
#include "Selectable.hpp"          // Drawing manipulators for selection
#include "Texture.hpp"             // Pausing and restarting texturing
#include "Transformation.hpp"      // Drawing manipulators for selection
#include "Scene.hpp"               // Rotating camera and accessing root node
#include "Vector.hpp"
using namespace std;


/**
 * @ingroup frontend
 * @brief
 *     Paints all the items to the screen or pick buffer.
 * 
 * @warning Does not flush to the buffer.
 */
class Painter {
	
	public :
		
		static void paint(Scene &scene,
		                  vector<Manipulator*> &manipulators,
		                  GLenum renderMode=GL_RENDER);
	
	private :
		
		static Box outline;
		
		static void disableTexturing();
		static void paintChildren(Node *node,
		                          GLenum renderMode,
		                          vector<Manipulator*> &manipulators);
		static void paintNode(Node *node,
		                      GLenum renderMode,
		                      vector<Manipulator*> &manipulators);
		static void paintUIElements(Selectable *selectable,
		                            GLenum renderMode,
		                            vector<Manipulator*> &manipulators);
};


#endif
