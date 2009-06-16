/*
 * Item.hpp
 *     Generic item class.  Also defines ItemSet.
 *
 * Author
 *     Andy Brown <adb1413@rit.edu>
 */
#ifndef ITEM_HPP
#define ITEM_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include "Identifiable.hpp"
#include "Vector.hpp"



class Item : public Identifiable  {
	
	
	public :
		
		Item();
		
		friend std::ostream& operator<<(std::ostream &stream,
		                                const Item &item);
		
		virtual std::string attributes() const;
		virtual void copy(const Item &item);
		virtual void draw() const = 0;
		
		int getID() const {return id;}
		bool isSelected() const {return selected;}
		bool isShown() const {return shown;}
		void setID(int id) {this->id = id;}
		void setPosition(float x, float y, float z) {position.set(x, y, z);}
		void setSelected(bool selected) {this->selected = selected;}
		void setShown(bool shown) {this->shown = shown;}
		void setStyle(GLenum style) {this->style = style;}
		void toggleSelected() {selected = !selected;}
		void toggleShown() {shown = !shown;}
	
	
	protected : 
		
		bool selected, shown;
		float size;
		GLenum style;
		static int count;
		std::string type;
		Vector position, rotation;
		int id;
};
typedef std::set<Item,Identifiable::Comparator> ItemSet;
typedef std::set<Item*,Identifiable::Comparator> ItemPtrSet;


#endif
