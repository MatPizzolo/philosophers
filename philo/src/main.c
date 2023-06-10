/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 03:58:40 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/10 14:14:13 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	start_dinner(t_env *env)
{
	int			i;
	int			nbr_philos;
	pthread_t	*philo_thread;
	t_philo		*philo_struct;

	i = -1;
	nbr_philos = env->nbr_philos;
	pthread_mutex_lock(env->start_mtx);
	while (++i < nbr_philos)
	{
		philo_thread = env->philos_threads + i;
		philo_struct = env->philos_struct[i];
		if (pthread_create(philo_thread, NULL, routine, philo_struct) != 0)
			return (printf("Failed when creating a thread\n"), 0);
	}
	env->start_time = ft_get_time();
	pthread_mutex_unlock(env->start_mtx);
	return (1);
}

void	vargs_to_env(t_env *env, char **argv)
{
	env->nbr_philos = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		env->times_must_eat = ft_atoi(argv[5]);
}

int	main(int argc, char *argv[])
{
	t_env	env;

	if (!check_args(argc, argv))
		return (printf("Invalid arguments\n"), 1);
	vargs_to_env(&env, argv);
	if (!initialize_env_struct(&env))
		return (printf("Failed to initialize env struct\n"), 2);
	if (!initialize_philos_struct(&env))
		return (printf("Failed to initialize philos struct\n"), 3);
	if (!start_dinner(&env))
		return (printf("Failed to start dinner\n"), 4);
	finish_dinner(&env, argc);
	return (0);
}
