/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebella <ebella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:21:27 by ebella            #+#    #+#             */
/*   Updated: 2024/11/28 19:05:33 by ebella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_cut(char *stach)
{
    int i = 0;
    while (stach[i] && stach[i] != '\n')
        i++;
    
    char *line = malloc(i + 2); // +1 pour '\0'
    if (!line)
        return (NULL);
    
    i = 0;
    while (stach[i] && stach[i] != '\n')
    {
        line[i] = stach[i];
        i++;
    }
    line[i + 1] = '\0';
    return (line);
}

char	*ft_fill(char *stach, int readed)
{
	int		i;
	char	*line;

	i = 0;
	while ((stach[i] != '\n' && stach[i] != '\0'))
		i++;
	if (stach[i] == '\n' || readed < BUFFER_SIZE)
	{
		line = ft_cut(stach);
		if (!line)
			return (free(line), NULL);
		line[i] = '\n';
		return (line);
	}
	else
		return (NULL);
}

char	*ft_initstach(char *stach, int fd)
{
	char	*buffer;
	int		readed;

	if (fd < 0	|| BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(buffer), NULL);
	readed = read(fd, buffer, BUFFER_SIZE);
	if (readed <= 0)
		return (free(buffer), NULL);
	if (!stach)
	{
		stach = ft_strjoin("", buffer);
		if (!stach)
			return (free(stach), NULL);
	}
	else
	{
		stach = ft_strjoin(stach, buffer);
		if (!stach)
			return (free(stach), NULL);
	}
	free(buffer);
	return (stach);
}


char	*read_buffer(char *stach, int fd, int *readed)
{
	char	*buffer;
	char *temp;
	
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(buffer), NULL);
	*readed = read(fd, buffer, BUFFER_SIZE);
	if (readed <= 0)
		return (free(buffer), NULL);
    buffer[*readed] = '\0';
   	temp = stach;
    stach = ft_strjoin(stach, buffer);
    free(temp);
    free(buffer);
    return (stach);
}

char	*get_next_line(int fd)
{
	static char	*stach;
	char		*line;
	int readed;

	readed = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	stach = ft_initstach(stach, fd);
	if (!stach)
		return (free(stach), NULL);
	while (stach)
	{
		stach = read_buffer(stach, fd, &readed);
		if (!stach)
			return (NULL);
		line = ft_fill(stach, readed);
		if (line)
		{
			stach = ft_strchr(stach, '\n');
			if (stach)
				stach++;
			return (line);
		}
	}
	return (NULL);
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
			printf("%d: %s", i, line);
			free(line);
			i++;
		}
		while ((line = get_next_line(fd)) != NULL)
			free(line);
		close(fd);
	}
	return (0);
}