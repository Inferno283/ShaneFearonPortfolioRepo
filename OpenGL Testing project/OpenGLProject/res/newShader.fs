in vec3 pos_eye;
in vec3 n_eye;
uniform samplerCube skybox;
uniform mat4 view; // view matrix
out vec4 frag_colour;

void main() {
  /* reflect ray around normal from eye to surface */
  vec3 incident_eye = normalize(pos_eye);
  vec3 normal = normalize(n_eye);

  vec3 reflected = reflect(normal, incident_eye);
  // convert from eye to world space
  reflected = vec3(inverse(view) * vec4(reflected, 0.0));

  frag_colour = texture(skybox, reflected);
}