#version 330
 
uniform sampler2D terrainTexture;
 
/* Get color value from vertex shader */
in vec2 frag_coord;
in vec3 world_position;
in vec3 world_normal;

/* Uniforms for light properties */
uniform vec3 lightDirection;
uniform vec3 lightPosition;
uniform vec3 eyePosition;

uniform float materialKd;
uniform float materialKs;
uniform int materialShininess;

uniform float cutOffAngle;

layout(location = 0) out vec4 out_color;

void main()
{
    vec4 texturedColour = texture2D(terrainTexture, frag_coord);

    vec3 N = normalize(world_normal);
	vec3 L = normalize(lightPosition - world_position);
	vec3 V = normalize(eyePosition - world_position);
	vec3 H = normalize(L + V);
	vec3 R = normalize(reflect(L, world_normal));

	/* Define ambient light component */
	float ambientLight = .25f;

	/* Compute diffuse light component */
	float diffuseLight = materialKd * max(dot(normalize(N), L), 0.f);

	/* Compute specular light component */
	float specularLight = 0.f;

	if (diffuseLight > 0.f)
	{
		specularLight = materialKs * pow(max(dot(N, H), 0.f), materialShininess);
	}

	/* Compute light */
	float light = 0.f;

	float cutOffRad			= radians(cutOffAngle);
	float spotLight			= dot(-L, lightDirection);
	float spotLightLimit	= cos(cutOffRad);
		
	if (spotLight > spotLightLimit)
	{	 
		/* Quadratic attenuation */
		float linearAtt			= (spotLight - spotLightLimit) / (1.f - spotLightLimit);
		float lightAttFactor	= linearAtt * linearAtt;
		light					= ambientLight + lightAttFactor * (diffuseLight + specularLight);
	} else
	{
	   /* There is no spot light, but there is light from other objects */
		light = ambientLight;
	}

	out_color = texturedColour * light;
}