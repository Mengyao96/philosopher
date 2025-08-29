/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:41:46 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/29 15:40:57 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (printf("Error: Too Few Arguments.\n"), 1);
	if (init_data(&data, argv, argc) < 0)
		return (printf("Error: Failed to init parameters.\n"), 1);
	if (launch_forks(&data) < 0)
		return (1);
	if (launch_philos(&data) < 0)
		return (cleanup(&data), 1);
	monitoring(&data);
	cleanup(&data);
	return (0);
}
