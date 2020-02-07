# Laboratory 9
Texture creation and rendering using the *Vertex* and *Fragment* shaders.

## Creating a texure
The function ```CreateRandomTexture()``` creates a texture containing random
random texels using **mip-maps** and various parameters such as **min** and
**mag** filters and **wrapping mode**.

## Using a texture
The texture is specified as an uniform to the *Fragment Shader*. This texture
unit will apply the given texture to the current fragment according to its
texture coordinates.