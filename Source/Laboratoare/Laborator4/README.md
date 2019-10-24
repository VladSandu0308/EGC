# Laboratory 4
3D transformations:
- scale
- translate
- rotate (around each axis of an object)

## Bonuses

### Bonus 1
Make a cube jump sinusoidally and rotate around its centre while doing so by
pressing the arrow keys.

### Bonus 2
A cube allways follows the second cube that's rendered and on pressing **0** or
**9**, the former rotates around the latter.

### Bonus 3
Make a cube jump in one direction. While jumping, the cube also has to turn
*180 degrees*.

The cube rotates around the middle of the line between the start and the end
of the jump. When the cube is at the end position, the start and end positions
shift by a set `JUMP_DISTANCE` in order for the cube jump again.