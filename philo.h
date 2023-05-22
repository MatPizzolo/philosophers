#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

struct timeval tv;

typedef struct s_list
{
	int	number_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_times;
	unsigned int start_time_ms;
	pthread_mutex_t	*mutex;
}	t_map;

typedef struct t_list
{
	int	last_time_eaten;
	int	meals_eaten;
	int fork_left;
	int fork_right;
	int	id;
} t_philo;

int		ft_atoi(char *str);

void	starting_vars(char *argv[], t_map *start_map);

void	start_philo_vars(int num, t_philo *philo_struct);

#endif
