/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:41:56 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/27 21:49:56 by mezhang          ###   ########.fr       */
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
	pthread_mutex_t	*mutexes;
	pthread_mutex_t	print_lock;

	//other env vars
	long long		start_time;

	//terminating vars: 0 or 1
	int				one_died;
	int				all_ate;
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
	pthread_t		thread_id;
	t_data			*data;

	//forks
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;

}	t_philo;

//parsing
int		ft_atoi(const char *str);
void	*ft_memset(void *b, int c, size_t len);
int		init_all(t_data *data, char **av, int ac);

//init all
int		launch_mutexes(t_data *data);
void	launch_philos(t_data *data);



//clean up
void	cleanup(t_data *data);

#endif
