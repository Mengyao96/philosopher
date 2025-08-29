/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:53:12 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/29 15:38:02 by mezhang          ###   ########.fr       */
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
	printf("%lld %d %s\n", current_time_ms() - philo->data->start_time, philo->id, message);
	pthread_mutex_unlock(&(philo->data->print_lock));
}

static void	print_status(t_philo *philo)
{
	if (philo->status == 0)
		safe_print(philo, "is thinking.");
	else if (philo->status == 1)
		safe_print(philo, "is eating.");
	else if (philo->status == 2)
		safe_print(philo, "is sleeping.");
}

static void	take_the_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	safe_print(philo, "has taken a fork.");
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	while (1)
	{
		if (philo->data->is_end)
			break ;
		
		//thinking
		philo->status = 0;
		print_status(philo);

		
		//get forks
		if (philo->id % 2 == 0)
		{
			take_the_fork(philo, philo->l_fork);
			if (philo->data->is_end)
			{
				pthread_mutex_unlock(philo->l_fork);
				break ;
			}
			take_the_fork(philo, philo->r_fork);
			if (philo->data->is_end)
			{
				pthread_mutex_unlock(philo->l_fork);
				pthread_mutex_unlock(philo->r_fork);
				break ;
			}
		}
		else
		{
			take_the_fork(philo, philo->r_fork);
			if (philo->data->is_end)
			{
				pthread_mutex_unlock(philo->r_fork);
				break ;
			}
			take_the_fork(philo, philo->l_fork);
			if (philo->data->is_end)
			{
				pthread_mutex_unlock(philo->l_fork);
				pthread_mutex_unlock(philo->r_fork);
				break ;
			}
		}


		//eating
		philo->status = 1;
		print_status(philo);
		usleep(philo->data->time_to_eat * 1000);

		//update last meal time & num_eaten
		pthread_mutex_lock(&philo->lock);
		philo->last_meal_time = current_time_ms();
		philo->num_eaten += 1;
		pthread_mutex_unlock(&philo->lock);

		//take off forks
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);

		//sleeping
		philo->status = 2;
		print_status(philo);
		usleep(philo->data->time_to_sleep * 1000);

	}
	return (NULL);
}
