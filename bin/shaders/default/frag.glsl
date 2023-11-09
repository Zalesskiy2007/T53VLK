in vec4 outCol;
in vec3 outPos;

layout(location = 0) out vec4 OutPosId;
layout(location = 1) out vec4 OutNormalIsShade;
layout(location = 2) out vec4 OutKa;
layout(location = 3) out vec4 OutKd;
layout(location = 4) out vec4 OutKsPh;
layout(location = 5) out vec4 OutColor;
void main( void )
{
  OutColor = outCol;
  OutPosId = vec4(outPos, 1);
  OutNormalIsShade = vec4(0, 0, 0, 0);
  OutKa = vec4(0, 0, 0, 0);
  OutKd = vec4(0, 0, 0, 0);
  OutKsPh = vec4(0, 0, 0, 0);
}