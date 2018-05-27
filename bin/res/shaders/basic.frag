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
in vec2 orginalTexCoord;
in vec3 fragPos;

out vec4 FragColor;
void main() {
  float base = 10.0;
  float x = 1.0;
  if(order != -1000){
    x = remap(order, -base, base, 0.0, 0.999) ;;
  }
  
  float d = remap(abs(orginalTexCoord.x - 0.5), 0.0, .5, 0.5 , 0.0);

  gl_FragDepth = x + (d/(4*base)) ;
  
  vec4 tex = texture(material.diffuse, texCoord);

  if(tex.a == 0.0) {
    discard;
  }

  FragColor = tex;
  //FragColor = vec4(vec3(gl_FragDepth),1.0);
}