/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 15:50:24 by aiblanco          #+#    #+#             */
/*   Updated: 2023/08/31 21:09:12 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*freeft(char *str)
{
	free(str);
	return (NULL);
}

char	*new_stc_str(int fd, char *stc_str)
{
	ssize_t	nr_bytes;
	char	*str;

	str = (char *)malloc(BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	nr_bytes = 1;
	while (nr_bytes > 0 && !ft_strchr(stc_str, '\n'))
	{
		nr_bytes = read(fd, str, BUFFER_SIZE);
		if (nr_bytes == -1)
		{
			free(stc_str);
			free(str);
			return (NULL);
		}
		str[nr_bytes] = '\0';
		stc_str = ft_strjoin_gnl(stc_str, str);
	}
	free(str);
	return (stc_str);
}

char	*get_line2(char *stc_str)
{
	char	*line;
	int		len;
	int		j;

	len = 0;
	j = 0;
	if (!stc_str)
		return (NULL);
	if (stc_str[0] == '\0')
		return (NULL);
	while (stc_str[len] != '\n' && stc_str[len] != '\0')
		len++;
	if (stc_str[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (freeft(stc_str));
	while (j < len)
	{
		line[j] = stc_str[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*clean_stc_str(char *stc_str)
{
	char	*str;
	ssize_t	i;
	ssize_t	j;

	i = 0;
	if (!stc_str)
		return (NULL);
	j = strleng_gnl(stc_str);
	while (stc_str[i] != '\0' && stc_str[i] != '\n')
		i++;
	if (stc_str[i] == '\0' || stc_str[0] == '\0')
		return (freeft(stc_str));
	str = malloc(j - i++);
	if (!str)
		return (freeft(stc_str));
	j = 0;
	while (stc_str[i] != '\0')
		str[j++] = stc_str[i++];
	str[j] = '\0';
	free(stc_str);
	if (str[0] == '\0')
		return (freeft(str));
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*stc_str[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stc_str[fd] = new_stc_str(fd, stc_str[fd]);
	if (!stc_str[fd])
		return (NULL);
	line = get_line2(stc_str[fd]);
	stc_str[fd] = clean_stc_str(stc_str[fd]);
	return (line);
}

/* void ft_leaks(void)
{
	system("leaks -q a.out");
}

 int	main(void)
{
	int		fd;
	char	*str;

	atexit(ft_leaks);
	fd = open("./archivo copy", O_RDONLY);
	str = NULL;
	if (fd == -1)
		printf("Error al abrir el archivo\n");
	else
	{
		str = get_next_line(fd);
		while (str != NULL)
		{
			printf("%s", str);
			free(str);
			str = get_next_line(fd);
		}
		printf("%s", str);
		close(fd);
	}
	return (0);
} */