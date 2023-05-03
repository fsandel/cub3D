#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/cub3D.h"
#include "../lib/libft/libft.h"

void	setup(void)
{
	cr_redirect_stderr();
}

TestSuite(parse_map, .init = setup);

//Test(parse_map, valid_map){
//	int			fd;
//	t_map		*result;
//	t_cube_type	expected_arr[8][10] = {
//		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//		{1, 0, 0, 1, 1, 1, 1, 0, 0, 1},
//		{1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
//		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//		{1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
//		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//	};
//	fd = open("../maps/test.cub", O_RDONLY);
//	result = parse(fd);
//	cr_assert_eq(result->width, 10);
//	cr_assert_eq(result->height, 8);
//	cr_assert_eq(result->floor_color, -878249985);
//	cr_assert_eq(result->ceiling_color, 77981183);
//	cr_assert_arr_eq(result->cubes[0], expected_arr[0], 10);
//	cr_assert_arr_eq(result->cubes[1], expected_arr[1], 10);
//	cr_assert_arr_eq(result->cubes[2], expected_arr[2], 10);
//	cr_assert_arr_eq(result->cubes[3], expected_arr[3], 10);
//	cr_assert_arr_eq(result->cubes[4], expected_arr[4], 10);
//	cr_assert_arr_eq(result->cubes[5], expected_arr[5], 10);
//	cr_assert_arr_eq(result->cubes[6], expected_arr[6], 10);
//	cr_assert_arr_eq(result->cubes[7], expected_arr[7], 10);
//}

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
			//cr_stderr_match_str("Error\n");
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

//Test(parse_map, valid_area){
//	int i;
//	char	*map_name;
//	char	*num_str;
//	char	*temp;
//	int		fd;
//	t_map	*result;
//	
//	i = 0;
//	while (i < 13)
//	{
//		if (i < 10)
//		{
//			num_str = ft_itoa(i);
//			temp = ft_strjoin("valid_maps/valid_map_area_00", num_str);
//			free(num_str);
//			map_name = ft_strjoin(temp, ".cub");
//			free(temp);
//			fd = open(map_name, O_RDONLY);
//			result = parse(fd);
//			cr_expect(map_is_valid(result) == true, "failed on %s \n", map_name);
//			free(map_name);
//			close(fd);
//		}
//		else
//		{
//			num_str = ft_itoa(i);
//			temp = ft_strjoin("valid_maps/valid_map_area_0", num_str);
//			free(num_str);
//			map_name = ft_strjoin(temp, ".cub");
//			free(temp);
//			fd = open(map_name, O_RDONLY);
//			result = parse(fd);
//			cr_expect(map_is_valid(result) == true, "failed on %s \n", map_name);
//			free(map_name);
//			close(fd);
//		}
//		i++;
//	}
//}

//Test(parse_map, invalid_rgb){
//	int i;
//	char	*map_name;
//	char	*num_str;
//	char	*temp;
//	int		fd;
//	t_map	*result;
//	
//	i = 0;
//	while (i < 43)
//	{
//		if (i < 10)
//		{
//			num_str = ft_itoa(i);
//			temp = ft_strjoin("invalid_maps/invalid_RGB_00", num_str);
//			free(num_str);
//			map_name = ft_strjoin(temp, ".cub");
//			free(temp);
//			fd = open(map_name, O_RDONLY);
//			result = parse(fd);
//			cr_expect(result == NULL, "failed on %s \n", map_name);
//			free(map_name);
//			close(fd);
//		}
//		else
//		{
//			num_str = ft_itoa(i);
//			temp = ft_strjoin("invalid_maps/invalid_RGB_0", num_str);
//			free(num_str);
//			map_name = ft_strjoin(temp, ".cub");
//			free(temp);
//			fd = open(map_name, O_RDONLY);
//			result = parse(fd);
//			cr_expect(result == NULL, "failed on %s \n", map_name);
//			free(map_name);
//			close(fd);
//		}
//		i++;
//	}
//}

//Test(parse_map, valid_rgb){
//	int i;
//	char	*map_name;
//	char	*num_str;
//	char	*temp;
//	int		fd;
//	t_map	*result;
//	
//	i = 0;
//	while (i < 23)
//	{
//		if (i < 10)
//		{
//			num_str = ft_itoa(i);
//			temp = ft_strjoin("valid_maps/valid_RGB_00", num_str);
//			free(num_str);
//			map_name = ft_strjoin(temp, ".cub");
//			free(temp);
//			fd = open(map_name, O_RDONLY);
//			result = parse(fd);
//			cr_expect(options_are_valid(result) == true, "failed on %s \n", map_name);
//			free(map_name);
//			close(fd);
//		}
//		else
//		{
//			num_str = ft_itoa(i);
//			temp = ft_strjoin("valid_maps/valid_RGB_0", num_str);
//			free(num_str);
//			map_name = ft_strjoin(temp, ".cub");
//			free(temp);
//			fd = open(map_name, O_RDONLY);
//			result = parse(fd);
//			cr_expect(options_are_valid(result) == true, "failed on %s \n", map_name);
//			free(map_name);
//			close(fd);
//		}
//		i++;
//	}
//}
//
//Test(parse_map, invalid_tex_NO){
//	int i;
//	char	*map_name;
//	char	*num_str;
//	char	*temp;
//	int		fd;
//	t_map	*result;
//	
//	i = 0;
//	while (i < 23)
//	{
//		if (i < 10)
//		{
//			num_str = ft_itoa(i);
//			temp = ft_strjoin("invalid_maps/invalid_tex_NO_00", num_str);
//			free(num_str);
//			map_name = ft_strjoin(temp, ".cub");
//			free(temp);
//			fd = open(map_name, O_RDONLY);
//			result = parse(fd);
//			cr_expect(options_are_valid(result) == false, "failed on %s \n", map_name);
//			free(map_name);
//			close(fd);
//		}
//		else
//		{
//			num_str = ft_itoa(i);
//			temp = ft_strjoin("invalid_maps/invalid_tex_NO_0", num_str);
//			free(num_str);
//			map_name = ft_strjoin(temp, ".cub");
//			free(temp);
//			fd = open(map_name, O_RDONLY);
//			result = parse(fd);
//			cr_expect(options_are_valid(result) == false, "failed on %s \n", map_name);
//			free(map_name);
//			close(fd);
//		}
//		i++;
//	}
//}
