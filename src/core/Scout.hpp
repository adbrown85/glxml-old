/*
 * Scout.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_SCOUT_HPP
#define GLXML_SCOUT_HPP
#include "glxml_common.h"
#include "Node.hpp"
#include "NodeInterfaces.hpp"
using namespace std;

/** @brief Utility for finding nodes in a scene.
 * 
 * @ingroup core
 */
template <typename T>
class Scout {
public:
	static T* locate(Node *node);
	static T* locate(Node *node, const string &name);
	static T* search(Node *root);
	static T* search(Node *node, const string &name);
	static void search(Node *root, list<T*> &items);
};

/** Finds a node above @e node of correct type. */
template <typename T>
T* Scout<T>::locate(Node* node) {
	
	T *t;
	
	// Look for ancestor
	while (node != NULL) {
		t = dynamic_cast<T*>(node);
		if (t != NULL)
			return t;
		node = node->getParent();
	}
	return NULL;
}

/** Finds a node above @e node of correct type named @e name. */
template <typename T>
T* Scout<T>::locate(Node* node, const string &name) {
	
	T *t;
	Nameable *nameable;
	
	// Look for ancestor with name
	while (node != NULL) {
		t = dynamic_cast<T*>(node);
		if (t != NULL) {
			nameable = dynamic_cast<Nameable*>(t);
			if ((nameable != NULL) && (nameable->getName() == name))
				return t;
		}
		node = node->getParent();
	}
	return NULL;
}

/** Finds a node under @e root of correct type. */
template <typename T>
T* Scout<T>::search(Node *root) {
	
	Node *node;
	Node::iterator it;
	queue<Node*> Q;
	T *t;
	
	// Search under root for node
	Q.push(root);
	while (!Q.empty()) {
		node = Q.front();
		t = dynamic_cast<T*>(node);
		if (t != NULL)
			return t;
		for (it=node->begin(); it!=node->end(); ++it)
			Q.push((*it));
		Q.pop();
	}
	return NULL;
}

/** Finds a node under @e root of correct type. */
template <typename T>
T* Scout<T>::search(Node *root, const string &name) {
	
	Nameable *nameable;
	Node *node;
	Node::iterator it;
	queue<Node*> Q;
	T *t;
	
	// Search under root for node
	Q.push(root);
	while (!Q.empty()) {
		node = Q.front();
		t = dynamic_cast<T*>(node);
		if (t != NULL) {
			nameable = dynamic_cast<Nameable*>(t);
			if ((nameable != NULL) && (nameable->getName() == name))
				return t;
		}
		for (it=node->begin(); it!=node->end(); ++it)
			Q.push((*it));
		Q.pop();
	}
	return NULL;
}

/** Finds all the nodes under @e root of a certain type. */
template <typename T>
void Scout<T>::search(Node *root, list<T*> &items) {
	
	Node::iterator it;
	Node *node;
	queue<Node*> Q;
	T *t;
	
	Q.push(root);
	while (!Q.empty()) {
		node = Q.front();
		t = dynamic_cast<T*>(node);
		if (t != NULL)
			items.push_back(t);
		for (it=node->begin(); it!=node->end(); ++it)
			Q.push(*it);
		Q.pop();
	}
}

#endif
