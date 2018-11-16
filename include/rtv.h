/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 15:02:11 by ylisyak           #+#    #+#             */
/*   Updated: 2018/11/16 02:27:43 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef 	RTV_H
#	define	RTV_H
#	include <libft.h>
#	include	<stdio.h>
#	include "SDL.h"
#	include "SDL_image.h"
#	include "SDL_timer.h"
#	include "SDL_ttf.h"
#	include "SDL_mixer.h"

#define	SCREEN_W 1200
#define	SCREEN_H 1200

typedef struct
{
	float			x;
	float			y;
	float			z;
}					vector;

typedef struct		s_object
{
	char			*name;
	vector			pos;  //for all objects (where they located?)
	vector			dir; //for camera and plane
	double			radius;
	int				reflaction;
	int				angle; // in degree
	unsigned int	color;
}					t_objects;

typedef struct		s_win
{
	SDL_Window		*window;
	SDL_Surface		*main_surface;
	t_objects		*objects;
}					t_win;

int				ft_parsing(t_win *window, char *input);
int				ft_count_objects(char *input);
int				ft_create_objects(t_win *window, int mount);
void			ft_core(t_win *window);

//SDL initialize connection with CPU and allocate window
//initialize main_surface 
int					ft_init_sdl(t_win *window);
//SDL fill pixels of surface;
void				ft_draw_bpx(int x, int y, size_t color, SDL_Surface *img);
#endif
