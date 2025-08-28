/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tracy <tracy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:41:56 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/28 19:18:14 by tracy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <machine/types.h>
# include <sys/time.h>

typedef struct s_data
{
	//parameter argvs
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_must_eat;

	//mutext
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;

	//other env vars
	long long		start_time;

	//terminating vars: 0 or 1
	// int				one_died; //in monitoring
	int				all_ate; //in monitoring
	int				is_end; //sharing termination status to philos

	//philosopher array
	struct s_philo	*philos;

}	t_data;

typedef struct s_philo
{
	int				id;
	int				num_eaten;
	long long		last_meal_time;
	int				status; // 0 = thinking, 1 = eating, 2 = sleeping

	//thread & common data
	pthread_t		thread_id; //main thread
	t_data			*data;

	//forks
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;

	//own data protection
	pthread_mutex_t	lock;

}	t_philo;

//parsing
int		ft_atoi(const char *str);
void	*ft_memset(void *b, int c, size_t len);
int		init_all(t_data *data, char **av, int ac);

//init all
int		launch_mutexes(t_data *data);
void	launch_philos(t_data *data);

//routine
void	philo_routine(t_philo *philo);

//clean up
void	cleanup(t_data *data);

#endif
