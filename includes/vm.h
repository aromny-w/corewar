/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgilwood <bgilwood@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 23:55:40 by bgilwood          #+#    #+#             */
/*   Updated: 2020/07/16 20:40:20 by bgilwood         ###   ########.fr       */
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
	size_t					cycles_to_die;
	size_t					live_count_in_period;
	size_t					checks_count;
	size_t					cycles_since_last_check;
	char					*arena;
	size_t					dump_idx;
	int						dump_flag_on;
	int						players_num;
	t_player				**players;
	int						carriages_num;
	t_car_list_elem			*carriages_list;
}							t_game_params;

extern void (*g_execs[])(t_carriage*, t_game_params*, int);

void						add_carriage_elem(t_car_list_elem **head,
								int car_position, int player_id, int id);
void						insert_existing_carriage(t_car_list_elem **head,
								t_carriage *elem);
t_carriage					*create_carriage(int start_position, int player_id,
								int id);
t_carriage					*duplicate_carriage(t_carriage *original,
								int new_id, int new_position);
void						move_carriage(t_carriage *carriage, int distance);
void						delete_carriage(t_carriage *carriage);
void						read_byte_to_carriage(t_carriage *carriage,
								t_game_params *arena);
int							read_number(char *arena, int position, int size_bytes);
void						write_number(char *arena, int position,
								int size_bytes, int number);
void						delete_carriage_elem(t_car_list_elem **head,
								int id);
void						delete_carriage_list(t_car_list_elem *head);
int							arena_read_byte(char *arena, int cur_position);
int							get_new_coord(int raw_coord);
int							get_registry(t_carriage *carriage,
								int registry_num);
void						save_registry(t_carriage *carriage,
								int registry_num, int value);
void						live_carriage(t_carriage *carriage, size_t cycle);

void						announce_player_alive(t_player **players, int id);
void						announce_players(t_player **players);
void						announce_winner(t_game_params *params);
void						dump_memory(char *arena);
void						announce_player_alive(t_player **players, int id);
void						print_memory_error();

void						*arena_init(void);
t_car_list_elem				*place_players(t_player **players, char *arena);
void						delete_all_players(t_player **players);
void						dump_mem_and_exit(t_game_params *params,
									t_car_list_elem *carriages);
void						game_over(t_game_params *params,
									t_car_list_elem *carriages);

t_game_params				*init_game_params(void);
t_player					*init_player(char *filename, int num);
void						init_ops(void);
void						get_args(int ac, char **av, t_game_params *params);
void						sort_players(t_game_params *prms, t_player **lst);
void						validate_players(char **av, t_game_params *prms);
void						play_game(t_car_list_elem **carriages,
										t_game_params *params);
void						exec_op(t_carriage *carriage, t_game_params *params);

int							get_argument(char *arena, t_carriage *carriage,
										int arg_type, int l_op);
int							get_address_argument(char *arena,
								t_carriage *carriage, int arg_type, int l_op);
void						print_usage(char *exec);
int32_t						bin_to_num(uint8_t *val, size_t len);
void						free_params(t_game_params **params);
void						free_players(t_player ***player);
void						error(char *str);

/*
** Operations
*/
void				op_live(t_carriage *carriage, t_game_params *params,
						int arg_code);
void				op_ld(t_carriage *carriage, t_game_params *params,
						int arg_code);
void				op_st(t_carriage *carriage, t_game_params *params,
						int arg_code);
void				op_add(t_carriage *carriage, t_game_params *params,
						int arg_code);
void				op_sub(t_carriage *carriage, t_game_params *params,
						int arg_code);
void				op_and(t_carriage *carriage, t_game_params *params,
						int arg_code);
void				op_or(t_carriage *carriage, t_game_params *params,
						int arg_code);
void				op_xor(t_carriage *carriage, t_game_params *params,
						int arg_code);
void				op_zjmp(t_carriage *carriage, t_game_params *params,
						int arg_code);
void				op_ldi(t_carriage *carriage, t_game_params *params,
						int arg_code);
void				op_sti(t_carriage *carriage, t_game_params *params,
						int arg_code);
void				op_fork(t_carriage *carriage, t_game_params *params,
						int arg_code);
void				op_lld(t_carriage *carriage, t_game_params *params,
						int arg_code);
void				op_lldi(t_carriage *carriage, t_game_params *params,
						int arg_code);
void				op_lfork(t_carriage *carriage, t_game_params *params,
						int arg_code);
void				op_aff(t_carriage *carriage, t_game_params *params,
						int arg_code);

#endif
