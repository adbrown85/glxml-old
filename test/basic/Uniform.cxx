/*
 * Uniform.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Uniform.hpp"
#include "Tester.hpp"
#include "BasicFactory.hpp"


Program* search(Node *node) {
	
	Node::iterator it;
	queue<Node*> Q;
	Program *program;
	
	Q.push(node);
	while (!Q.empty()) {
		node = Q.front();
		program = dynamic_cast<Program*>(node);
		if (program != NULL)
			return program;
		for (it=node->begin(); it!=node->end(); ++it)
			Q.push(*it);
		Q.pop();
	}
	return NULL;
}


void testGetUniformsFor(Scene *scene) {
	
	map<string,UniformInfo> uniforms;
	map<string,UniformInfo>::iterator it;
	Program *program;
	
	program = search(scene->getRoot());
	if (program != NULL) {
		uniforms = Uniform::getUniformsFor(program);
		for (it=uniforms.begin(); it!=uniforms.end(); ++it) {
			cout << (it->first) << " " << (it->second.type) << endl;
		}
	}
}


int main(int argc,
         char *argv[]) {
	
	Toolkit toolkit(argc, argv);
	Tester tester;
	
	BasicFactory::install();
	
	tester.open("Uniform.xml");
	testGetUniformsFor(tester.getScene());
	tester.start();
	
	return 0;
}

