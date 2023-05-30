/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 04:13:58 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/05/30 07:04:19 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_get_time(void)
{
	int				time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (unsigned long long)tv.tv_sec * 1000
		+ (unsigned long long)tv.tv_usec / 1000;
	return (time);
}

int	starting_vars(char *argv[], t_env *map)
{
	map->nbr_philos = ft_atoi(argv[1]);
	if (argv[5])
		map->must_eat_times = ft_atoi(argv[5]);
	map->start_time = ft_get_time();
	map->msg_mutex = malloc(sizeof(pthread_mutex_t) * 1);
	map->philos = malloc(sizeof(pthread_t) * map->nbr_philos);
	if (!map->philos)
		return (free(map->philos), 0);
	map->philo = malloc(sizeof(pthread_t) * map->nbr_philos);
	if (!map->philo)
		return (0);
	map->forks = malloc(sizeof(pthread_mutex_t) * map->nbr_philos);
	if (!map->forks)
		return (0);
	return (1);
}

int	start_philo_vars(int i, t_env *v, int argc, char **argv)
{
	if (pthread_mutex_init(&(v->forks[i]), NULL))
		return (0);
	if (pthread_mutex_init(&(v->msg_mutex[i]), NULL))
		return (0);
	v->philo[i].id = i + 1;
	v->philo[i].fork_left = &(v->forks[(i + 1) % v->nbr_philos]);
	v->philo[i].fork_right = &(v->forks[i]);
	v->philo[i].meals_eaten = 0;
	v->philo[i].time_to_die = ft_atoi(argv[2]);
	v->philo[i].time_to_eat = ft_atoi(argv[3]);
	v->philo[i].time_to_sleep = ft_atoi(argv[4]);
	v->philo[i].start_time = v->start_time;
	if (argc == 6)
		v->philo[i].time_to_sleep = ft_atoi(argv[5]);
	v->philo[i].msg_mutex = v->msg_mutex;
	printf("philo vars finished\n");
	return (1);
}

void	print_ms_p(t_philo *p, char *str)
{
	pthread_mutex_lock(p->msg_mutex);
	printf("%i, %s", p->id, str);
	pthread_mutex_unlock(p->msg_mutex);
}
