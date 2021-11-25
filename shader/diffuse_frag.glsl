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

uniform vec3 ViewPos; // new

// The vertex shader will feed this input
in vec2 texCoord;

in vec3 Position; // new
in vec3 FragPos; // new

// Wordspace normal passed from vertex shader
in vec4 normal;

in vec3 Normal; // new

// The final color
out vec4 FragmentColor;

void main() {
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(LightPosition - FragPos);

  // Compute ambient lightning
  float ambientStrength = 0.25f;
  vec3 ambient = ambientStrength * LightColor;

  // Compute diffuse lighting
  //float diffuse = max(dot(normal, vec4(normalize(LightDirection), 1.0f)), 0.0f);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * LightColor;
  vec3 objectColor = texture(Texture, vec2(texCoord.x, 1.0 - texCoord.y) + TextureOffset).xyz;

  // Compute specular lightning
  float specularStrength = 0.1;
  vec3 viewDir = normalize(LightPosition - FragPos);
  vec3 reflectDir = reflect(-LightDirection, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
  vec3 specular = specularStrength * spec * LightColor;

  vec3 phong = (ambient + diffuse + specular) * objectColor;

  FragmentColor = vec4(phong, 1.0);
  FragmentColor.a = Transparency;
}
