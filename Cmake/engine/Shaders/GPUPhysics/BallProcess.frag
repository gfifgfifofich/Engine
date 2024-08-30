#version 330 core
out float FragValue;
// will process one layer of nn, 

uniform int inSize = 10;// X
uniform int outSize = 10;// X
uniform int InstanceCount = 1;// X
uniform int Func = 0; //Activation function of layer 

uniform sampler2D weights; // [inSize][outSize];
uniform sampler2D biases; // [outSize][1];
uniform sampler2D data_in; // [inSize][InstanceCount]
//uniform sampler2D data_out;// [outSize][InstanceCount] // this will be outputed wia FragValue

float GetBias(int i)
{
	return texture(biases,vec2( (float(i+0.5f) / inSize),0.0f)).r;
}

float GetWeight(int i)
{
	return texture(weights,vec2( (float(i+0.5f) / inSize),(gl_FragCoord.x / outSize) )).r;
}

float GetIn(int i)
{
	return texture(data_in,vec2( (float(i+0.5f) / inSize), (gl_FragCoord.y / InstanceCount))).r;
}

float Run()
{
	float sum = GetBias(int(gl_FragCoord.x));

	for(int i=0;i<inSize;i++)
	{
		sum += GetWeight(i) * GetIn(i);
	}
	return sum;
}

void main()
{
	//FragValue = texture(weights,vec2( (gl_FragCoord.y / inSize),(gl_FragCoord.x / outSize) )).r;
	//FragValue = GetIn(int(gl_FragCoord.x));
	//FragValue = GetWeight(int(gl_FragCoord.x));
	//FragValue = GetBias(int(gl_FragCoord.x));
	FragValue = Run();
}