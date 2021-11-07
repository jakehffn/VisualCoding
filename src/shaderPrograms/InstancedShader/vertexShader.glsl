#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;
// Model Matrix
layout(location = 3) in mat4 M;

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;

out vec3 colorBase;

// Values that stay constant for the whole mesh.
uniform mat4 P;
uniform mat4 V;
uniform vec3 LightPosition_worldspace;

uniform float yLow;
uniform float yHigh;
uniform vec3 lowColor;
uniform vec3 highColor;

void main(){

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  P * V * M * vec4(vertexPosition_modelspace,1);

	// Position of the vertex, in worldspace : M * position
	Position_worldspace = (M * vec4(vertexPosition_modelspace,1)).xyz;

	float yRange = yHigh - yLow;
	float yReal = abs(Position_worldspace.y - yLow);
	// float yReal = yLow;
	float yRealInv = abs(yRange - yReal);

	mat3 lowP = mat3(yRealInv/yRange);
	mat3 highP = mat3(yReal/yRange);
	

	colorBase = (lowP * lowColor) + (highP * highColor);
	// colorBase = highColor;
	// colorBase = vec3(1, 1, 1);

	// Vector that goes from the vertex to the camera, in camera space.
	// In camera space, the camera is at the origin (0,0,0).
	vec3 vertexPosition_cameraspace = ( V * M * vec4(vertexPosition_modelspace,1)).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

	// Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
	vec3 LightPosition_cameraspace = ( V * vec4(LightPosition_worldspace,1)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;
	
	// Normal of the the vertex, in camera space
	Normal_cameraspace = ( V * M * vec4(vertexNormal_modelspace,0)).xyz; // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
	
	// UV of the vertex. No special space for this one.
	UV = vertexUV;
}