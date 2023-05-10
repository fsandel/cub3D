#include <cub3D.h>

char	*create_texture_name(const char *name, int num, char *tp)
{
	char	*temp;
	char	*temp2;
	char	*num_char;

	num_char = ft_itoa(num);
	temp = ft_strjoin("textures/enemy/", name);
	temp2 = ft_strjoin(temp, "/");
	free(temp);
	temp = ft_strjoin(temp2, tp);
	free(temp2);
	temp2 = ft_strjoin(temp, num_char);
	free(num_char);
	free(temp);
	temp = ft_strjoin(temp2, ".png");
	free(temp2);
	return (temp);
}

int	enemy_load_single_png(t_enemy *enemy, t_enemy_type type,
			const char *name)
{
	int		i;
	char	*att_char;
	char	*mov_char;
	int	error;

	error = 0;
	i = 0;
	while (i < 8)
	{
		mov_char = create_texture_name(name, i, "m");
		att_char = create_texture_name(name, i, "a");
		enemy->walking_tex[type][i] = mlx_load_png(mov_char);
		enemy->attacking_tex[type][i] = mlx_load_png(att_char);
		if (!(enemy->walking_tex[type][i] && enemy->attacking_tex[type][i]))
			error++;
		free(mov_char);
		free(att_char);
		i++;
	}
	return (error);
}

int	enemy_load_png(t_enemy *enemy)
{
	t_enemy_type	type;
	const char		*names[8] = {
		names[big_hans_blue] = "big_hans_blue",
		names[big_hans_red] = "big_hans_red",
		names[dog] = "dog",
		names[guard] = "guard",
		names[hans] = "hans",
		names[mutant] = "mutant",
		names[officer] = "officer",
		names[surgeon] = "surgeon"
	};
	int	error;

	error = 0;
	type = 0;
	while (type < 8)
	{
		error += enemy_load_single_png(enemy, type, names[type]);
		type++;
	}
	return (error);
}
