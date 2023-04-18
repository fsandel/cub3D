#include <criterion/criterion.h>
#include "../include/cub3D.h"
#include "../lib/libft/libft.h"

TestSuite(syntax_check);

Test(syntax_check, invalid_char)
{
	cr_expect_eq(is_valid_map_str("abcde"), false);
}
