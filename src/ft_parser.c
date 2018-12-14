/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylisyak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 18:10:55 by ylisyak           #+#    #+#             */
/*   Updated: 2018/12/11 01:13:16 by ylisyak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rtv.h"

void				ft_direction_catcher(t_win *window, int id, int nbr)
{
	static int		id_value = -2;
	static int  	counter;
	static int		color;

	(id_value == -2) ? id_value = -1 : 0;
	if (id != id_value)
	{
		color = 0;
		counter = 0;
	}
	(counter == 0) ? (window->objects[id].dir.x = nbr) : 0;
	(counter == 1) ? (window->objects[id].dir.y = nbr) : 0;
	(counter == 2) ? (window->objects[id].dir.z = nbr) : 0;
	(counter == 0) ? printf("X : %f\n", window->objects[id].dir.x) : 0;
	(counter == 1) ? printf("Y : %f\n", window->objects[id].dir.y) : 0;
	(counter == 2) ? printf("Z : %f\n", window->objects[id].dir.z) : 0;
	counter++;
	id_value = id;
}

void	ft_direction(t_win *window, char *line, int id)
{
	int				nbr;
	int				point;
	int				tmpwl;
	int				tmpdl;

	nbr = 0;
	point = 0;
	tmpwl = 0;
	tmpdl = 0;
	while (*line != '\0' && *line != '>')
	{
		while (*line == ' ')
			line++;
		if (ft_isdigit(*line))
		{
			tmpwl = (point == 2) ? ft_strlen_until(line, '>') :\
			ft_strlen_until(line, ',');
			nbr = ft_atoi_base(line, 10);
			tmpdl = ft_nbrlen(nbr);
			((nbr <= SCREEN_W && nbr >= 100) || (nbr >= 100 && nbr <= SCREEN_H)) ?\
			printf("Not valid RGB parameter in cell\n") : 0;
			(tmpwl == tmpdl) ? printf("yes") : printf("no");
			ft_direction_catcher(window, id, nbr);
		}
		line += tmpwl + 1;
		point++;
	}	   
}

void	ft_get_direction(t_win *window, char *line, int id)
{
	while (*line != '<' && *line != '\0')
		line++;
	line++;
	if (ft_isdigit(*line))
		ft_direction(window, line, id);	
}

void				ft_rgb_catcher(t_win *window, int id, int nbr)
{
	static int		id_value = -2;
	static int  	counter;
	static int		color;

	(id_value == -2) ? id_value = -1 : 0;
	if (id != id_value)
	{
		color = 0;
		counter = 0;
	}
	(counter == 0) ? color += ft_rgb(nbr, 0, 0) : 0;
	(counter == 1) ? color += ft_rgb(0, nbr, 0) : 0;
	(counter == 2) ? color += ft_rgb(0, 0, nbr) : 0;
	(counter == 2) ? window->objects[id].color = color : 0;
	(counter == 2) ? printf("Color in object : %d\n", window->objects[id].color):0;
	counter++;
	id_value = id;
}

int				ft_isalphahex(char c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 70) || (c >= 97 && c <= 102)) 
		return (1);
	return (0);
}

void				ft_hex_rgb(t_win *window, char *line, int id)
{
	int				nbr;
	int				point;
	int				tmpwl;
	int				wlmax;

	nbr = 0;
	point = 0;
	tmpwl = 0;
	wlmax = 6;
	while (*line != '\0' && *line != '>')
	{
		while (*line == ' ')
			line++;
		if (ft_isdigit(*line))
		{
			line += 2;
			tmpwl = ft_strlen_until(line, '>');
			(tmpwl > wlmax) ? printf("Max 6 simbols in hex") : 0; 
			nbr = ft_atoi_base(line, 16);
			window->objects[id].color = nbr;
		}
		line += tmpwl + 1;
		point++;
	}
}

void				ft_dec_rgb(t_win *window, char *line, int id)
{
	int				nbr;
	int				point;
	int				tmpwl;
	int				tmpdl;

	nbr = 0;
	point = 0;
	tmpwl = 0;
	tmpdl = 0;
	while (*line != '\0' && *line != '>')
	{
		while (*line == ' ')
			line++;
		if (ft_isdigit(*line))
		{
			tmpwl = (point == 2) ? ft_strlen_until(line, '>') :\
			ft_strlen_until(line, ',');
			nbr = ft_atoi_base(line, 10);
			tmpdl = ft_nbrlen(nbr);
			(nbr > 255 || nbr < 0) ? printf("Not valid RGB parameter in cell\n") : 0;
			(tmpwl == tmpdl) ? printf("yes") : printf("no");
			ft_rgb_catcher(window, id, nbr);
		}
		line += tmpwl + 1;
		point++;
	}	   
}

void	ft_default_color(t_win *window, char *line, int id)
{
	if (ft_strncmp(line, "white", ft_strlen_until(line, '>')) == 0)
		window->objects[id].color = 16777215;		
	else if (ft_strncmp(line, "black", ft_strlen_until(line, '>')) == 0)
		window->objects[id].color = 0;
	else if (ft_strncmp(line, "red", ft_strlen_until(line, '>')) == 0)
		window->objects[id].color = 16711680;
	else if (ft_strncmp(line, "green", ft_strlen_until(line, '>')) == 0)
		window->objects[id].color = 65280;
	else if (ft_strncmp(line, "blue", ft_strlen_until(line, '>')) == 0)
		window->objects[id].color = 255;
	else
	{
		printf("\33[0;31m");
		printf("Object name: %s\n", window->objects[id].name);
		printf("Not correct default color in object [id:%d]\n", id);
		printf("Color set as black as default.\n");
		window->objects[id].color = 0;
		printf("\33[0m");
	}
}

void	ft_get_color(t_win *window, char *line, int id)
{
	while (*line != '<' && *line != '\0')
		line++;
	line++;
	if (ft_isalpha(*line))
		ft_default_color(window, line, id);
	if (*line == '0' && (*(line + 1) == 'x' || *(line + 1) == 'X'))
		ft_hex_rgb(window, line, id);
	else if (ft_isdigit(*line) && (*(line + 1) != 'x' || *(line + 1) != 'X'))
		ft_dec_rgb(window, line, id);	
}

void				ft_location_catcher(t_win *window, int id, int nbr)
{
	static int		id_value = -2;
	static int  	counter;
	static int		color;

	(id_value == -2) ? id_value = -1 : 0;
	if (id != id_value)
	{
		color = 0;
		counter = 0;
	}
	(counter == 0) ? (window->objects[id].pos.x = nbr) : 0;
	(counter == 1) ? (window->objects[id].pos.y = nbr) : 0;
	(counter == 2) ? (window->objects[id].pos.z = nbr) : 0;
	(counter == 0) ? printf("X : %f\n", window->objects[id].pos.x):0;
	(counter == 1) ? printf("Y : %f\n", window->objects[id].pos.y):0;
	(counter == 2) ? printf("Z : %f\n", window->objects[id].pos.z):0;
	counter++;
	id_value = id;
}

void	ft_location(t_win *window, char *line, int id)
{
	int				nbr;
	int				point;
	int				tmpwl;
	int				tmpdl;

	nbr = 0;
	point = 0;
	tmpwl = 0;
	tmpdl = 0;
	while (*line != '\0' && *line != '>')
	{
		while (*line == ' ')
			line++;
		if (ft_isdigit(*line))
		{
			tmpwl = (point == 2) ? ft_strlen_until(line, '>') :\
			ft_strlen_until(line, ',');
			nbr = ft_atoi_base(line, 10);
			tmpdl = ft_nbrlen(nbr);
			((nbr <= SCREEN_W && nbr >= 100) || (nbr >= 100 && nbr <= SCREEN_H)) ?\
			printf("Not valid RGB parameter in cell\n") : 0;
			(tmpwl == tmpdl) ? printf("yes") : printf("no");
			ft_location_catcher(window, id, nbr);
		}
		line += tmpwl + 1;
		point++;
	}	   
}

void	ft_get_location(t_win *window, char *line, int id)
{
	while (*line != '<' && *line != '\0')
		line++;
	line++;
	if (ft_isdigit(*line))
		ft_location(window, line, id);	
}



void	ft_angle(t_win *window, char *line, int id)
{
	double			angle;

	while (*line != '\0' && *line != '\n' && *line != ' ')
	{	
		if (ft_isdigit(*line) || *line == '-')
		{
			window->objects[id].angle = ft_atoi(line);
			line += ft_nbrlen(ft_atoi(line)) - 1;	
		}
		line++;
	}
}

void	ft_get_angle(t_win *window, char *line, int id)
{
	while (*line != '-' && !ft_isdigit(*line) && *line != '\0')
		line++;
	while (*line == ' ')
		line++;
	if (ft_isdigit(*line) || *line == '-')
		ft_angle(window, line, id);
}

void	ft_radius(t_win *window, char *line, int id)
{
	while (*line != '\0' && *line != '\n' && *line != ' ')
	{
		if (ft_isdigit(*line))
		{
			window->objects[id].radius = ft_atoi(line);
			line += ft_strlen_until(line, ' ') - 1;
		}
		line++;
	}
}

void	ft_get_radius(t_win *window, char *line, int id)
{
	while (!ft_isdigit(*line) && *line != '\0')
		line++;
	while (*line == ' ')
		line++;
	if (ft_isdigit(*line))
		ft_radius(window, line, id);
}

void	ft_parameter(t_win *window, char *line, int *id)
{
	while (*line == 9)
		line++;
	if (ft_isalpha(*line))
	{
		if (ft_strncmp(line, "color", ft_strlen_until(line, ':')) == 0)
			ft_get_color(window, line, *id);	
		if (ft_strncmp(line, "location", ft_strlen_until(line, ':')) == 0)
			ft_get_location(window, line, *id);
		if (ft_strncmp(line, "direction", ft_strlen_until(line, ':')) == 0)
			ft_get_direction(window, line, *id);
		if (ft_strncmp(line, "angle", ft_strlen_until(line, ':')) == 0)
			ft_get_angle(window, line, *id);
		if (ft_strncmp(line, "radius", ft_strlen_until(line, ':')) == 0)
			ft_get_radius(window, line, *id);
	}	
}

void	ft_name(t_win *window, char *line, int id)
{
	int		i;

	i = 0;
	window->objects[id].name = (char*)malloc(sizeof(char) * ft_strlen_until(line, ' '));
	ft_bzero(window->objects[id].name, sizeof(ft_strlen_until(line, ' ')));
	ft_memcpy(window->objects[id].name, line, ft_strlen_until(line, ' '));

}

int		ft_parsing(t_win *window, char *input)
{
	int		fd;
	int		id;
	char	*line;

	fd = 0;
	id = -1;
	line = NULL;
	if ((fd = open(input, O_RDONLY)) == -1)
		return (0);
	while (get_next_line(fd, &line))
	{
		if (ft_isalpha(*line))
		{
			id++;
			ft_name(window, line, id);
		}
		if (*line == 9)
			ft_parameter(window, line, &id);
		
	}
	return (1);
}

int		ft_create_objects(t_win *window, int mount)
{
	//HERE NEED TO BE BZERED !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	window->objects = (t_objects *)malloc(sizeof(t_objects) * mount);
	if (window->objects != NULL)
		return (1);
	else
	{
		ft_putstr("Can't allocate memory");
		return (0);
	}
}

int			ft_count_objects(char *path)
{
	int		fd;
	int		objects;
	char	*line;

	fd = 0;
	line = NULL;
	objects = 0;
	if ((fd = open(path, O_RDONLY)) == -1)
		return (0);	
	while (get_next_line(fd, &line))
	{	
		if (ft_isalpha(*line))
		{	
			objects++;
		}
		if (*line == '/')				//skip comment
		{	
			free(line);
			line = NULL;
		}
	}
	close(fd);
	return (objects);
}
