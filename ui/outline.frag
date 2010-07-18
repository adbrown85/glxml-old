/*
 * outline.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
#include "../glsl/Colors.glsl"
out vec4 FragColor;


void main() {
	
	gl_FragDepth = gl_FragCoord.z - 0.0005;
	FragColor = YELLOW;
}

