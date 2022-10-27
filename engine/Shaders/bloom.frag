#version 330 core
out vec4 Color;

in vec2 TexCoords;

uniform sampler2D screenTexture;
void main()
{           
    vec4 FragColor = vec4(texture(screenTexture, TexCoords).rgb, 1.0);
    //float brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(FragColor.r > 1.0 ||FragColor.g > 1.0 ||FragColor.b > 1.0 )
    {
        FragColor.r += FragColor.g*0.05f + FragColor.b*0.05f;
        FragColor.g += FragColor.r*0.05f + FragColor.b*0.05f;
        FragColor.b += FragColor.g*0.05f + FragColor.r*0.05f;
        Color = vec4(FragColor.rgb, 1.0);
	}
    else
		Color = vec4(0.0,0.0,0.0, 1.0);
    
}