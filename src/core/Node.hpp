/*
 * Node.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_NODE_HPP
#define GLXML_NODE_HPP
#include "glxml_common.h"
#include <algorithm>
#include <typeinfo>
#include <vector>
#include <edo/Parser.hpp>
#include <edo/Tag.hpp>
#include <edo/Text.hpp>
#include <edo/Log.hpp>
#include "NodeException.hpp"
#include "Identifiable.hpp"
using namespace std;

/** @brief Basic element of the scene graph.
 * @ingroup scene
 */
class Node {
public:
	Node(const Tag &tag);
	virtual ~Node() {};
	void addChild(Node *child);
	void removeChild(Node *node);
	virtual string toString() const;
// Preparation
	virtual void verify() {}
	virtual void associate() {}
	virtual void associateAfter() {}
	virtual void finalize() {}
	virtual void finalizeAfter() {}
// Traversing
	virtual bool areChildrenDestroyable() const;
	virtual bool areChildrenPreparable() const;
	virtual bool areChildrenPrintable() const;
	virtual bool areChildrenSelectable() const;
	virtual bool areChildrenTraversable() const;
// Iterating
	typedef vector<Node*>::iterator iterator;
	iterator begin();
	iterator end();
	void erase(iterator it);
// Getters and setters
	virtual string getAttribute(const string &key) const;
	virtual bool setAttribute(pair<string,string> attribute);
	vector<Node*> getChildren() const;
	bool hasChildren() const;
	string getClassName() const;
	float getDepth() const;
	void setDepth(float depth);
	Node* getParent() const;
	void setParent(Node *parent);
	Tag getTag() const;
// Operators
	friend ostream& operator<<(ostream &stream, const Node &node);
// Utilities
	static bool compare(Node *A, Node *B);
	static void destroy(Node *node);
	static Node* findRoot(Node *node);
protected:
	float depth;
	Node *parent;
	Tag tag;
	vector<Node*> children;
};

inline bool Node::areChildrenDestroyable() const {return true;}
inline bool Node::areChildrenPreparable() const {return true;}
inline bool Node::areChildrenPrintable() const {return true;}
inline bool Node::areChildrenSelectable() const {return true;}
inline bool Node::areChildrenTraversable() const {return true;}
inline Node::iterator Node::begin() {return children.begin();}
inline Node::iterator Node::end() {return children.end();}
inline void Node::erase(Node::iterator it) {children.erase(it);}
inline vector<Node*> Node::getChildren() const {return children;}
inline float Node::getDepth() const {return depth;}
inline Node* Node::getParent() const {return parent;}
inline Tag Node::getTag() const {return tag;}
inline bool Node::hasChildren() const {return !children.empty();}
inline bool Node::setAttribute(pair<string,string> a) {return false;}
inline void Node::setDepth(float depth) {this->depth = depth;}
inline void Node::setParent(Node *parent) {this->parent = parent;}

#endif
