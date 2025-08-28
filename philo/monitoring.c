/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:18:32 by tracy             #+#    #+#             */
/*   Updated: 2025/08/28 20:47:56 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_dead(t_philo *philo)
{
	long long	since_last_meal;

	since_last_meal = current_time_in_ms() - philo->last_meal_time;
	if (since_last_meal >= philo->data->time_to_die)
	{
		printf("%lld %d died.\n", current_time_ms(), philo->id);
		philo->data->is_end = 1;
		return (1);
	}
	return (0);
}


void monitoring(t_data *data)
{
	int	i;
	int all_ate;

	while (1)
	{
		i = 0;
		all_ate = 0;
		while (i < data->num_philos) //need protection
		{
			pthread_mutex_lock(&(data->philos[i].lock));
			if (is_philo_dead(&data->philos[i]))
			{
				return (pthread_mutex_unlock(&(data->philos[i].lock)));
			}
			if (data->philos[i].num_eaten >= data->num_must_eat)
				all_ate += 1;
			pthread_mutex_unlock(&(data->philos[i].lock));
			i++;
		}
		if (all_ate == data->num_philos)
		{
			return (data->is_end = 1);
		}
		usleep(1000); //sleep 1ms to reduce CPU usage
	}
}
