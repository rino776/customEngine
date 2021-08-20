#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    vec4 TexColour = texture(ourTexture, TexCoord);

  //  if(TexColour.a < 0.1){
//        discard;
//   }

    FragColor = TexColour * vec4(ourColor, 1.0);

//	FragColor = vec4(ourColor,1.0);

}
