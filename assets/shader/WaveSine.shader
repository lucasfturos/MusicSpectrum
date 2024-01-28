#shader vertex
#version 330 core
    
layout(location = 0) in vec4 position;

uniform mat4 uMVP;

void main() {
    gl_Position = uMVP * position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 fColor;

uniform mat4 uColor;

void main() {
    fColor = uColor;
}
