/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tracy <tracy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:53:12 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/28 17:32:16 by tracy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long current_time_ms(void)
{
	struct timeval	tv;
	long long		current_ms;

	gettimeofday(&tv, NULL);
	current_ms = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	return (current_ms);
}

void	safe_print(t_philo *philo, const char *message)
{
	pthread_mutex_lock(&(philo->data->print_lock));
	printf("%lld %d %s\n", current_time_ms(), philo->id, message);
	pthread_mutex_unlock(&(philo->data->print_lock));
}

void	print_status(t_philo *philo)
{
	long long	current_time;

	current_time = current_time_ms();
	if (philo->status == 0)
		safe_print(philo, "is thinking.");
	else if (philo->status == 1)
		safe_print(philo, "is eating.");
	else if (philo->status == 2)
		safe_print(philo, "is sleeping.");
}

void	take_the_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	safe_print(philo, "has taken a fork");
}

//thinking, (m)getting forks, eating and sleeping

void	philo_routine(t_philo *philo)
{
	long long	start_time;

	start_time = current_time_ms();
	while (1)
	{
		//thinking
		print_status(philo);

		//get forks
		if (philo->id % 2 == 0)
		{
			take_the_fork(philo, philo->l_fork);
			take_the_fork(philo, philo->r_fork);
		}
		else
		{
			take_the_fork(philo, philo->r_fork);
			take_the_fork(philo, philo->l_fork);
		}

		//eating
		philo->status = 1;
		print_status(philo);
		usleep(philo->data->time_to_eat * 1000);
		philo->last_meal_time = current_time_ms();
		philo->num_eaten += 1;

		//take off forks
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);

		//sleeping
		philo->status = 2;
		print_status(philo);
		usleep(philo->data->time_to_sleep * 1000);

		//quit
		if (philo->data->is_end)
			break ;
	}
}
