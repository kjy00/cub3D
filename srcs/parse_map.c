#include "../gnl/get_next_line.h" 
#include "cub3d.h"

static int	check_element(char *line, int *flag, t_game *g)
{
	int	w;

	w = -1;
	while(line[++w])
	{
		if (!(*flag) && gnl_strchr("NSEW", line[w]))
		{
			init_vec(g->vec, line[w], w, g->cub->h);
			(*flag) = 1;
			line[w] = '0';
			continue ;
		}
		if (!gnl_strchr("10 \n", line[w]))
			return (FAIL);
	}
	if (w > g->cub->w)
		g->cub->w = w;
	return (SUCCESS);
}

static int	check_map_closed(int y, char **map, t_cub *c)
{
	int	x;

	x = -1;
	while (++x < c->w)
	{
		if (map[y][x] == '0' && (
			y == 0 || y == c->h - 1 || x == 0 || x == c->w - 1\
			|| map[y - 1][x] == ' ' || map[y + 1][x] == ' '\
			|| map[y][x - 1] == ' ' || map[y][x + 1] == ' '))
			return (FAIL);
	}
	return (SUCCESS);
}

static int	make_map_rectangle(char **line, int width)
{
	int		size;
	char	*fill;
	
	size = width - (int)ft_strlen(*line) - 1;
	if (size > 0)
	{
		fill = ft_calloc(sizeof(char), size + 1);
		if (!fill)
			return (FAIL);
		ft_memset(fill, ' ', size);
		*line = ft_strjoin(*line, fill);
		free(fill);
		if (!*line)
			return (FAIL);
	}
	return (SUCCESS);
}

static int	set_map(char *full_line, t_cub *c)
{
	int		y;
	int		err;
	char	**map;

	y = -1;
	err = SUCCESS;
	map = ft_split(full_line, '\n');
	if (!map)
	{
		free(full_line);
		return (FAIL);
	}
	while (++y < c->h && !err)
		err = make_map_rectangle(&map[y], c->w);
	y = -1;
	while (++y < c->h && !err)
		err = check_map_closed(y, map, c);
	if (!err)
		c->map = map;
	else
		free_double_char(map);
	return (err);
}

static int	skip_empty_line(int fd, char **line)
{
	*line = get_next_line(fd);
	if (!(*line))
		return (FAIL);
	while ((*line) && is_empty_line(*line))
	{
		free(*line);
		*line = get_next_line(fd);
	}
	return (SUCCESS);
}

static int	check_line(char **full_line, char *line, int *p, t_game *g)
{
	int	err;
	
	err = SUCCESS;
	if (is_empty_line(line) || check_element(line, p, g))
		err = FAIL;
	if (!err)
		*full_line = gnl_strjoin(*full_line, line);
	if (!(*full_line))
		err = FAIL;
	free(line);
	return(err);
}

int	parse_map(int fd, t_game *g)
{
	int		is_p;
	char	*line;
	char	*full_line;

	is_p = 0;
	full_line = NULL;
	if (skip_empty_line(fd, &line))
		return (FAIL);
	while (line)
	{
		if (check_line(&full_line, line, &is_p, g))
			return (FAIL);
		g->cub->h++;
		line = get_next_line(fd);
	}
	if (!is_p)
	{
		free(full_line);
		return (FAIL);
	}
	if (set_map(full_line, g->cub))
		return (FAIL);
	return (SUCCESS);
}