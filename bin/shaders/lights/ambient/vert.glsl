// версия языка шейдера (3.3)

// кто куда приходит
layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InTexCoord;
layout(location = 2) in vec3 InNormal;
layout(location = 3) in vec4 InColor;

// глобальные переменные (произведение матриц: World * View * Proj)
uniform mat4 MatrWvp;

// выходные параметры (varying)

void main( void )
{
  gl_Position = vec4(InPosition, 1);
}