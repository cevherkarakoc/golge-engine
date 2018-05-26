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
  float base = 10.0;
  float x = 1.0;
  if(order != -1000){
    x = remap(order, -base, base, 0.0, 0.99) ;;
  }
  
  gl_FragDepth = x ;
  
  vec4 tex = texture(material.diffuse, texCoord);


  if(tex.a == 0.0) {
    discard;
  }


  FragColor = tex;
  //FragColor = vec4(vec3(x),1.0);
}