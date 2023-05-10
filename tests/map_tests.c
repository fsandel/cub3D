#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/cub3D.h"
#include "../lib/libft/libft.h"

void	setup(void)
{
	cr_redirect_stderr();
}

TestSuite(parse_map, .init = setup);

Test(parse_map, invalid_area){
	int i;
	char	*map_name;
	char	*num_str;
	char	*temp;
	int		fd;
	t_map	*result;
	
	i = 0;
	while (i < 28)
	{
		if (i < 10)
		{
			num_str = ft_itoa(i);
			temp = ft_strjoin("invalid_maps/invalid_map_area_00", num_str);
			free(num_str);
			map_name = ft_strjoin(temp, ".cub");
			free(temp);
			fd = open(map_name, O_RDONLY);
			result = parse(fd);
			cr_expect(result == NULL, "failed on %s \n", map_name);
			free(map_name);
			close(fd);
		}
		else
		{
			num_str = ft_itoa(i);
			temp = ft_strjoin("invalid_maps/invalid_map_area_0", num_str);
			free(num_str);
			map_name = ft_strjoin(temp, ".cub");
			free(temp);
			fd = open(map_name, O_RDONLY);
			result = parse(fd);
			cr_expect(result == NULL, "failed on %s \n", map_name);
			free(map_name);
			close(fd);
		}
		i++;
	}
}

Test(parse_map, valid_area){
	int i;
	char	*map_name;
	char	*num_str;
	char	*temp;
	int		fd;
	t_map	*result;
	
	i = 0;
	while (i < 13)
	{
		if (i < 10)
		{
			num_str = ft_itoa(i);
			temp = ft_strjoin("valid_maps/valid_map_area_00", num_str);
			free(num_str);
			map_name = ft_strjoin(temp, ".cub");
			free(temp);
			fd = open(map_name, O_RDONLY);
			result = parse(fd);
			cr_expect(map_is_valid(result) == true, "failed on %s \n", map_name);
			free(map_name);
			close(fd);
		}
		else
		{
			num_str = ft_itoa(i);
			temp = ft_strjoin("valid_maps/valid_map_area_0", num_str);
			free(num_str);
			map_name = ft_strjoin(temp, ".cub");
			free(temp);
			fd = open(map_name, O_RDONLY);
			result = parse(fd);
			cr_expect(map_is_valid(result) == true, "failed on %s \n", map_name);
			cr_expect(result != NULL, "result is null on %s \n", map_name);
			free(map_name);
			close(fd);
		}
		i++;
	}
}

Test(parse_map, invalid_rgb){
	int i;
	char	*map_name;
	char	*num_str;
	char	*temp;
	int		fd;
	t_map	*result;
	
	i = 0;
	while (i < 43)
	{
		if (i < 10)
		{
			num_str = ft_itoa(i);
			temp = ft_strjoin("invalid_maps/invalid_RGB_00", num_str);
			free(num_str);
			map_name = ft_strjoin(temp, ".cub");
			free(temp);
			fd = open(map_name, O_RDONLY);
			result = parse(fd);
			cr_expect(result == NULL, "failed on %s \n", map_name);
			free(map_name);
			close(fd);
		}
		else
		{
			num_str = ft_itoa(i);
			temp = ft_strjoin("invalid_maps/invalid_RGB_0", num_str);
			free(num_str);
			map_name = ft_strjoin(temp, ".cub");
			free(temp);
			fd = open(map_name, O_RDONLY);
			result = parse(fd);
			cr_expect(result == NULL, "failed on %s \n", map_name);
			free(map_name);
			close(fd);
		}
		i++;
	}
}

Test(parse_map, valid_rgb){
	int i;
	char	*map_name;
	char	*num_str;
	char	*temp;
	int		fd;
	t_map	*result;
	
	i = 0;
	while (i < 23)
	{
		if (i < 10)
		{
			num_str = ft_itoa(i);
			temp = ft_strjoin("valid_maps/valid_RGB_00", num_str);
			free(num_str);
			map_name = ft_strjoin(temp, ".cub");
			free(temp);
			fd = open(map_name, O_RDONLY);
			result = parse(fd);
			cr_expect(result != NULL, "failed on %s \n", map_name);
			free(map_name);
			close(fd);
		}
		else
		{
			num_str = ft_itoa(i);
			temp = ft_strjoin("valid_maps/valid_RGB_0", num_str);
			free(num_str);
			map_name = ft_strjoin(temp, ".cub");
			free(temp);
			fd = open(map_name, O_RDONLY);
			result = parse(fd);
			cr_expect(result != NULL, "failed on %s \n", map_name);
			free(map_name);
			close(fd);
		}
		i++;
	}
}

Test(parse_map, invalid_tex_NO){
	int i;
	char	*map_name;
	char	*num_str;
	char	*temp;
	int		fd;
	t_map	*result;
	
	i = 0;
	while (i < 23)
	{
		if (i < 10)
		{
			num_str = ft_itoa(i);
			temp = ft_strjoin("invalid_maps/invalid_tex_NO_00", num_str);
			free(num_str);
			map_name = ft_strjoin(temp, ".cub");
			free(temp);
			fd = open(map_name, O_RDONLY);
			result = parse(fd);
			cr_expect(result == NULL, "failed on %s \n", map_name);
			free(map_name);
			close(fd);
		}
		else
		{
			num_str = ft_itoa(i);
			temp = ft_strjoin("invalid_maps/invalid_tex_NO_0", num_str);
			free(num_str);
			map_name = ft_strjoin(temp, ".cub");
			free(temp);
			fd = open(map_name, O_RDONLY);
			result = parse(fd);
			cr_expect(result == NULL, "failed on %s \n", map_name);
			free(map_name);
			close(fd);
		}
		i++;
	}
}

Test(parse_map, invalid_tex_EA){
	int i;
	char	*map_name;
	char	*num_str;
	char	*temp;
	int		fd;
	t_map	*result;
	
	i = 0;
	while (i < 23)
	{
		if (i < 10)
		{
			num_str = ft_itoa(i);
			temp = ft_strjoin("invalid_maps/invalid_tex_EA_00", num_str);
			free(num_str);
			map_name = ft_strjoin(temp, ".cub");
			free(temp);
			fd = open(map_name, O_RDONLY);
			result = parse(fd);
			cr_expect(result == NULL, "failed on %s \n", map_name);
			free(map_name);
			close(fd);
		}
		else
		{
			num_str = ft_itoa(i);
			temp = ft_strjoin("invalid_maps/invalid_tex_EA_0", num_str);
			free(num_str);
			map_name = ft_strjoin(temp, ".cub");
			free(temp);
			fd = open(map_name, O_RDONLY);
			result = parse(fd);
			cr_expect(result == NULL, "failed on %s \n", map_name);
			free(map_name);
			close(fd);
		}
		i++;
	}
}

Test(parse_map, invalid_tex_SO){
	int i;
	char	*map_name;
	char	*num_str;
	char	*temp;
	int		fd;
	t_map	*result;
	
	i = 0;
	while (i < 23)
	{
		if (i < 10)
		{
			num_str = ft_itoa(i);
			temp = ft_strjoin("invalid_maps/invalid_tex_SO_00", num_str);
			free(num_str);
			map_name = ft_strjoin(temp, ".cub");
			free(temp);
			fd = open(map_name, O_RDONLY);
			result = parse(fd);
			cr_expect(result == NULL, "failed on %s \n", map_name);
			free(map_name);
			close(fd);
		}
		else
		{
			num_str = ft_itoa(i);
			temp = ft_strjoin("invalid_maps/invalid_tex_SO_0", num_str);
			free(num_str);
			map_name = ft_strjoin(temp, ".cub");
			free(temp);
			fd = open(map_name, O_RDONLY);
			result = parse(fd);
			cr_expect(result == NULL, "failed on %s \n", map_name);
			free(map_name);
			close(fd);
		}
		i++;
	}
}

Test(parse_map, invalid_tex_WE){
	int i;
	char	*map_name;
	char	*num_str;
	char	*temp;
	int		fd;
	t_map	*result;
	
	i = 0;
	while (i < 23)
	{
		if (i < 10)
		{
			num_str = ft_itoa(i);
			temp = ft_strjoin("invalid_maps/invalid_tex_WE_00", num_str);
			free(num_str);
			map_name = ft_strjoin(temp, ".cub");
			free(temp);
			fd = open(map_name, O_RDONLY);
			result = parse(fd);
			cr_expect(result == NULL, "failed on %s \n", map_name);
			free(map_name);
			close(fd);
		}
		else
		{
			num_str = ft_itoa(i);
			temp = ft_strjoin("invalid_maps/invalid_tex_WE_0", num_str);
			free(num_str);
			map_name = ft_strjoin(temp, ".cub");
			free(temp);
			fd = open(map_name, O_RDONLY);
			result = parse(fd);
			cr_expect(result == NULL, "failed on %s \n", map_name);
			free(map_name);
			close(fd);
		}
		i++;
	}
}

Test(parse_map, invalid_tex_DO){
	int i;
	char	*map_name;
	char	*num_str;
	char	*temp;
	int		fd;
	t_map	*result;
	
	i = 0;
	while (i < 1)
	{
		num_str = ft_itoa(i);
		temp = ft_strjoin("invalid_maps/invalid_tex_DO_00", num_str);
		free(num_str);
		map_name = ft_strjoin(temp, ".cub");
		free(temp);
		fd = open(map_name, O_RDONLY);
		result = parse(fd);
		cr_expect(result == NULL, "failed on %s \n", map_name);
		free(map_name);
		close(fd);
		i++;
	}
}

Test(parse_map, valid_tex){
	int i;
	char	*map_name;
	char	*num_str;
	char	*temp;
	int		fd;
	t_map	*result;
	
	i = 0;
	while (i < 50)
	{
		if (i < 10)
		{
			num_str = ft_itoa(i);
			temp = ft_strjoin("valid_maps/valid_tex_00", num_str);
			free(num_str);
			map_name = ft_strjoin(temp, ".cub");
			free(temp);
			fd = open(map_name, O_RDONLY);
			result = parse(fd);
			cr_expect(result != NULL, "failed on %s \n", map_name);
			free(map_name);
			close(fd);
		}
		else
		{
			num_str = ft_itoa(i);
			temp = ft_strjoin("valid_maps/valid_tex_0", num_str);
			free(num_str);
			map_name = ft_strjoin(temp, ".cub");
			free(temp);
			fd = open(map_name, O_RDONLY);
			result = parse(fd);
			cr_expect(result != NULL, "failed on %s \n", map_name);
			free(map_name);
			close(fd);
		}
		i++;
	}
}
