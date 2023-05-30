/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 04:16:30 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/05/30 05:31:23 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct t_list
{
	int				meals_eaten;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	unsigned long	last_time_eaten;
	unsigned long	start_time;
	pthread_mutex_t	*msg_mutex;
}	t_philo;

typedef struct s_list
{
	int				nbr_philos;
	int				must_eat_times;
	unsigned long	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*msg_mutex;
	t_philo			*philo;
	pthread_t		*philos;
}	t_env;



int		ft_atoi(char *str);

int		starting_vars(char *argv[], t_env *start_map);

int		start_philo_vars(int num, t_env *v, int argc, char **argv);

void	print_ms_p(t_philo *p, char *str);

#endif
