/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:55:46 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/27 22:08:48 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_mutexes(pthread_mutex_t *mutexes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&mutexes[i]);
		i++;
	}
	free(mutexes);
}

void	stop_philos(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(&philos[i], NULL);
		i++;
	}
	free(philos);
}

void	cleanup(t_data *data)
{
	if (data->mutexes)
		free_mutexes(data->mutexes, data->num_philos);
	if (data->philos)
		stop_philos(data->philos, data->num_philos);
}
