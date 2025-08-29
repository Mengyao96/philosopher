/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:55:46 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/29 12:54:40 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_mutexes(t_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (&(data->philos[i].lock))
			pthread_mutex_destroy(&(data->philos[i].lock));
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
	}
}

static void	stop_philos(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(philos[i].thread_id, NULL);
		i++;
	}
}

void	cleanup(t_data *data)
{
	if (data->philos)
		stop_philos(data->philos, data->num_philos);
	if (data->forks)
		free_mutexes(data, data->num_philos);
	pthread_mutex_destroy(&(data->print_lock));
	free(data->philos);
	free(data->forks);
}
