/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 12:43:19 by aromny-w          #+#    #+#             */
/*   Updated: 2020/08/19 12:43:20 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	draw_carriage(t_mlx *visu, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++j < 25)
	{
		while (++i < 20)
			mlx_pixel_put(visu->mlx_ptr, visu->win_ptr, x + i, y + j,
			LIGHT_GREY_COLOR);
		i = 0;
	}
}

static void	draw_carriages(t_game_params *params)
{
	t_car_list_elem	*carriage_ptr;
	int				x;
	int				y;

	carriage_ptr = params->carriages_list;
	while (carriage_ptr)
	{
		x = (carriage_ptr->content->cur_position % 64) * 25;
		y = (carriage_ptr->content->cur_position / 64) * 20;
		draw_carriage(params->visu, x, y);
		carriage_ptr = carriage_ptr->next;
	}
}

static void	set_byte(char *byte, unsigned char n)
{
	byte[1] = n % 16 + (n % 16 < 10 ? '0' : 'a' - 10);
	n /= 16;
	byte[0] = n % 16 + (n % 16 < 10 ? '0' : 'a' - 10);
}

static void	draw_bytecode(t_game_params *params)
{
	char	byte[3];
	int		x;
	int		y;
	int		i;

	x = 0;
	y = 0;
	i = 0;
	ft_bzero(byte, sizeof(byte));
	while (i < MEM_SIZE)
	{
		set_byte(byte, params->arena[i]);
		mlx_string_put(params->visu->mlx_ptr, params->visu->win_ptr, x, y,
		params->visu->color[i], byte);
		x += 25;
		if (!(++i % 64) || i == MEM_SIZE)
		{
			x = 0;
			y += 20;
		}
	}
}

void		draw_arena(t_game_params *params)
{
	mlx_clear_window(params->visu->mlx_ptr, params->visu->win_ptr);
	draw_carriages(params);
	draw_bytecode(params);
}
