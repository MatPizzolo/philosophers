/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 03:57:52 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/06 09:34:04 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct env	t_env;

typedef struct philo
{
	int				id;
	int				times_eaten;
	unsigned long	last_meal;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*print_msg;
	pthread_mutex_t	*shield_mtx;
	t_env			*env;
}	t_philo;

typedef struct env
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	t_philo			**philos_struct;
	pthread_t		*philos_threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_msg;
	pthread_mutex_t	*shield_mtx;
	unsigned long	start_time;
	int				finish_dinner;
	pthread_mutex_t	*finish_dinner_mtx;
	int				someone_died;
}	t_env;

/* ft_atoi*/
int				ft_atoi(char *str);

/* utils.c */
void			ft_usleep(int sleep);
void			print_ms_p(t_philo *p, char *str);
unsigned long	ft_get_time(void);
void			ft_finish_threads(t_env *env);
int				is_starved(t_philo *philo);

/* initialize */
int				initialize_env_struct(t_env *env);
int				initialize_philos_struct(t_env *env);
int				vargs_to_env(t_env *env, char **argv);

/* dining.c */
void			*routine(void *arg);

/* finish_dinner.c */
int				finish_dinner(t_env *env, int argc);

#endif