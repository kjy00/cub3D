#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"

// #define MOVE_SPEED	0.07;
// #define TURN_SPEED	0.06;
typedef enum e_keycode {
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_R = 39,
	KEY_L = 37,
	KEY_ESC = 53,
}	t_keycode;

typedef enum e_x_event {
	ON_KEYDOWN = 2,
	ON_DESTROY = 17,
}	t_x_event;

typedef enum e_size {
	PIX = 16,
	WIN_X = 600,
	WIN_Y = 600
}	t_size;

typedef enum e_speed {
	MOVE_SPEED = 7,
	ROT_SPEED = 6
}	t_speed;
// 열거형은 정수만 사용 가능하기 때문에
// 8,9번째 줄처럼 #define 메크로로 사용할지
// 열거형으로 선언하여 (MOVE_SPEED / 100) 할지.. 고민
// 근데 메크로 사용해보니까 계산이 안돼서 열거형 사용중

typedef struct s_ray {
	double	cam_x;
	double	raydir_x;
	double	raydir_y;
	int			map_x;
	int			map_y;
	double	deltadist_x;
	double	deltadist_y;
	double	sidedist_x;
	double	sidedist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side; //NEWS ?
	double	wall_dist;
} t_ray;

typedef struct s_wall {
	int line_h;
	int	draw_start;
	int	draw_end;
	int	color; //red 잠시 추가
}	t_wall;

typedef struct s_mlx {
	void	*mlx_ptr;
	void	*mlx_win;
	int		**tmp;
	int		*texture;
}	t_mlx;

typedef struct s_cub {
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		fl;
	int		ce;
	char	**map;
	int		h;
	int		w;
}	t_cub;

typedef struct s_vec {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	pln_x;
	double	pln_y;
}	t_vec;

typedef struct s_game {
	struct s_cub	*cub;
	struct s_mlx	*mlx;
	struct s_vec	*vec;
}	t_game;

/**********
* main.c  *
**********/
void	err_exit(const char *str, t_game *game);
int		close_win(t_mlx *mlx);

/**********
* move.c  *
**********/
int		key_press(int keycode, t_game *g);

/**********
* draw.c  *
**********/
int		draw_game(t_game *g);

/**********
* parse.c  *
**********/
void	free_strs(char **strs);
int		is_empty_line(char *line);
void	parse(char *av, t_cub *c);
void	parse_cub(int fd, t_cub *c);
void	parse_map(int fd, t_cub *c);
int		set_color(int *content, char *value);
void	p_err_exit(const char *str, char **f_str);

/*************
* init_mlx.c *
**************/
void	init_mlx_strt(t_game *g);

/***************
* raycasting.c *
****************/
void	calc_ray(t_vec *v, t_ray *r, int x);
void	dda(t_ray* r, t_cub *cub);

#endif
