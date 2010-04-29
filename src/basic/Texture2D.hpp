/*
 * Texture2D.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <IL/ilut.h>
#include <iostream>
#include <sstream>
#include <string>
#include "Texture.hpp"


/**
 * @ingroup basic
 * @brief
 *     %Texture node for images.
 */
class Texture2D : public Texture {
	
	public :
		
		Texture2D(const string &name,
		          const string &filename);
		Texture2D(const string &name,
		          int size);
		Texture2D(const Tag &tag);
		virtual void associate();
		virtual int getSize() const;
		virtual string toString() const;
	
	private:
		
		ILuint image;
		int size;
		
		virtual void generate();
		virtual void init();
		virtual void load();
	
	public: 
		
		static void find(Node *node,
		                 Texture2D *&pointer,
		                 const string &name);
	
	private:
		
		static bool librariesLoaded;
		
		static void initLibraries();
};


inline int Texture2D::getSize() const {return size;}


#endif
