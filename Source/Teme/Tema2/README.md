# Plane Runner
The game is (too) similar to the previous one: an endless runner where the
player avoids obstacles... but now in 3D. At the beginning of the game, the
player starts with 3 lives and full fuel. The fuel decays over time and can
be replenished by colliding with jerry cans. A life is lost upon a collision
with a rock.

Upon reaching 0 fuel or 0 lives, the player dies and the plane crashes.

## Controls
The plane follows the `mouse`: it moves up and down and rotates according to its
movement.

Press `P` to pause the game.

Press `F` to change the camera type. **Beware!** The first person camera is
considered a *hardcore* difficulty setting: the player only has one life and
doesn't see the fuel indicator.

## The plane
The plane is made of simple geometric shapes (parallelepiped) and has a
transparent cockpit.

## The sea
The sea is made up of 100 disks that in turn are made up of 100 points for
better *granulation* i.e. ability to deform. Actually,  there are 2 seas, one
moving twice as fast as the other to further create irregularity.

## The objects
All objects (clouds, fuel cans, lives or obstacles i.e. rocks) are `.obj` files
loaded into memory and with various textures applied to them. The objects rotate
around the sea.

Fuel cans and obstacles can also have varying scales. The amount of fuel
contained in a jerry can is proportional to its scale.