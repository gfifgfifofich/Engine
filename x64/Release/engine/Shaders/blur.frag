#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D image;

uniform sampler2D downscale;

uniform bool horizontal;
uniform float weight[8] = float[](0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162, 0.0162162162, 0.0162162162, 0.0162162162);//(0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

uniform float textureweight[8] = float[](512.0f,343.0f,216.0f,125.0f,64.0f,27.0f,8.0f,1.0f);


uniform float strength = 1.0f;


uniform int it = 0;


void main()
{             
     
     vec2 tex_offset = 1.0 / textureSize(downscale, 0); 
     vec2 tex_offset_img = 1.0 / textureSize(image, 0); 
     vec3 result = texture(image, TexCoords).rgb  ;
    /*
  if(horizontal)
     {
         for(int i = 1; i < 5; ++i)
         {
            result += (texture(image, TexCoords + vec2(tex_offset_img.x * i, 0.0)).rgb+texture(downscale, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb) * weight[i];
            result += (texture(image, TexCoords - vec2(tex_offset_img.x * i, 0.0)).rgb+texture(downscale, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb) * weight[i];
         }
     }
     else
     {
         for(int i = 1; i < 5; ++i)
         {
            result += (texture(image, TexCoords + vec2(0.0,tex_offset_img.x * i)).rgb+texture(downscale, TexCoords + vec2(0.0,tex_offset.x * i)).rgb)* weight[i];
            result += (texture(image, TexCoords - vec2(0.0,tex_offset_img.x * i)).rgb+texture(downscale, TexCoords - vec2(0.0,tex_offset.x * i)).rgb)* weight[i];
         }
     }*/
    
    

     //FragColor = vec4(result*textureweight[it]*0.007704160246*strength, 1.0);
     //FragColor = vec4(texture(downscale, TexCoords ).rgb+result, 1.0);
     FragColor = vec4(texture(downscale, TexCoords ).rgb+result, 1.0);
}


    
    

    /*
    
    if(horizontal)
     {
         for(int i = 1; i < 5; ++i)
         {
            result += (texture(image, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb+texture(downscale, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb) * weight[i]*strength;//
            result += (texture(image, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb+texture(downscale, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb) * weight[i]*strength;//
         }
     }
     else
     {
         for(int i = 1; i < 5; ++i)
         {
            result +=(texture(image, TexCoords + vec2(0.0,tex_offset.x * i)).rgb+texture(downscale, TexCoords + vec2(0.0,tex_offset.x * i)).rgb)* weight[i]*strength;// 
            result += (texture(image, TexCoords - vec2(0.0,tex_offset.x * i)).rgb+texture(downscale, TexCoords - vec2(0.0,tex_offset.x * i)).rgb)* weight[i]*strength;//
         }
     }
    


    if(horizontal)
     {
         for(int i = 1; i < 5; ++i)
         {
            result += texture(downscale, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i]*strength;
            result += texture(downscale, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i]*strength;
         }
     }
     else
     {
         for(int i = 1; i < 5; ++i)
         {
            result += texture(downscale, TexCoords + vec2(0.0,tex_offset.x * i)).rgb* weight[i]*strength;
            result += texture(downscale, TexCoords - vec2(0.0,tex_offset.x * i)).rgb* weight[i]*strength;
         }
     }
    */