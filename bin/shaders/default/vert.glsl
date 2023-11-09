layout(location=0) in vec3 inPos;
layout(location=3) in vec4 inCol;

uniform mat4 MatrWvp;

out vec4 outCol;
out vec3 outPos;

void main( void )
{
  gl_Position = MatrWvp * vec4(inPos, 1);
  outCol = inCol;
  outPos = inPos;
}