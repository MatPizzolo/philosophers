/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 03:58:40 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/06 15:32:43 by mpizzolo         ###   ########.fr       */
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
	pthread_mutex_lock(env->print_msg);
	while (++i < nbr_philos)
	{
		philo_thread = env->philos_threads + i;
		philo_struct = env->philos_struct[i];
		if (pthread_create(philo_thread, NULL, routine, philo_struct) != 0)
			return (printf("Failed when creating a thread\n"), 0);
	}
	// env->start_time = ft_get_time();
	pthread_mutex_unlock(env->print_msg);
	return (1);
}

static void	ft_leaks(void)
{
	system("leaks -q philo");
}

int	main(int argc, char *argv[])
{
	t_env	env;

	atexit(ft_leaks);
	if (!check_args(argc, argv))
		return (printf("Invalid arguments\n"), 0);
	if (!vargs_to_env(&env, argv))
		return (printf("Failed to get argv's\n"), 0);
	if (!initialize_env_struct(&env))
		return (printf("Failed to initialize env struct\n"), 0);
	if (!initialize_philos_struct(&env))
		return (printf("Failed to initialize philos struct\n"), 0);
	if (!start_dinner(&env))
		return (printf("Failed to start dinner\n"), 0);
	if (!finish_dinner(&env, argc))
		return (0);
	return (0);
}
