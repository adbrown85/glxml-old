#version 130

/* Uniforms */
uniform mat4 MVPMatrix = mat4(1.0);

/* Inputs */
in vec4 MCVertex;


/** Transform incoming vertices */
void main() {
    
    gl_Position = MVPMatrix * MCVertex; 
}