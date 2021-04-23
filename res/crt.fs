#version 330

in vec2 fragTexCoord;

uniform sampler2D texture0;

out vec4 finalColor;

uniform float time;

float rand(vec2 p)
{
  vec2 k1 = vec2(23.14069263277926, 2.665144142690225);
  return fract(cos(dot(p, k1)) * 12345.6789);
}


void main()
{
  const float renderHeight = 600;

  //curved screen
  vec2 curvature = vec2(2.25, 2.5);
  vec2 uvc = vec2(fragTexCoord.x * 2.0 - 1.0, fragTexCoord.y * 2.0 - 1.0);
  vec2 offset = abs(uvc.yx) / vec2(curvature.x, curvature.y);
  uvc = uvc + uvc * offset * offset;
  uvc = uvc * 0.5 + 0.5;

  vec3 col = texture(texture0, uvc).rgb;
  finalColor = vec4((col) * vec3(1.0), 1.0);

  // CRT lines
  vec3 lines = vec3(1.0);
  float intensity = sin(uvc.x * 1006.0 * 3.14 * 2.5);
  intensity = ((0.5 * intensity) + 0.5) * 0.9 + 0.1;
  lines *= vec3(pow(intensity, 0.05)); // .1
  intensity = sin(uvc.y * 50.0 * 3.14 * 2.5);
  intensity = ((0.5 * intensity) + 0.5) * 0.9 + 0.1;
  lines *= vec3(pow(intensity, 0.05)); // .1

  finalColor = vec4(col * lines, 1.0);

  // film grain
  vec2 uvr = fragTexCoord;
  uvr.y *= rand(vec2(uvr.y, time));
  finalColor.rgb += finalColor.rgb * (rand(uvr) * 0.5);

  // rolling scanlines
  float y = ((fragTexCoord.y + time * 20.0) / renderHeight);
  finalColor.rgb *= 1.0 - 0.25 * (sin(y * 64.0) * 0.5 + 0.5);

  // edge colors (black)
  if (uvc.x < 0 || uvc.x > 1.0 || uvc.y < 0 || uvc.y > 1.0)
    finalColor = vec4(0.0, 0.0, 0.0, 1.0);
}