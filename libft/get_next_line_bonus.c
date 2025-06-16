/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmunoz-c <rmunoz-c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:52:56 by rmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/29 17:16:01 by rmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join_stash(char *stash, char *buffer)
{
	char	*temp;

	if (!stash)
		return (ft_strdup(buffer));
	temp = ft_strjoin(stash, buffer);
	if (!temp)
	{
		free (stash);
		return (NULL);
	}
	free (stash);
	return (temp);
}

static char	*read_n_store(int fd, char *stash, ssize_t *nbytes)
{
	char	*buffer;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	*nbytes = read(fd, buffer, BUFFER_SIZE);
	while (*nbytes > 0)
	{
		buffer[*nbytes] = '\0';
		stash = join_stash(stash, buffer);
		if (!stash || ft_strchr(stash, '\n'))
			break ;
		*nbytes = read(fd, buffer, BUFFER_SIZE);
	}
	free (buffer);
	if (*nbytes < 0)
	{
		free (stash);
		return (NULL);
	}
	return (stash);
}

static char	*get_line(char *stash)
{
	char	*ptr;
	char	*substr;
	size_t	len;

	if (!stash || !*stash)
		return (NULL);
	ptr = ft_strchr(stash, '\n');
	if (ptr)
	{
		len = (ptr + 1) - stash;
		substr = ft_substr(stash, 0, len);
	}
	else
	{
		len = ft_strlen(stash) + 1;
		substr = ft_substr(stash, 0, len);
	}
	if (!substr)
		return (NULL);
	return (substr);
}

static char	*update_stash(char *stash)
{
	char	*ptr;
	char	*new_stash;
	size_t	len;

	if (!stash)
		return (NULL);
	ptr = ft_strchr(stash, '\n');
	if (ptr)
	{
		len = ft_strlen(ptr + 1);
		new_stash = ft_substr(ptr + 1, 0, len);
	}
	else
		new_stash = NULL;
	free(stash);
	return (new_stash);
}

char	*get_next_line_bonus(int fd)
{
	static char	*stash[MAX_FD];
	char		*line;
	ssize_t		nbytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_n_store(fd, stash[fd], &nbytes);
	if (nbytes < 0 || !stash[fd])
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	line = get_line(stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = update_stash(stash[fd]);
	return (line);
}

/*int main() {
    int fd1 = open("hola.txt", O_RDONLY);
    int fd2 = open("otro.txt", O_RDONLY); 
    
    if (fd1 < 0 || fd2 < 0) {
        perror("Error opening files");
        return 1;
    }
    char *line1 = get_next_line(fd1);
    char *line2 = get_next_line(fd2);
    while ((line1) != NULL || (line2) != NULL) 
	{
        if (line1) {
            printf("FD1: %s", line1);
            free(line1);
        }
        if (line2) {
            printf("FD2: %s", line2);
            free(line2);
        }
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
    }

    close(fd1);
    close(fd2);
    return 0;
}*/