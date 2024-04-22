/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:31:36 by skuznets          #+#    #+#             */
/*   Updated: 2024/04/22 17:01:16 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *buf, char *str)
{
	int	r;

	r = 1;
	while (!ft_strchr(str, '\n') && r != 0)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r < 0)
		{
			free(buf);
			free(str);
			return (NULL);
		}
		buf[r] = '\0';
		if (!str)
			str = ft_substr(buf, 0, r);
		else
			str = ft_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

char	*ft_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	i++;
	line = ft_substr(str, 0, i);
	return (line);
}

char	*ft_remain_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_substr(str, i+1, ft_strlen(str));
	free(str);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	str = ft_read(fd, buf, str);
	if (!str)
	{
		free(buf);
		str = NULL;
		return (NULL);
	}
	line = ft_line(str);
	str = ft_remain_line(str);
	return (line);
}

 int main()
 {
 	int i = 0;
 	int fd = open("test.txt", O_RDONLY);
 	while (i < 10)
 	{
 		printf("%s", get_next_line(fd));
 		i++;
 	}
 	close(fd);
 	return (0);
 }