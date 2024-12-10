/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabdel-f <rabdel-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:27:14 by rabdel-f          #+#    #+#             */
/*   Updated: 2024/09/10 16:05:51 by rabdel-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->writer);
	pthread_mutex_destroy(&data->is_eating);
	pthread_mutex_destroy(&data->death_checker);
}

void	free_data(t_data *data)
{
	if (data->forks != NULL)
		free(data->forks);
	if (data->philosophers != NULL)
		free(data->philosophers);
}

void	clear_data(t_data *data)
{
	destroy_mutexes(data);
	free_data(data);
}
