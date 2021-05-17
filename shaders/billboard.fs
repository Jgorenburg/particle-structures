#version 400

in vec2 uv;
in vec4 color;
uniform sampler2D image;

out vec4 FragColor;

void main()
{
   FragColor = color;// * texture(image, uv);
  //FragColor = vec4(1, 0, 0, 1);
}
