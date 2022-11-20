#include "../gnl/get_next_line.h" 
#include "cub3d.h"

static int set_cub_content(char *key, char *value, unsigned int len, t_cub *c)
{
	 // ft_strdup에 실패할 경우도 생각해봐야할 것 같아요 😭
	if (ft_strncmp(key, "NO", len) == 0 && c->no == NULL)
		c->no = ft_strdup(value);
	else if (ft_strncmp(key, "SO", len) == 0 && c->so == NULL)
		c->so = ft_strdup(value);
	else if (ft_strncmp(key, "WE", len) == 0 && c->we == NULL)
		c->we = ft_strdup(value);
	else if (ft_strncmp(key, "EA", len) == 0 && c->ea == NULL)
		c->ea = ft_strdup(value);
	else if (ft_strncmp(key, "F", len) == 0 && c->fl == -1)
		c->fl = 1; // 임시
	else if (ft_strncmp(key, "C", len) == 0 && c->ce == -1)
		c->ce = 1; // 임시
	else
		return (0);
	return (1);
}

static void	set_cub(char ***split, char **line, t_cub *c)
{
	if (!set_cub_content((*split)[0], (*split)[1], ft_strlen((*split)[0]), c))
	{
		free(*line);
		free_strs(*split);
		err_exit("Malloc failed.", NULL);
	}
	else
	{
		free(*line);
		free_strs(*split);
	}
}

static void	check_cub(int fd, t_cub *c)
{
	char	*line;
	char	**split;	

	line = get_next_line(fd);
	if (!line)
		err_exit("Not enough file contents.", NULL);
	if (is_empty_line(line))
	{
		free(line);
		return ;
	}
	split = ft_split(line, ' ');
	if (!split)
	{
		free(line);
		err_exit("Malloc failed.", NULL);
	}
	set_cub(&split, &line, c);
}

void	parse_cub(int fd, t_cub *c)
{
	do {
		check_cub(fd, c);
	} while (c->no == NULL || c->so == NULL || c->we == NULL\
			|| c->ea == NULL || c->fl == -1 || c->ce == -1);
}
