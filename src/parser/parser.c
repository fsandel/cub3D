#include "cub3D.h"

static t_list	*read_file(int fd);
static void		print_file(t_list *line_list);

int	parse(int fd)
{
	t_list	*line_list;

	line_list = read_file(fd);
	print_file(line_list);
	close(fd);
	return (EXIT_SUCCESS);
}

static void	print_file(t_list *line_list)
{
	t_list	*temp;

	temp = line_list;
	while (temp->next != NULL)
	{
		ft_printf("%s", temp->content);
		temp = temp->next;
	}
	ft_printf("%s\n", temp->content);
	ft_lstclear(&line_list, &free);
}

static t_list	*read_file(int fd)
{
	char	*str;
	int		line_count;
	t_list	*lines;

	line_count = 0;
	str = get_next_line(fd);
	lines = NULL;
	while (str != NULL)
	{
		if (str != NULL)
		{
			ft_lstadd_back(&lines, ft_lstnew(str));
			line_count++;
		}
		str = get_next_line(fd);
	}
	ft_printf("line count: %d\n", line_count);
	return (lines);
}
