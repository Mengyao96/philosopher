/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:46:29 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/28 21:02:28 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	launch_forks(t_data *data)
{
	int	i;
	int	total;

	total = data->num_philos;
	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * total);
	if (!data->forks)
		return (printf("Failed to malloc forks.\n"), -1);
	while (i < total)
	{
		pthread_mutex_init(&(data->forks[i]), NULL);
		i++;
	}
	return (0);
}

int	launch_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (printf("Error: Failed to malloc philos.\n"), -1);
	while (i < data->num_philos)
	{
		ft_memset(&(data->philos[i]), 0, sizeof(t_philo));
		data->philos[i].id = i;
		data->philos[i].data = data;
		data->philos[i].l_fork = &(data->forks[i]);
		data->philos[i].r_fork = &(data->forks[(i + 1) % data->num_philos]);
		pthread_mutex_init(&(data->philos[i].lock), NULL);
		if (pthread_create(&data->philos[i].thread_id, NULL,
			philo_routine, &data->philos[i]) != 0)
			return (printf("Error: Failed to create philos[%d].\n", i), -1);
		i++;
	}
	return (0);

}

//pthread_create: 0 success, -1 error
