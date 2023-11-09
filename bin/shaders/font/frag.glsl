layout(binding = 0) uniform sampler2D Tex0;
layout(location = 0) out vec4 OutPosId;
layout(location = 1) out vec4 OutNormalIsShade;
layout(location = 2) out vec4 OutKa;
layout(location = 3) out vec4 OutKd;
layout(location = 4) out vec4 OutKsPh;
layout(location = 5) out vec4 OutColor;

in vec2 DrawTexCoord;
in vec3 DrawPos, DrawNormal, DrawColor;

void main( void )
{
  vec4 tc = texture(Tex0, vec2(1, 1) * DrawTexCoord);

  if (tc.a < 0.6)
    discard;
  OutColor = tc;
  OutPosId = vec4(DrawPos, 1);
  OutNormalIsShade = vec4(0, 0, 0, 0);
  OutKa = vec4(0, 0, 0, 0);
  OutKd = vec4(0, 0, 0, 0);
  OutKsPh = vec4(0, 0, 0, 0);

}               	