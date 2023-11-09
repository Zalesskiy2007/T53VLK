layout(location=0) in vec3 inPos;
layout(location=1) in vec2 inTexCoord;
layout(location=2) in vec3 inNorm;
layout(location=3) in vec4 inCol;

uniform mat4 MatrWvp;
uniform mat4 MatrWorld;

out vec4 outCol;
out vec3 outPos;
out vec2 outTexCoord;
out vec3 outNorm;

void main( void )
{
  gl_Position = MatrWvp * vec4(inPos, 1);
  outCol = inCol;
  outNorm = inNorm;
  outPos = (MatrWorld * vec4(inPos, 1)).xyz;
  outTexCoord = inTexCoord;
}