# Homework assignment 1: Flappy Bird
An OpenGL-powered version of the cancerous game.

The game uses 3 modules:
- **Bird** - creates and keeps the meshes that comprise the bird;
- **Obstacle** - contains the mesh for a single obstacle;
- **FlappyBird** - implements the entire game logic

## Bird
The bird is made up of 7 meshes:
- head (circle);
- body (ellipse);
- eye (circle);
- wing (triangle);
- beak (triangle);
- tail (triangle);
- (optional) hit box (ellipse)

The hit box is also given to the *FlappyBird* module so that it can check for
collisions.

## Obstacle
Contains a mesh representing a rectangle of lenght equal to the width of the
viewport in *FlappyBird* and some given `(R, G, B)`	 colour that fades into
white at the top of the obstacle.

## FlappyBird
Contains constants regarding speeds, angles, positions, accelerations, movement
in general. Also renders the meshes individually in order to create the scene.

### Init()
Assigns initial values to all movement and rotation parameters and creates
**20** obstacles with random colours, **5** out of which will be rendered at any
time. Moreover, about **1 in 5** obstacles will have variable scale (the
variation is sinusoidal).

### Update()
**Node:** the first frame has an immense `deltaTimeSeconds` which causes a huge
movement step. Thus, the first frame is not rendered.

As long as the bird is still alive, it still moves (duh...) and the score is
printed. However, whether a collision has occured or not, the visuals are stil
rendered in order for the player to fully grasp their mistake.

### Further notes:
Collisions are only checked between the bird and the obstacles directly above
and below it (if there are any).

The bird's movement follows the equation of motion, for better realism. The
flapping of the wing is treated as a scale transformation of the wing on the
*OY* axis.