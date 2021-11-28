#version 330

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragmentPosition;

out vec4 colour;


struct Light
{
	vec3 colour; //Em
	float ambientIntensity; //Ia
	float diffuseIntensity; //Id
	float specularIntensity; //Is
};

struct DirectionalLight 
{
	Light base;
	vec3 direction; //D
};

struct PointLight
{
	Light base;
	vec3 position; //PL
	float constant; //k0
	float linear;   //k1
	float exponent; //k2
};

struct Material
{
	float ambientIntensity;
	float diffuseIntensity;
	float specularIntensity;

	vec4 ambientColour; // Ka
	vec4 diffuseColour; // Kd
	vec4 specularColour;// Ks
	
	float shininess; // Exp m
};

uniform DirectionalLight directionalLight;
uniform PointLight pointLight;

uniform sampler2D theTexture;
uniform Material material;

uniform vec3 eyePosition;

vec4 CalcMaterialColourByDirection(Light light, vec3 direction)
{
	vec4 ambientColour = material.ambientColour * light.ambientIntensity * vec4(light.colour, 1.0);
	
	float diffuseFactor = max(dot(normalize(Normal), normalize((-1)*direction)), 0.0f);
	
	vec4 diffuseColour = material.diffuseColour * light.diffuseIntensity * diffuseFactor * vec4(light.colour, 1.0);
	vec4 specularColour = vec4(0, 0, 0, 0);
	
	if(diffuseFactor > 0.0f)
	{
		vec3 fragToEye = normalize(eyePosition - FragmentPosition);
		vec3 reflectedVertex = normalize(reflect(direction, normalize(Normal)));
		
		float specularFactor = dot(fragToEye, reflectedVertex);
		if(specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColour = vec4(vec3(material.specularColour) * light.specularIntensity * specularFactor * light.colour, 1.0f);
		}
	}

	return (ambientColour + diffuseColour + specularColour);
}

vec4 CalcDirectionalLight()
{
	return CalcMaterialColourByDirection(directionalLight.base, directionalLight.direction) + vec4(directionalLight.base.colour, 1.0) * directionalLight.base.ambientIntensity;
}

vec4 CalcPointLight()
{
	vec4 totalColour = vec4(0, 0, 0, 0);
	vec3 direction = FragmentPosition - pointLight.position;
	float distance = length(direction);
	direction = normalize(direction);
		
	vec4 colour = CalcMaterialColourByDirection(pointLight.base, direction);
	float attenuation = pointLight.exponent * distance * distance +
						pointLight.linear * distance +
						pointLight.constant;
		
	totalColour = (colour / attenuation);
	
	return totalColour;
}


void main()
{
	vec4 finalColour = CalcDirectionalLight();
	finalColour += CalcPointLight();

	colour = texture(theTexture, TexCoord) * finalColour;
}