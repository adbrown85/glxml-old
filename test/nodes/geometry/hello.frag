#version 130

/* Uniforms */
uniform vec4 Color = vec4(1.0);

/* Outputs */
out vec4 FragColor;


/** Color fragments */
void main() {
	
	FragColor = Color;
}