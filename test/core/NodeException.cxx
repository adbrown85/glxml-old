/*
 * NodeException.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "NodeException.hpp"

/** @brief Unit test for NodeException. */
class NodeExceptionTest {
public:
	void setUp();
	void testThrow();
private:
	Tag tag;
};

void NodeExceptionTest::setUp() {
	
	tag.setFilename("NodeExceptionTest.xml");
	tag.setLine(27);
}

void NodeExceptionTest::testThrow() {
	
	NodeException e(tag);
	e << "This is a NodeException!";
	throw e;
}

/* Runs the test. */
int main(int argc, char *argv[]) {
	
	NodeExceptionTest test;
	
	try {
		test.setUp();
		test.testThrow();
	} catch (exception &e) {
		cerr << e.what() << endl;
	}
	return 0;
}

