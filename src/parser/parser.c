#include "cub3D.h"

int	parse(int fd)
{
	char	*str;
	t_list	*lines;
	t_list	*head;

	str = get_next_line(fd);
	lines = NULL;
	while (str != NULL)
	{
		if (str != NULL)
			ft_lstadd_back(&lines, ft_lstnew(str));
		str = get_next_line(fd);
	}
	head = lines;
	while (lines->next != NULL)
	{
		ft_printf("%s", lines->content);
		lines = lines->next;
	}
	ft_printf("%s\n", lines->content);
	ft_lstclear(&head, &free);
	close(fd);
	return (EXIT_SUCCESS);
}
