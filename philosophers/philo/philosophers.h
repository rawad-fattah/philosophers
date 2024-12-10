/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdel-f <rabdel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:02:46 by rabdel-f          #+#    #+#             */
/*   Updated: 2024/09/10 17:34:42 by rabdel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	pthread_t		thread_id;
	int				id;
	int				left_fork_id;
	int				right_fork_id;
	int				eating_count;
	time_t			last_eating_time;
	struct s_data	*data;
}					t_philosopher;

typedef struct s_data
{
	int				number_of_philosophers;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				philosopher_must_eat;
	time_t			start_time;
	int				died_any_philosopher;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writer;
	pthread_mutex_t	is_eating;
	pthread_mutex_t	death_checker;
	t_philosopher	*philosophers;
}					t_data;

int		ft_atoi(char *str);
int		print_error(char *message);
time_t	get_time_milliseconds(void);
int		init_data(t_data *data, char **argv);
void	clear_data(t_data *data);
void	philosopher_wait(t_data *data, time_t wait_time);
void	philosopher_writer(t_philosopher *philosopher, char *message);
void	philosopher_eat(t_data *data, t_philosopher *philosopher);
void	philosopher_sleep(t_data *data, t_philosopher *philosopher);
void	philosopher_think(t_philosopher *philosopher);
void	philosopher_one(t_data *data);
void	philosopher_many(t_data *data);
void	init_philosophers(t_data *data);
int		init_mutexes(t_data *data);
int		check_args(char **argv);
void	*philosopher_one_func(void *void_philosopher);
void	*philosopher_many_func(void *void_philosopher);
void	catch_death_or_eat(t_data *data);
int		all_ate(t_data *data);
void	destroy_mutexes(t_data *data);
void	free_data(t_data *data);
void	join_and_clear(t_data *data);

#endif