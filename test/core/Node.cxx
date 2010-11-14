/*
 * Node.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "glxml_common.h"
#include <cassert>
#include <edo/Text.hpp>
#include "Node.hpp"
#define NUMBER_OF_ITEMS 4
using namespace std;

void print(Node *node, int level=0) {
	
	Node::iterator it;
	
	if (node == NULL)
		return;
	
	cout << Text::indent(level) << *node << " " << node << endl;
	for (it=node->begin(); it!=node->end(); ++it) {
		print(*it, level+1);
	}
}

class NodeTest {
public:
	void setUp();
	void tearDown();
	void testAddChild();
	void testIterator();
	void testFindRoot();
private:
	Node *nodes[NUMBER_OF_ITEMS], *root;
};

void NodeTest::setUp() {
	
	Tag tag;
	
	// Set up
	cout << "Setting up..." << endl;
	root = new Node(tag);
	for (int i=0; i<NUMBER_OF_ITEMS; ++i) {
		nodes[i] = new Node(tag);
	}
}

void NodeTest::tearDown() {
	
	cout << "\nTearing down..." << endl;
	Node::destroy(root);
}

void NodeTest::testAddChild() {
	
	// Add children
	cout << "\nAdding children..." << endl;
	root->addChild(nodes[0]);
	for (int i=0; i<NUMBER_OF_ITEMS-1; ++i)
		nodes[i]->addChild(nodes[i+1]);
	print(root, 1);
}

void NodeTest::testFindRoot() {
	
	Node *from, *result;
	
	// Find root
	cout << "\nFinding root..." << endl;
	from = nodes[NUMBER_OF_ITEMS-1];
	result = Node::findRoot(from);
	cout << "  From   = " << from << endl;
	cout << "  Root   = " << root << endl;
	cout << "  Result = " << result << endl;
	assert(result == root);
}

void NodeTest::testIterator() {
	
	Node::iterator it;
	
	// Iterate
	cout << "\nIterating through root..." << endl;
	for (it=root->begin(); it!=root->end(); ++it) {
		cout << "  " << *(*it) << " " << (*it) << endl;
	}
}

/* Run the test. */
int main() {
	
	NodeTest test;
	
	try {
		test.setUp();
		test.testAddChild();
		test.testFindRoot();
		test.testIterator();
		test.tearDown();
	} catch (exception &e) {
		cerr << e.what() << endl;
	}
}

