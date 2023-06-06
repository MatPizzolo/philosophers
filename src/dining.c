/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 04:30:05 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/06 15:33:27 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	grabbing_forks_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	print_ms_p(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork_right);
	print_ms_p(philo, "has taken a fork");
	pthread_mutex_lock(philo->env->print_msg);
	philo->times_eaten++;
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(philo->env->print_msg);
	print_ms_p(philo, "is eating");
	ft_usleep(philo->env->time_to_eat);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
	return (1);
}

int	sleep_and_think(t_philo *philo)
{
	print_ms_p(philo, "is sleeping");
	ft_usleep(philo->env->time_to_sleep);
	print_ms_p(philo, "is thinking");
	return (1);
}

int	philo_ations(t_philo *philo)
{
	if (!grabbing_forks_eating(philo))
		return (0);
	if (!sleep_and_think(philo))
		return (0);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->print_msg);
	pthread_mutex_unlock(philo->print_msg);
	if ((philo->id % 2) == 0)
		usleep(200);
	pthread_mutex_lock(philo->print_msg);
	while (!philo->env->someone_died && !philo->env->finish_dinner)
	{
		pthread_mutex_unlock(philo->print_msg);
		if (philo_ations(philo) == 0)
			break ;
		pthread_mutex_lock(philo->print_msg);
	}
	pthread_mutex_unlock(philo->print_msg);
	return (NULL);
}