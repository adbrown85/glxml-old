/*
 * OrganizeFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "OrganizeFactory.hpp"
bool OrganizeFactory::installed=false;

void OrganizeFactory::install() {
	
	// Check if already called
	if (installed)
		return;
	installed = true;
	
	// Tags
	Factory::install("branch", &createBranch);
	Factory::install("choose", &createChoose);
	Factory::install("clone", &createClone);
	Factory::install("group", &createGroup);
	Factory::install("instance", &createInstance);
	Factory::install("placeholder", &createPlaceholder);
	Factory::install("replacement", &createReplacement);
	Factory::install("replica", &createReplica);
	Factory::install("sort", &createSort);
}

Node* OrganizeFactory::createBranch(const Tag &t) {
	return new Branch(t);
}

Node* OrganizeFactory::createChoose(const Tag &t) {
	return new Choose(t);
}

Node* OrganizeFactory::createClone(const Tag &tag) {
	return new Clone(tag);
}

Node* OrganizeFactory::createGroup(const Tag &tag) {
	return new Group(tag);
}

Node* OrganizeFactory::createInstance(const Tag &tag) {
	return new Instance(tag);
}

Node* OrganizeFactory::createPlaceholder(const Tag &t) {
	return new Placeholder(t);
}

Node* OrganizeFactory::createReplacement(const Tag &t) {
	return new Replacement(t);
}

Node* OrganizeFactory::createReplica(const Tag &t) {
	return new Replica(t);
}

Node* OrganizeFactory::createSort(const Tag &t) {
	return new Sort(t);
}
