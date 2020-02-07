# Laboratory 7
Lighting using the Gouraud model.

## Vertex Shader
According to the Gouraud model, the light attributes are calculated **per vertex**
and the values corresponding to each fragment are obtained via the default
interpolation performed by the GPU.

### Diffuse light
Represents the light that is unifromly reflected by the surface, thus the
amount that the observer perceives is unaltered by their angle relative to the
reflected ray.

### Specular light
Due to imperfections in each material, however, light also seems dimmer the
higher the angle between the line determined by the incidence point and the
observer's position and the reflected ray is. This reduction in intensity can
be approximated as ```cos(aforementioned_anlge)^n```, where ```n``` is the
shininess of the material.

## Fragment Shader
It only interpolates the colour obtained by the *Vertex Shader* in order to
obtain the colour of the fragment.