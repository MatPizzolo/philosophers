/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:19:35 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/02 08:02:22 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	initialize_philos_struct(t_env *env)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < env->nbr_philos)
	{
		if (pthread_mutex_init(env->forks + i, NULL) != 0)
			return (0);
		if (pthread_mutex_init(env->print_msg + i, NULL) != 0)
			return (0);
		if (pthread_mutex_init(env->shield_mtx + i, NULL) != 0)
			return (0);
		if (pthread_mutex_init(env->finish_dinner_mtx + i, NULL) != 0)
			return (0);
		philo = env->philos_struct[i];
		philo->id = i + 1;
		philo->print_msg = env->print_msg;
		philo->fork_left = &(env->forks[((i + 1) % env->nbr_philos)]);
		philo->fork_right = &(env->forks[i]);
		philo->shield_mtx = env->shield_mtx;
		philo->finish_dinner_mtx = env->finish_dinner_mtx;
		philo->env = env;
		philo->is_starved = 0;
	}
	return (1);
}

int	initialize_env_struct(t_env *env)
{
	int	nbr;
	int	i;

	nbr = env->nbr_philos;
	env->start_time = ft_get_time();
	env->finish_dinner = 0;
	env->philos_struct = (t_philo **)malloc(sizeof(t_philo *) * nbr);
	if (!env->philos_struct)
		return (0);
	i = -1;
	while (++i < nbr)
	{
		env->philos_struct[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!env->philos_struct[i])
			return (0);
	}
	env->philos_threads = (pthread_t *)malloc(sizeof(pthread_t) * nbr);
	if (!env->philos_threads)
		return (0);
	env->print_msg = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!env->print_msg)
		return (0);
	env->shield_mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nbr);
	if (!env->shield_mtx)
		return (0);
	env->finish_dinner_mtx = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nbr);
	if (!env->finish_dinner_mtx)
		return (0);
	env->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nbr);
	if (!env->forks)
		return (0);
	return (1);
}

int	vargs_to_env(t_env *env, char **argv)
{
	env->nbr_philos = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_sleep = ft_atoi(argv[3]);
	env->times_must_eat = ft_atoi(argv[4]);
	if (argv[5])
		env->times_must_eat = ft_atoi(argv[5]);
	return (1);
}
