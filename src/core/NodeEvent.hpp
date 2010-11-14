/*
 * NodeEvent.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_NODEEVENT_HPP
#define GLXML_NODEEVENT_HPP
#include "glxml_common.h"
#include "Node.hpp"
using namespace std;

/** @brief Event originating from a node.
 * 
 * @ingroup core
 */
class NodeEvent {
public:
	enum {ASSOCIATE,FINALIZE,MODIFY};
	NodeEvent(Node *source, int type);
// Getters and setters
	Node* getSource() const;
	int getType() const;
private:
	Node *source;
	int type;
};
inline NodeEvent::NodeEvent(Node *s, int t) : source(s), type(t) {}
inline Node* NodeEvent::getSource() const {return source;}
inline int NodeEvent::getType() const {return type;}

/** @brief Object that is notified by a node.
 * 
 * @ingroup core
 * @interface NodeListener
 */
class NodeListener {
public:
	virtual void onNodeEvent(NodeEvent &event) = 0;
};

/** @brief Utility for notifying listeners of node events.
 * 
 * @ingroup core
 */
class NodeNotifier {
public:
	void addListener(NodeListener *listener, int type);
	void fireEvent(NodeEvent event);
	static set<NodeNotifier*> search(Node *node);
protected:
	list<NodeListener*>* getListenersFor(int type);
private:
	map<int, list<NodeListener*> > listeners;
};

#endif
