/*
 * Selection.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_SELECTION_HPP
#define GLXML_SELECTION_HPP
#include "glxml_common.h"
#include <set>
#include "Identifiable.hpp"
#include "Node.hpp"
#include "NodeInterfaces.hpp"
#include "NodeEvent.hpp"
using namespace std;

/** @brief Collection of selected items.
 * @ingroup scene
 */
class Selection {
public:
	void add(Node *node);
	void addAll(Node *node);
	void addListener(NodeListener *listener);
	void clear();
	void remove(Node *node);
// Iterating
	typedef set<Drawable*,Identifiable::Comparator>::iterator iterator;
	iterator begin();
	iterator end();
protected:
	void fireEvent();
private:
	set<Drawable*,Identifiable::Comparator> items;
	NodeNotifier notifier;
	Node *active;
};

/** @return iterator to the beginning of the selection. */
inline Selection::iterator Selection::begin() {return items.begin();}

/** @return iterator to the end of the selection. */
inline Selection::iterator Selection::end() {return items.end();}

#endif
