#version 450 core
layout (location = 0) in vec3 a_Pos;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

in vec3 u_albedo;
out vec3 v_albedo;

void main()
{
    v_albedo = u_albedo;
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Pos, 1.0);
}
