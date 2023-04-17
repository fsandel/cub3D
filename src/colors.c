#include <cub3D.h>

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_red(int rgba)
{
	return ((rgba >> 24) & 0xFF);
}

int	get_green(int rgba)
{
	return ((rgba >> 16) & 0xFF);
}

int	get_blue(int rgba)
{
	return ((rgba >> 8) & 0xFF);
}

int	get_alpha(int rgba)
{
	return (rgba & 0xFF);
}
