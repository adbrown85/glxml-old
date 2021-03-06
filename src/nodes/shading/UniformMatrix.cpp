/*
 * UniformMatrix.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "UniformMatrix.hpp"

/** @throw NodeException if matrix type not supported. */
UniformMatrix::UniformMatrix(const Tag &tag) : Uniform(tag) {
	
	// Find matrix type
	if (tag.get("as", as, false)) {
		setTypeFromAs();
	} else {
		setTypeFromName();
	}
	
	// Light
	light = NULL;
	tag.get("of", of, false, false);
}

/** Finds the light. */
void UniformMatrix::associate() {
	
	Uniform::associate();
	
	if (!of.empty()) {
		findLight();
	}
}

/** @throw NodeException if light named @e of cannot be found. */
void UniformMatrix::findLight() {
	
	light = Light::search(Node::findRoot(this), of);
	if (light == NULL) {
		NodeException e(getTag());
		e << "[UniformMatrix] Light '" << of << "' could not be found.";
		throw e;
	}
}

bool UniformMatrix::hasChild(Node *node, const string &name) {
	
	Node::iterator it;
	UniformMatrix *uniform;
	
	for (it=node->begin(); it!=node->end(); ++it) {
		uniform = dynamic_cast<UniformMatrix*>((*it));
		if ((uniform != NULL) && (uniform->getName() == name)) {
			return true;
		}
	}
	return false;
}

bool UniformMatrix::isDefault(const string &name, GLenum type) {
	
	return isMatrixType(type) && isDefaultName(name);
}

/** @return True if @e name matches one of the default matrix names. */
bool UniformMatrix::isDefaultName(const string &name) {
	
	return ((name == DEFAULT_MODELVIEW_MATRIX_NAME)
	        || (name == DEFAULT_PROJECTION_MATRIX_NAME)
	        || (name == DEFAULT_MODELVIEW_PROJECTION_MATRIX_NAME)
	        || (name == DEFAULT_NORMAL_MATRIX_NAME)
	        || (name == DEFAULT_IDENTITY_MATRIX_NAME)
	        || (name == DEFAULT_LIGHT_MATRIX_NAME));
}

/** @throw NodeException if @e as not supported. */
void UniformMatrix::setTypeFromAs() {
	
	if (as == "modelview") {
		matrixType = MODELVIEW;
	} else if (as == "projection") {
		matrixType = PROJECTION;
	} else if (as == "modelviewprojection") {
		matrixType = MODELVIEW_PROJECTION;
	} else if (as == "normal") {
		matrixType = NORMAL;
	} else if (as == "model") {
		matrixType = MODEL;
	} else if (as == "identity") {
		matrixType = IDENTITY;
	} else if (as == "light") {
		matrixType = LIGHT;
	} else {
		NodeException e(tag);
		e << "[UniformMatrix] Matrix '" << as << "' not supported.";
		throw e;
	}
}

/** @throw NodeException if default name not supported. */
void UniformMatrix::setTypeFromName() {
	
	if (getName() == DEFAULT_MODELVIEW_PROJECTION_MATRIX_NAME) {
		matrixType = MODELVIEW_PROJECTION;
		as = "modelviewprojection";
	} else if (getName() == DEFAULT_MODELVIEW_MATRIX_NAME) {
		matrixType = MODELVIEW;
		as = "modelview";
	} else if (getName() == DEFAULT_NORMAL_MATRIX_NAME) {
		matrixType = NORMAL;
		as = "normal";
	} else if (getName() == DEFAULT_MODEL_MATRIX_NAME) {
		matrixType = MODEL;
		as = "model";
	} else if (getName() == DEFAULT_PROJECTION_MATRIX_NAME) {
		matrixType = PROJECTION;
		as = "projection";
	} else if (getName() == DEFAULT_IDENTITY_MATRIX_NAME) {
		matrixType = IDENTITY;
		as = "identity";
	} else if (getName() == DEFAULT_LIGHT_MATRIX_NAME) {
		matrixType = LIGHT;
		as = "light";
	} else {
		NodeException e(tag);
		e << "[UniformMatrix] Unrecognized default name and no 'as' attribute.";
		throw e;
	}
}

void UniformMatrix::apply() {
	
	if (!hasLocation())
		return;
	
	switch (matrixType) {
	case MODEL:
		State::getModelMatrix(value);
		glUniformMatrix4fv(getLocation(), 1, false, value);
		break;
	case MODELVIEW:
		State::getModelViewMatrix(value);
		glUniformMatrix4fv(getLocation(), 1, false, value);
		break;
	case PROJECTION:
		State::getProjectionMatrix(value);
		glUniformMatrix4fv(getLocation(), 1, false, value);
		break;
	case MODELVIEW_PROJECTION:
		State::getModelViewProjectionMatrix(value);
		glUniformMatrix4fv(getLocation(), 1, false, value);
		break;
	case NORMAL:
		State::getNormalMatrix(value);
		glUniformMatrix3fv(getLocation(), 1, false, value);
		break;
	case IDENTITY:
		State::getIdentityMatrix(value);
		glUniformMatrix4fv(getLocation(), 1, false, value);
		break;
	case LIGHT:
		if (light != NULL) {
			light->getLightMatrix(value);
			glUniformMatrix4fv(getLocation(), 1, false, value);
		}
		break;
	default:
		NodeException e(getTag());
		e << "[UniformMatrix] Matrix type not supported.";
		throw e;
	}
}

string UniformMatrix::toString() const {
	
	ostringstream stream;
	
	stream << Uniform::toString();
	stream << " as='" << as << "'";
	if (!of.empty())
		stream << " of='" << of << "'";
	return stream.str();
}
