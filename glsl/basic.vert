/*
 * basic.vert
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130
uniform mat4 MVMatrix;
uniform mat4 MVPMatrix;
uniform mat3 NormalMatrix;
uniform vec3 LightPosition;
uniform float Ambient;
in vec4 MCVertex;
in vec3 MCNormal;
in vec3 TexCoord0;
out float LightIntensity;
out vec3 TexCoord;
out vec3 Normal;


void main() {
	
	vec3 ecPosition = vec3(MVMatrix * MCVertex);
	vec3 tnorm = normalize(NormalMatrix * MCNormal);
	vec3 lightVec = normalize(LightPosition - ecPosition);
	vec3 viewVec = normalize(-ecPosition);
	
	// Computations
	LightIntensity = Ambient + max(dot(lightVec, tnorm), 0.0);
	TexCoord = TexCoord0;
	gl_Position = MVPMatrix * MCVertex;
}

