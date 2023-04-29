#ifndef DESIGN_H
# define DESIGN_H

# define WIDTH 1000
# define HEIGHT 1000
# define HUD_SIZE 40
# define FOV 45

# define SPEED 0.05f
# define SPRINT_SPEED 0.08f
# define COLLISION 0.2f
# define TURN_SPEED 0.05f

# define MINIMAP_MAX_ZOOM 10
# define MINIMAP_MIN_ZOOM 3

//1 to dynamicly change speed based on fps
//0 to deactivate
# define DYNAMIC_SPEED 1
# define DYNAMIC_TURN_SPEED 1

//range in which the user can open doors
# define DOOR_TOUCH_RANGE 2

//range player can see
//0 to turn of fog
# define FOG 5

# define ENEMIE_HITPOINTS 3
# define ENEMY_RANGE 5
# define ENEMY_FRAME_COOLDOWN 8

#endif