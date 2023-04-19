#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/cub3D.h"
#include "../lib/libft/libft.h"

void	setup(void)
{
	cr_redirect_stderr();
}

TestSuite(parse_map, .init = setup);

Test(parse_map, valid_map){
int			fd;
t_map		*result;
t_cube_type	expected_arr[8][10] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 1, 0, 1, 0, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};
fd = open("../maps/test.cub", O_RDONLY);
result = parse(fd);
cr_assert_eq(result->width, 10);
cr_assert_eq(result->height, 8);
cr_assert_eq(result->floor_color, -878249985);
cr_assert_eq(result->ceiling_color, 77981183);
cr_assert_arr_eq(result->cubes[0], expected_arr[0], 10);
cr_assert_arr_eq(result->cubes[1], expected_arr[1], 10);
cr_assert_arr_eq(result->cubes[2], expected_arr[2], 10);
cr_assert_arr_eq(result->cubes[3], expected_arr[3], 10);
cr_assert_arr_eq(result->cubes[4], expected_arr[4], 10);
cr_assert_arr_eq(result->cubes[5], expected_arr[5], 10);
cr_assert_arr_eq(result->cubes[6], expected_arr[6], 10);
cr_assert_arr_eq(result->cubes[7], expected_arr[7], 10);
}
