#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

struct timeval tv;
typedef struct t_list t_philo; 

typedef struct t_list
{
	int	last_time_eaten;
	int	meals_eaten;
	int fork_left;
	int fork_right;
	int	id;
	pthread_t philo;
	struct s_list	*env_struct;
} t_philo;

typedef struct s_list
{
	int	nbr_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat_times;
	unsigned int start_time_ms;
	pthread_mutex_t	*forks;
	t_philo *philos;
}	t_env;



int		ft_atoi(char *str);

void	starting_vars(char *argv[], t_env *start_map);

void	start_philo_vars(int num, t_philo *philo_struct);

#endif
