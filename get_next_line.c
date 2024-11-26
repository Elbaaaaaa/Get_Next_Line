/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebella <ebella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:21:27 by ebella            #+#    #+#             */
/*   Updated: 2024/11/26 18:14:21 by ebella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_cut(char *stach)
{
	int		i;
	char	*line;

	i = 0;
	while (stach[i] != '\n' && stach[i] != '\0')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (free(line), NULL);
	i = 0;
	while (stach[i] != '\n' && stach[i] != '\0')
	{
		line[i] = stach[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_fill(char *stach, int readed)
{
	int		i;
	char	*line;

	i = 0;
	while ((stach[i] != '\n' && stach[i] != '\0'))
		i++;
	if (stach[i] == '\n' || BUFFER_SIZE < readed)
	{
		line = ft_cut(stach);
		if (!line)
			return (NULL);
		return (line);
	}
	else
		return (NULL);
}

char	*ft_initstach(char *stach, int fd)
{
	char	*buffer;
	int		readed;

	if (!stach)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed <= 0)
			return (free(buffer), NULL);
		buffer[readed] = '\0';
		stach = ft_strjoin("", buffer);
		free(buffer);
	}
	return (stach);
}

char	*get_next_line(int fd)
{
	static char	*stach;
	char		*buffer;
	char		*line;
	int			readed;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!stach && !(stach = ft_initstach(stach, fd)))
		return (NULL);
	while (stach && !(line = ft_fill(stach, 0)))
	{
		if (!(buffer = malloc(BUFFER_SIZE + 1)))
			return (NULL);
		if ((readed = read(fd, buffer, BUFFER_SIZE)) <= 0)
			return (free(buffer), NULL);
		buffer[readed] = '\0';
		stach = ft_strjoin(stach, buffer);
		free(buffer);
	}
    if (line)
	{
		readed = 0;
		while(line[readed] != '\0')
			readed++;
		stach = ft_strjoin("", stach + readed + 1);
	}
	return (line);
}

#include <fcntl.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	int i = 0;
	char *line;
	if (ac == 2)
	{
		int fd = open("test.txt", O_RDONLY);
		while (i < atoi(av[1]))
		{
			line = get_next_line(fd);
			printf("%d: %s\n", i, line);
			free(line);
			i++;
		}
		while ((line = get_next_line(fd)) != NULL)
			free(line);
		close(fd);
	}
	return (0);
}