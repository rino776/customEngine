#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D ourTexture;

uniform vec3 lightPos;
uniform vec3 viewPos;

vec3 lightColour = vec3(1,1,1);

float ambientStrength = 0.2;
float specularStrength = 0.5;



void main()
{
    vec4 TexColour = texture(ourTexture, TexCoord);

    if(TexColour.a < 0.1){
        discard;
    }


    vec3 ambient = ambientStrength * lightColour;

    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir),0.0);
    vec3 diffuse = diff * lightColour;

    //specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir),0.0),64);
    vec3 specular = specularStrength * spec * lightColour;
 //   
    //combine everything
    vec3 result = (ambient + diffuse + specular) * ourColor;

    FragColor = TexColour * vec4(result,1);
	//FragColor = vec4(ourColor,1.0);
}
