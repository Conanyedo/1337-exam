/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 22:34:12 by ybouddou          #+#    #+#             */
/*   Updated: 2020/12/03 17:33:30 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

size_t  ft_strlen(const char *s)
{
	int     i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char    *ft_strdup(const char *s1)
{
	unsigned int    i;
	unsigned int    j;
	char            *copy;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	if (!(copy = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (j < i)
	{
		copy[j] = s1[j];
		j++;
	}
	copy[j] = '\0';
	return (copy);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
	int     i;
	int     j;
	char    *join;
	int     len1;
	int     len2;

	if (s1 && s2)
	{
		i = 0;
		j = 0;
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		if (!(join = (char *)malloc((len1 + len2 + 1) * sizeof(char))))
			return (NULL);
		while (s1[i])
			join[j++] = s1[i++];
		i = 0;
		while (s2[i])
			join[j++] = s2[i++];
		join[j] = '\0';
		return (join);
	}
	return (NULL);
}

char    *ft_strchr(const char *s, int c)
{
	int     i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (0);
}

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int    i;
	unsigned int    j;
	char            *sub;

	if (!s)
		return (NULL);
	if (!*s || start > ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	j = 0;
	if (!(sub = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (s[i])
	{
		if (i == start)
		{
			while (s[i] && j < len)
				sub[j++] = s[i++];
			sub[j] = '\0';
			return (sub);
		}
		i++;
	}
	return (NULL);
}

int				get_next_line(char	**line)
{
	char		*buffer;
	static char	*str;
	char		*tmp;
	int			r;
	int			len;

	len = 0;
	buffer = NULL;
	if (line == NULL || (!(buffer = (char *)malloc(sizeof(char) * (1 + 1)))))
		return (-1);
	if (!str)
		str = ft_strdup("");
	while (!ft_strchr(str, '\n') && (r = read(0, buffer, 1)) > 0)
	{
		buffer[r] = '\0';
		tmp = ft_strjoin(str, buffer);
		free(str);
		str = tmp;
	}
	free(buffer);
	if (r < 0)
		return (-1);
	if (!*str && !r)
	{
		*line = ft_strdup("");
		free(str);
		str = NULL;
		return (0);
	}
	while (str[len] != '\n' && str[len] != '\0')
		len++;
	if (str[len] == '\n')
	{
		*line = ft_substr(str, 0, len);
		tmp = ft_strdup(str + len + 1);
		free(str);
		str = tmp;
	}
	else
	{
		*line = ft_strdup(str);
		free(str);
		str = NULL;
		return (0);
	}
	return (1);
}

int		main(int ac, char **av)
{
	char	*line;
	int		fd = open(av[1], O_RDONLY);
	int		r = 1;

	while (r == 1)
	{
		r = get_next_line(&line);
		printf("r : %d | line : %s\n", r, line);
		free(line);
	}
}
