#ifndef DESIGN_H
# define DESIGN_H

# define WIDTH 1500
# define HEIGHT 1250
# define HUD_SIZE 40
# define FOV 45

# define SPEED 0.05f
# define SPRINT_SPEED 0.08f
# define COLLISION 0.2f
# define TURN_SPEED 0.05f

# define MINIMAP_MAX_ZOOM 10
# define MINIMAP_MIN_ZOOM 3

# define STARTING_HP 100
# define STARTING_AMMO 32

//1 to dynamicly change speed based on fps
//0 to deactivate
# define DYNAMIC_SPEED 1
# define DYNAMIC_TURN_SPEED 1

//range in which the user can open doors
# define DOOR_TOUCH_RANGE 2

//range player can see
//0 to turn of fog
# define FOG 7

# define ENEMIE_HITPOINTS 10
# define ENEMY_RANGE 6
# define ENEMY_FRAME_COOLDOWN 8
# define ENEMY_Y_OFFSET 130

# define ENEMY_HEIGHT 350
# define ENEMY_WIDTH 200

# define START_SCREEN "textures/screen/screen_start0.png"
# define START_SCREEN1 "textures/screen/screen_start1.png"
# define DEFEAT_SCREEN "textures/screen/screen_death.png"
# define VICTORY_SCREEN "textures/screen/wolf_victory.png"

# define HP_PICKUP 50
# define AMMO_PICKUP 16

# define WEAPON_COOLDOWN 10

# define CROSSHAIR_COLOR 0xc3c3c3ff

#endif
