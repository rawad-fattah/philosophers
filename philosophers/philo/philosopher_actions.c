/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdel-f <rabdel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:59:40 by rabdel-f          #+#    #+#             */
/*   Updated: 2024/09/10 16:07:13 by rabdel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philosopher_wait(t_data *data, time_t wait_time)
{
	time_t	limit;

	limit = get_time_milliseconds() + wait_time;
	while (get_time_milliseconds() < limit)
	{
		pthread_mutex_lock(&data->death_checker);
		if (data->died_any_philosopher == 1)
		{
			pthread_mutex_unlock(&data->death_checker);
			break ;
		}
		pthread_mutex_unlock(&data->death_checker);
	}
}

void	philosopher_writer(t_philosopher *philosopher, char *message)
{
	t_data	*data;

	data = philosopher->data;
	pthread_mutex_lock(&data->death_checker);
	if (data->died_any_philosopher == 0)
	{
		pthread_mutex_lock(&data->writer);
		printf("%ld %d %s\n", get_time_milliseconds() - data->start_time, \
		philosopher->id + 1, message);
		pthread_mutex_unlock(&data->writer);
	}
	pthread_mutex_unlock(&data->death_checker);
}

void	philosopher_eat(t_data *data, t_philosopher *philosopher)
{
	pthread_mutex_lock(&data->forks[philosopher->left_fork_id]);
	philosopher_writer(philosopher, "has taken a fork");
	pthread_mutex_lock(&data->forks[philosopher->right_fork_id]);
	philosopher_writer(philosopher, "has taken a fork");
	pthread_mutex_lock(&data->is_eating);
	philosopher_writer(philosopher, "is eating");
	philosopher->last_eating_time = get_time_milliseconds();
	pthread_mutex_unlock(&data->is_eating);
	philosopher_wait(data, data->time_to_eat);
	pthread_mutex_lock(&data->is_eating);
	philosopher->eating_count++;
	pthread_mutex_unlock(&data->is_eating);
	pthread_mutex_unlock(&data->forks[philosopher->left_fork_id]);
	pthread_mutex_unlock(&data->forks[philosopher->right_fork_id]);
}

void	philosopher_sleep(t_data *data, t_philosopher *philosopher)
{
	philosopher_writer(philosopher, "is sleeping");
	philosopher_wait(data, data->time_to_sleep);
}

void	philosopher_think(t_philosopher *philosopher)
{
	philosopher_writer(philosopher, "is thinking");
}
