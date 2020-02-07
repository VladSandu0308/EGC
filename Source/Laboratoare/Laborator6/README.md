# Laboratory 6
Introduction to shaders

## Vertex Shader
Nothing special (*yet*). One of the cube meshes doesn't have colours assigned
to it so the normals are used as colours instead. For this reason, in order to
create some variation, the normals vary sinusoidally. Similarly, in order to
create smooth motion, the coordinates of the vertices are also altered
sinusoidally.

## Fragment shader
The parameters passed by the *Vertex Shader* are simply forwarded with no change,
except for the colour, for which the normal attribute is used instead.