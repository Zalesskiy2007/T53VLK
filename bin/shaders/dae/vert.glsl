layout(location=0) in vec3 inPos;
layout(location=1) in vec2 inTexCoord;
layout(location=2) in vec3 inNorm;
layout(location=3) in vec4 inCol;
layout(location=4) in vec4 inGm;
layout(location=5) in vec4 inGw;

uniform mat4 MatrWvp;
uniform mat4 MatrWorld;

layout(std430, binding = 0) buffer MBuffer
{
  mat4 IBM[];
};

layout(std430, binding = 1) buffer MBuffer2
{
  mat4 MatrD[];
};

out vec4 outCol;
out vec4 outGw;
out vec4 outGm;
out vec3 outPos;
out vec2 outTexCoord;
out vec3 outNorm;

void main( void )
{
  float sum = inGw.x;
  if (inGw.y != -1)
    sum += inGw.y;
  if (inGw.z != -1)
    sum += inGw.z;
  if (inGw.w != -1)
    sum += inGw.w;
  float k = 1 / sum;

  vec4 vpos = (MatrD[int(inGm.x)] * (IBM[int(inGm.x)] * vec4(inPos, 1))) * inGw.x * k;
  if (inGm.y != -1)
    vpos += (MatrD[int(inGm.y)] * (IBM[int(inGm.y)] * vec4(inPos, 1))) * inGw.y * k;
  if (inGm.z != -1)
    vpos += (MatrD[int(inGm.z)] * (IBM[int(inGm.z)] * vec4(inPos, 1))) * inGw.z * k;
  if (inGm.w != -1)
    vpos += (MatrD[int(inGm.w)] * (IBM[int(inGm.w)] * vec4(inPos, 1))) * inGw.w * k;

  gl_Position = MatrWvp * vec4(vpos.xyz, 1);
  outCol = inCol;
  outNorm = inNorm;
  outPos = (MatrWorld * vec4(vpos.xyz, 1)).xyz;
  outTexCoord = inTexCoord; 
  outGm = inGm;
  outGw = inGw;
}