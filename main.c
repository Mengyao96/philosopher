/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tracy <tracy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:41:46 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/28 17:20:06 by tracy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_all(t_data *data, char **av, int ac)
{
	ft_memset(data, 0, sizeof(t_data));
	data->num_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->num_must_eat = ft_atoi(av[5]);
	if (data->num_philos < 1 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || (ac == 6 && data->num_must_eat < 1)
		|| data->time_to_die <= data->time_to_sleep)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (printf("Error: Too Few Arguments.\n"), 1);
	if (init_all(&data, argv, argc) < 0)
		return (printf("Error: Failed to init parameters.\n"), 1);
	if (launch_mutexes(&data) < 0) // init forks & print_lock
		return (1);
	launch_philos(&data); // init philos & threads - philos start their routines, print data
	monitoring(&data); // monitor philos' status, and terminate if needed
	cleanup(&data); // free all malloced memory & destroy mutexes
	return (0);
}
