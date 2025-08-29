/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:41:56 by mezhang           #+#    #+#             */
/*   Updated: 2025/08/29 12:50:24 by mezhang          ###   ########.fr       */
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

	int				is_end; //sharing termination status to philos

	//philosopher array
	struct s_philo	*philos;

}	t_data;

typedef struct s_philo
{
	int				id;
	int				num_eaten; //shared
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
int			ft_atoi(const char *str);
void		*ft_memset(void *b, int c, size_t len);
int			init_all(t_data *data, char **av, int ac);

//launch all
int			launch_forks(t_data *data);
int			launch_philos(t_data *data);

//routine
void		*philo_routine(void *arg);
long long 	current_time_ms(void);
void		safe_print(t_philo *philo, const char *message);

//monitoring
void 		monitoring(t_data *data);

//clean up
void		cleanup(t_data *data);

#endif
