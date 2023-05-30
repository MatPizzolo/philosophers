/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 04:13:52 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/05/30 07:03:19 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	printf("rt started\n");
	// pthread_mutex_lock(philo->msg_mutex);
	printf("Routine del %i\n", philo->id);
	pthread_mutex_lock(philo->fork_left);
	print_ms_p(philo, "grabbed fork\n");
	pthread_mutex_lock(philo->fork_right);
	print_ms_p(philo, "grabbed fork\n");
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	// pthread_mutex_unlock(philo->msg_mutex);
	return (arg);
}

int	starting_philos(t_env *v, int argc, char **argv)
{
	int		i;
	int		nbr;

	nbr = v->nbr_philos;
	i = -1;
	printf("starting philos\n\n");
	pthread_mutex_lock(v->msg_mutex);
	while (++i < nbr)
	{
		if (!start_philo_vars(i, v, argc, argv))
			return (0);
		if (pthread_create(&(v->philos[i]), NULL,
				routine, &(v->philo[i])) != 0)
		{
			printf("Failed to create philo thread\n");
			return (0);
		}
		printf("thread created\n\n");
	}
	pthread_mutex_unlock(v->msg_mutex);
	printf("msg unlock\n\n");
	return (1);
}

int	main(int argc, char	*argv[])
{
	t_env	start_vars;

	if (argc != 5 && argc != 6)
		return (printf("Invalid number of arguments"), 1);
	if (!starting_vars(argv, &start_vars))
		return (0);
	if (!starting_philos(&start_vars, argc, argv))
		return (free(&start_vars), 0);
	return (0);
}

