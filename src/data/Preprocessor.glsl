/*
 * Preprocessor.glsl
 *     Tests Preprocessor class.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#define COOL_MACRO
#include "../../input/Ray.glsl"
#include "../../input/Ray.glsl"



void main() {
	
	// A comment!
	gl_FragColor = gl_TexCoord[0];		// Another comment
	/* This one might be tricky! */
}
