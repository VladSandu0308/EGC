#version 330
 
uniform sampler2D texture;
 
/* Get color value from vertex shader */
in vec2 frag_coord;
in vec3 world_position;
in vec3 world_normal;

/* Uniforms for light properties */
uniform vec3 lightDirection;
uniform vec3 lightPosition1;
uniform vec3 lightPosition2;
uniform vec3 eyePosition;

uniform float materialKd;
uniform float materialKs;
uniform int materialShininess;

uniform float cutOffAngle;

layout(location = 0) out vec4 out_color;

void main()
{
    vec4 texturedColour = texture2D(texture, frag_coord);

    vec3 N = normalize(world_normal);
	vec3 L1 = normalize(lightPosition1 - world_position);
	vec3 L2 = normalize(lightPosition2 - world_position);
	vec3 V = normalize(eyePosition - world_position);
	vec3 H1 = normalize(L1 + V);
	vec3 H2 = normalize(L2 + V);

	/* Define ambient light component */
	float ambientLight = .25f;

	/* Compute diffuse light components */
	float diffuseLight1 = materialKd * max(dot(N, L1), 0.f);
	float diffuseLight2 = materialKd * max(dot(N, L2), 0.f);

	/* Compute specular light component */
	float specularLight1 = 0.f;
	float specularLight2 = 0.f;

	if (diffuseLight1 > 0.f)
	{
		specularLight1 = materialKs * pow(max(dot(N, H1), 0.f), materialShininess);
	}
	if (diffuseLight2 > 0.f)
	{
		specularLight2 = materialKs * pow(max(dot(N, H2), 0.f), materialShininess);
	}

	/* Compute light */
	float light1 = 0.f;
	float light2 = 0.f;

	float cutOffRad			= radians(cutOffAngle);
	float spotLight1		= dot(-L1, lightDirection);
	float spotLight2		= dot(-L2, lightDirection);
	float spotLightLimit	= cos(cutOffRad);
		
	if (spotLight1 > spotLightLimit)
	{	 
		/* Quadratic attenuation */
		float linearAtt			= (spotLight1 - spotLightLimit) / (1.f - spotLightLimit);
		float lightAttFactor	= linearAtt * linearAtt;
		light1					= lightAttFactor * (diffuseLight1 + specularLight1);
	}

	if (spotLight2 > spotLightLimit)
	{	 
		/* Quadratic attenuation */
		float linearAtt			= (spotLight2 - spotLightLimit) / (1.f - spotLightLimit);
		float lightAttFactor	= linearAtt * linearAtt;
		light2					= lightAttFactor * (diffuseLight2 + specularLight2);
	}

	out_color = texturedColour * (light1 + light2 + ambientLight);
}