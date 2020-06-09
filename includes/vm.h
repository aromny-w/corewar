/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 23:55:40 by bgilwood          #+#    #+#             */
/*   Updated: 2020/06/09 22:57:50 by bgilwood         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "op.h"

typedef struct				s_player
{
	int						id;
	char					*name;
	char					*comment;
	int						code_size;
	char					*code;
}							t_player;

typedef struct				s_carriage
{
	int						id;
	char					carry;
	int						code_op;
	int						last_live;
	int						num_cycles_before_op;
	int						cur_position;
	int						bytes_next_op;
	int						registries[REG_NUMBER];
}							t_carriage;

typedef struct				s_car_list_elem
{
	t_carriage				*content;
	struct s_car_list_elem	*next;
}							t_car_list_elem;

typedef struct				s_game_params
{
	int						last_alive;
	size_t					cycles_since_start; // longer than int and unsigned?
	int						cycles_to_die;
	size_t					live_count_in_period;
	size_t					checks_count;
	char					*arena;
}							t_game_params;

void						add_carriage_elem(t_car_list_elem **head,
								int car_position, int player_id, int id);
t_carriage					*create_carriage(int start_position, int player_id,
											int id);

void						delete_carriage(t_carriage *carriage);

int							arena_read(char *arena, int cur_position);


#endif
