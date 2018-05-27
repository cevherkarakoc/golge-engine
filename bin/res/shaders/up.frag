#version 400
struct Material {
  sampler2D diffuse;
};

float remap(float value,float rangeLow,float rangeHigh,float targetLow,float targetHigh) {
  return targetLow + (value - rangeLow) * (targetHigh - targetLow) / (rangeHigh - rangeLow);
}

uniform mat4 modelMatrix;
uniform Material material;

uniform float tileNumber;
uniform float order;

in vec2 texCoord;
in vec3 fragPos;

out vec4 FragColor;
void main() {
  gl_FragDepth = remap(modelMatrix[3].y, -10.0, 10.0, 0.0, 1.0) ;
 
  vec4 tex = texture(material.diffuse, texCoord);

  if(tex.a == 0.0) {
    discard;
  }

  FragColor = tex;
  //FragColor = vec4(vec3(gl_FragDepth), 1.0);
}