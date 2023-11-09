// версия языка шейдера (3.3)

// выходные параметры - цвет рисования
layout(location = 0) out vec4 OutColor;

layout(binding = 0) uniform sampler2D InPosId;
layout(binding = 1) uniform sampler2D InNormalIsShade;
layout(binding = 2) uniform sampler2D InKa;
layout(binding = 3) uniform sampler2D InKd;
layout(binding = 4) uniform sampler2D InKsPh;
layout(binding = 5) uniform sampler2D InColor;

layout(binding = 8) uniform sampler2D ShadowMap;

uniform vec3 CamLoc, LightDir, LightColor;
uniform float Time, FrameW, FrameH;
uniform mat4 MatrShadow;

// входные параметры (varying)

void main( void )
{
  ivec2 sc = ivec2(gl_FragCoord.xy);
  vec4 NiS = texelFetch(InNormalIsShade, sc, 0);
  vec4 RealC;

  if (NiS.a == 0)
    RealC = texelFetch(InColor, sc, 0);
  else
  {
    vec3 L = LightDir;//normalize(vec3(sin(Time) * 100, 100, sin(Time) * 100));
    vec3 LC = LightColor;//vec3(1, 1, 1);            
    vec3 color = vec3(0);
    vec3 P = texelFetch(InPosId, sc, 0).xyz;
    vec3 N = NiS.xyz; 
    vec3 V = normalize(P - CamLoc);
    vec3 RealKa = texelFetch(InColor, sc, 0).xyz;
    vec3 RealKd = texelFetch(InKd, sc, 0).xyz;
    vec4 RealKsPh = texelFetch(InKsPh, sc, 0);
    vec3 RealKs = RealKsPh.xyz;
    float RealPh = RealKsPh.w;

    // Ambient
    color = texelFetch(InColor, sc, 0).rgb;
  	
    N = faceforward(N, V, N);

    // Diffuse
    color += max(0, dot(N, L)) * RealKd * LC;

    // Specular
    vec3 R = reflect(V, N);
        
    color += pow(max(0, dot(R, L)), RealPh) * RealKs * LC;

    vec3 pos = ((MatrShadow * vec4(P, 1)).xyz + 1) / 2;
    float shadow = 1;
    if (pos.x > 0 && pos.y > 0 && pos.x < 1 && pos.y < 1)
    {
      shadow = 1;

      if (texture(ShadowMap, pos.xy).r < pos.z)
        shadow = 0.8;
    }
   
    RealC = vec4(color * shadow, 1); 
  }
  
    OutColor = RealC;
}