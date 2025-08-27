/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 20:46:29 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/27 22:09:40 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	launch_mutexes(t_data *data)
{
	int	i;
	int	total;

	total = data->num_philos;
	i = 0;
	data->mutexes = malloc(sizeof(pthread_mutex_t) * total);
	if (!data->mutexes)
		return (-1);
	while (i < total)
	{
		pthread_mutex_init(&data->mutexes[i], NULL);
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
		return (-1);
	// while (i < data->num_philos)
	// {
	// 	data->philos[i].id = i;
	// 	data->philos[i].num_eaten = 0;
	// 	data->philos[i].last_meal_time = 0;
	// 	data->philos[i].status = 0;
	// 	data->philos[i].data = data;
	// 	pthread_create(&data->philos[i].thread_id, NULL,
	// 		&routine, &data->philos[i]);
	// 	i++;
	// }
	return (0);

}
