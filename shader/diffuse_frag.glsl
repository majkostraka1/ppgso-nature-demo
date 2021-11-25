#version 330
// A texture is expected as program attribute
uniform sampler2D Texture;

// Direction of light
uniform vec3 LightDirection;

// Lightning color
uniform vec3 LightColor;

// Position of light
uniform vec3 LightPosition;

// (optional) Transparency
uniform float Transparency;

// (optional) Texture offset
uniform vec2 TextureOffset;

// The vertex shader will feed this input
in vec2 texCoord;

// Wordspace normal passed from vertex shader
in vec4 normal;

// The final color
out vec4 FragmentColor;

void main() {
  // Compute ambient lightning
  float ambientStrength = 0.25f;
  vec3 ambient = ambientStrength * LightColor;

  // Compute specular lightning
  float specularStrength = 0.5;
  vec3 viewDir = normalize(LightPosition - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);

  // Compute diffuse lighting
  float diffuse = max(dot(normal, vec4(normalize(LightDirection), 1.0f)), 0.0f);

  vec3 objectColor = texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y)).xyz;

  vec3 result = (ambient + diffuse) * objectColor;

  FragmentColor = vec4(result, 1.0f);

  // Lookup the color in Texture on coordinates given by texCoord
  // NOTE: Texture coordinate is inverted vertically for compatibility with OBJ
  //FragmentColor = texture(Texture, vec4(result, 1.0) + TextureOffset);
  //vec2(texCoord.x, 1.0 - texCoord.y)
  FragmentColor.a = Transparency;
}
