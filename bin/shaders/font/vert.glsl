
// кто куда приходит
layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InTexCoord;
layout(location = 2) in vec3 InNormal;
layout(location = 3) in vec4 InColor;

uniform mat4 MatrWvp;
uniform mat4 MatrTrans;
uniform mat4 MatrWorld;
uniform float FrameW, FrameH;

out vec2 DrawTexCoord;
out vec3 DrawPos, DrawNormal, DrawColor;

mat4 MatrOrtho( float L, float R, float B, float T, float N, float F )
{
  return mat4(
      vec4(2 / (R - L), 0, 0, 0),
      vec4(0, 2 / (T - B), 0, 0),
      vec4(0, 0, -2 / (F - N), 0),
      vec4(-(R + L) / (R - L), -(T + B) / (T - B), -(F + N) / (F - N), 1));
}

mat4 MatrScale( float S )
{
  return mat4(vec4(S, 0, 0, 0),
              vec4(0, S, 0, 0),
              vec4(0, 0, S, 0),
              vec4(0, 0, 0, 1));
}

void main( void )
{
  //gl_Position = MatrWvp * vec4(InPosition, 1);
  gl_Position = MatrOrtho(0, FrameW, -FrameH, 0, -1, 1) * MatrScale(28) * MatrWorld * vec4(InPosition, 1);
  DrawTexCoord = InTexCoord;
  DrawNormal = InNormal;
  DrawPos = InPosition;
  DrawColor = InColor.rgb;
}