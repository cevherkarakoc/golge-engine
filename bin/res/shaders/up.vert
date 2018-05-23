#version 400
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

uniform float columnCount;
uniform float tileNumber; 

vec2 calculateTextureCoordinate() {
  float y = floor(tileNumber/columnCount);
  float x = mod(tileNumber,columnCount);
  return  (aTexCoord + vec2(x, y ) ) * (1/columnCount) ;
}

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;
void main() {
  texCoord = calculateTextureCoordinate();
  fragPos  = vec3(modelMatrix * vec4(aPosition.xy, 0.0, 1.0));

  gl_Position = projectionMatrix * viewMatrix * vec4(fragPos, 1.0);
}