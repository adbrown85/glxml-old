/*
 * SimpleDrawable.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_SIMPLEDRAWABLE_HPP
#define GLXML_SIMPLEDRAWABLE_HPP
#include "glxml_common.h"
#include "Node.hpp"
#include "NodeInterfaces.hpp"
#include "SimpleTransformable.hpp"
using namespace std;

/** @brief Base class for a node that can be drawn on screen.
 * 
 * @ingroup geometry
 */
class SimpleDrawable : public SimpleTransformable,
                       public Drawable {
public:
	SimpleDrawable(const Tag &tag);
	virtual string toString() const;
// Traversal
	virtual void draw() const = 0;
// Getters and setters
	virtual bool isExcluded() const;
	virtual void setExcluded(bool excluded);
	virtual bool isSelectable() const;
	virtual bool isSelected() const;
	virtual void setSelected(bool selected);
	virtual void toggleSelected();
	virtual bool isVisible() const;
	virtual void setVisible(bool visible);
	virtual void toggleVisible();
protected:
	bool excluded, selectable, selected, visible;
};

inline bool SimpleDrawable::isExcluded() const {return excluded;}
inline void SimpleDrawable::setExcluded(bool exc) {this->excluded = exc;}
inline bool SimpleDrawable::isSelectable() const {return selectable;}
inline bool SimpleDrawable::isSelected() const {return selected;}
inline void SimpleDrawable::setSelected(bool sel) {this->selected = sel;}
inline void SimpleDrawable::toggleSelected() {selected = !selected;}
inline bool SimpleDrawable::isVisible() const {return visible;}
inline void SimpleDrawable::setVisible(bool vis) {this->visible = vis;}
inline void SimpleDrawable::toggleVisible() {visible = !visible;}

#endif
