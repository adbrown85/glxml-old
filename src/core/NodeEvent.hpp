/*
 * NodeEvent.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef NODEEVENT_HPP
#define NODEEVENT_HPP
#include "common.h"
#include "Node.hpp"
using namespace std;


/** @brief Event originating from a node.
 * @ingroup scene
 */
class NodeEvent {
public:
	enum {ASSOCIATE,FINALIZE,MODIFY};
	NodeEvent(Node *source, int type);
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
 * @ingroup scene
 * @interface NodeListener
 */
class NodeListener {
public:
	virtual void onNodeEvent(NodeEvent &event) = 0;
};


/** @brief Utility for notifying listeners of node events.
 * @ingroup scene
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