/*
 * Replica.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLXML_REPLICA_HPP
#define GLXML_REPLICA_HPP
#include "glxml_common.h"
#include "Clone.hpp"
#include "Replacement.hpp"
#include "Placeholder.hpp"
using namespace std;


/** @brief Smart instance of a group capable of making replacements.
 * @ingroup advanced
 */
class Replica : public Clone {
public:
	Replica(const Tag &tag);
	virtual void apply();
	virtual void associate();
	virtual void associateAfter();
	virtual void finalize();
	virtual void finalizeAfter();
	virtual void remove();
	virtual string toString() const;
protected:
	void findReplacements();
	void applyReplacements();
	void removeReplacements();
private:
	map<Placeholder*,Replacement*> replacements;
};


#endif
