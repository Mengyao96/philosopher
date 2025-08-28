/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tracy <tracy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:18:32 by tracy             #+#    #+#             */
/*   Updated: 2025/08/28 19:04:49 by tracy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_dead(t_philo *philo)
{
	long long	since_last_meal;

	since_last_meal = get_current_time_in_ms() - philo->last_meal_time;
	if (since_last_meal >= philo->data->time_to_die)
	{
		safe_print(&philo->data->philos, "died");
		return (1);
	}
	return (0);
}


void monitoring(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (is_philo_dead(&data->philos[i]))
			{
				data->is_end = 1;
				return ;
			}
			if (data->philos[i].num_eaten >= data->num_must_eat)
				data->all_ate += 1;
			i++;
		}
		if (data->all_ate == data->num_philos)
		{
			data->is_end = 1;
			return ;
		}
		usleep(1000); //sleep 1ms to reduce CPU usage
	}
}
