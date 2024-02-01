/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:40:06 by lilizarr          #+#    #+#             */
/*   Updated: 2024/02/01 16:29:26 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.c"


int	main(void)
{
	char	*line;
	int		fd1;
	char	*str;
	int		i;

	i = 1;
	str = "ABCDEFGHIJ\nKLMN\nOPQRS\nTUVWXYZ\t\n1234567890\n_123*---&";
	fd1 = open("file1", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	write(fd1, str, ft_strlen(str));
	close(fd1);
	str = NULL;
	sleep(1);
	fd1 = open("file1", O_RDONLY);;
	while (1)
	{
		line = get_next_line(fd1);
		printf("\n\nReturn: : \n");
		if (line)
		{
			check_after_string_data(line, ft_strlen(line), 1);
			printf("%s\t[%zu]\n", line, ft_strlen(line));
		}
		else
		{
			printf("%s\n\n", (void *)0);
			break ;
		}
		free(line);
	}
	if (close(fd1) == -1)
	{
		printf("| %s |", str);
		return (1);
	}
	return (0);
}
