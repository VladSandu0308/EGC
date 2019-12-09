#version 330

in vec3 frag_normal;
in vec3 frag_color;
in vec3 frag_position;

uniform vec3 lightSea;
uniform vec3 viewPos;

layout(location = 0) out vec4 out_color;

void main() {
	/* Diffuse light */
	vec3 lightColor = vec3(.196078f, .6f, .8f);
	vec3 norm		= normalize(frag_normal);
	vec3 lightDir	= normalize(lightSea - frag_position);
	float diff		= max(dot(norm, lightDir), 0.f);
	vec3 diffuse	= diff * lightColor;

	/* Ambient light */
	float ambientStrength	= .25f;
	vec3 ambient			= ambientStrength * lightColor;

	/* Specular light */
	float specularStrength	= .7f;
	vec3 viewDir			= normalize(viewPos - frag_position);
	vec3 reflectDir			= reflect(-lightDir, norm);
	float spec				= pow(max(dot(viewDir, reflectDir), 0.f), 4.f);
	vec3 specular			= specularStrength * spec * lightColor; 

    vec3 result				= (ambient + diffuse + specular) * frag_color;
	out_color				= vec4(result, 1.f);
}