/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_dinner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 06:21:53 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/10 14:12:42 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_env(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->nbr_philos)
		free(env->philos_struct[i]);
	free(env->forks);
	free(env->print_msg);
	free(env->start_mtx);
	free(env->times_eat_mtx);
	free(env->check_finish);
	free(env->philos_threads);
	free(env->philos_struct);
}

void	ft_finish_threads(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->nbr_philos)
	{
		pthread_mutex_unlock(env->philos_struct[i]->fork_left);
		pthread_join(env->philos_threads[i], NULL);
	}
	i = -1;
	while (++i < env->nbr_philos)
	{	
		pthread_mutex_destroy(env->forks + i);
		pthread_mutex_destroy(env->times_eat_mtx + i);
	}
	pthread_mutex_destroy(env->forks);
	pthread_mutex_destroy(env->times_eat_mtx);
	pthread_mutex_destroy(env->print_msg);
	pthread_mutex_destroy(env->start_mtx);
	pthread_mutex_destroy(env->check_finish);
	free_env(env);
}

int	a_philo_is_starved(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->nbr_philos)
	{
		if (is_starved(env->philos_struct[i]))
		{
			pthread_mutex_lock(env->print_msg);
			env->can_print = 0;
			pthread_mutex_unlock(env->print_msg);
			return (1);
		}
	}
	return (0);
}

int	are_philos_full(t_env *env)
{
	int	i;
	int	philos_full;

	philos_full = 0;
	i = -1;
	while (++i < env->nbr_philos)
	{
		pthread_mutex_lock(env->philos_struct[i]->times_eat_mtx);
		if (env->philos_struct[i]->times_eaten >= env->times_must_eat)
			philos_full++;
		pthread_mutex_unlock(env->philos_struct[i]->times_eat_mtx);
		if (philos_full == env->nbr_philos)
		{
			pthread_mutex_lock(env->check_finish);
			env->finish_dinner = 1;
			pthread_mutex_unlock(env->check_finish);
			pthread_mutex_lock(env->print_msg);
			if (env->can_print)
				printf("\033[32;3m 😋 All philos are full 😋 \033[0m\n");
			env->can_print = 0;
			pthread_mutex_unlock(env->print_msg);
			return (1);
		}
	}
	return (0);
}

void	finish_dinner(t_env *env, int argc)
{
	int	x;

	x = 1;
	pthread_mutex_lock(env->start_mtx);
	pthread_mutex_unlock(env->start_mtx);
	while (x)
	{
		if (argc == 6)
		{
			if (are_philos_full(env))
				x = 0;
		}
		if (a_philo_is_starved(env))
			x = 0;
	}
	ft_finish_threads(env);
}
