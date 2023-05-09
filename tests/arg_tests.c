#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/cub3D.h"
#include "../lib/libft/libft.h"

void	setup(void)
{
	cr_redirect_stderr();
}

TestSuite(valid_args, .description = "Testing Args", .init = setup);

Test(valid_args, wrong_argc){
	char *test[3];
	test[0] = "cub3D";
	test[1] = "test";
	test[2] = "test";
	cr_expect_eq(args_valid(3, test), -1);
}

Test(valid_args, wrong_file_extension){
	char *test[2];
	test[0] = "cub3D";
	test[1] = "test";
	cr_expect_eq(args_valid(2, test), -1);
}

Test(valid_args, correct_args){
	char *test[2];
	test[0] = "cub3D";
	test[1] = "../maps/dungeon.cub";
	cr_expect_gt(args_valid(2, test), 2);
}

Test(valid_args, non_existing_file){
	char *test[2];
	test[0] = "cub3D";
	test[1] = "../maps/test123123123123.cub";
	cr_expect_eq(args_valid(2, test), -1);
}
