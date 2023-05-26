#include "../philo.h"

void	starting_vars(char *argv[], t_env *start_map)
{
	struct timeval tv;
	unsigned long long time;

	start_map->nbr_philos = ft_atoi(argv[1]);
	start_map->time_to_die =  ft_atoi(argv[2]);
	start_map->time_to_eat = ft_atoi(argv[3]);
	start_map->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		start_map->must_eat_times = ft_atoi(argv[5]);
	gettimeofday(&tv, NULL);
	time = (unsigned long long)tv.tv_sec * 1000 + (unsigned long long)tv.tv_usec / 1000;
	start_map->start_time_ms = time;
}

void	start_philo_vars(int num, t_philo *philo_struct)
{
	philo_struct->id = num + 1;
	philo_struct->fork_left = 1;
	philo_struct->fork_right = 0;
	philo_struct->meals_eaten = 0;
}
