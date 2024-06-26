/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuznets <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:42:39 by dvoronin          #+#    #+#             */
/*   Updated: 2024/04/22 19:10:31 by skuznets         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *buf, char *str)
{
	int	r;

	r = 1;
	while (ft_strchr(str, '\n') == 0 && r != 0)
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r < 0)
		{
			free(buf);
			free(str);
			return (0);
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

char	*ft_remain(char	*str)
{
	char	*rem;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	i++;
	rem = ft_substr(str, i, ft_strlen(str));
	free(str);
	return (rem);
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

char	*get_next_line(int fd)
{
	char			*current_line;
	char			*buf;
	static char		*str;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (0);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	str = ft_read(fd, buf, str);
	if (!str || str[0] == '\0')
	{
		free(str);
		str = 0;
		return (NULL);
	}
	current_line = ft_line(str);
	str = ft_remain(str);
	return (current_line);
}

//int	main()
//{
//	int i;
//	int fd;
//
//	i = 0;
//	fd = open("test.txt", O_RDONLY);
//	while (i < 10)
//	{
//		printf("%s", get_next_line(fd));
//		i++;
//	}
//	close(fd);
//	return (0);
//}