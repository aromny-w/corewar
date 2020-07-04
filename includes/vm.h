/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veronika <veronika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 23:55:40 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/04 16:36:12 by veronika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "op.h"
# include "libft.h"
# include <string.h>
# include <errno.h>
# include <stdint.h>

# define RESET_COLOR "\e[m"
# define RED "\033[4;31m"

typedef struct				s_player
{
	int						id;
	char					*name;
	char					*filename;
	char					*comment;
	int						code_size;
	char					*code;
	struct s_player			*next;
}							t_player;

typedef struct				s_carriage
{
	int						id;
	char					carry;
	int						code_op;
	size_t					last_live;
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
	size_t					cycles_since_last_check;
	char					*arena;
	size_t					dump_idx;
	int						players_num;
	t_player				**players;
}							t_game_params;

void						add_carriage_elem(t_car_list_elem **head,
								int car_position, int player_id, int id);
t_carriage					*create_carriage(int start_position, int player_id,
											int id);
void						move_carriage(t_carriage *carriage, int distance);
void						delete_carriage(t_carriage *carriage);
void						read_arena_to_carriage(t_carriage *carriage, t_game_params *arena);
void						delete_carriage_elem(t_car_list_elem **head, int id);
void						delete_carriage_list(t_car_list_elem *head);
int							arena_read(char *arena, int cur_position);

void						announce_players(t_player **players);
void						announce_winner(t_game_params *params);
void						dump_memory(char *arena);
void						announce_player_alive(t_player **players, int id);
void						print_memory_error();

void						delete_all_players(t_player **players);
void						dump_mem_and_exit(t_game_params *params,
									t_car_list_elem *carriages);
void						game_over(t_game_params *params, t_car_list_elem *carriages);
void						mem_error_exit();

t_game_params				*init_game_params(void);
t_player					*init_player(char *filename, int num);
void						get_args(int ac, char **av, t_game_params *params);
void						sort_players(t_game_params *prms, t_player **lst);
void						validate_players(char **av, t_game_params *prms);

void						print_usage(char *exec);
int32_t 					bin_to_num(uint8_t *val, size_t len);
void						free_params(t_game_params **params);
void						free_players(t_player ***player);
void						error(char *str);

#endif
