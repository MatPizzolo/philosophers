/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 03:59:40 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/02 10:03:30 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_usleep(int time)
{
	unsigned long	start_time;
	unsigned long	act_time;

	start_time = ft_get_time();
	act_time = start_time;
	while (start_time >= (act_time - time))
	{	
		act_time = ft_get_time();
		usleep(100);
	}
}

void	print_ms_p(t_philo *p, char *str)
{
	unsigned long	time;

	time = ft_get_time() - p->env->start_time;
	pthread_mutex_lock(p->print_msg);
	printf("%lu - %i, %s\n", time, p->id, str);
	pthread_mutex_unlock(p->print_msg);
}

unsigned long	ft_get_time(void)
{
	unsigned long	time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (unsigned long long)tv.tv_sec * 1000
		+ (unsigned long long)tv.tv_usec / 1000;
	return (time);
}

void	ft_finish_threads(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->nbr_philos)
	{
		printf("destoying: %i\n", i);
		if (pthread_join(env->philos_threads[i], NULL) == 0)
			printf("t: %i, joined succesfully\n", i);
		else
			printf("t:%i, already terminated\n", i);
	}
	i = -1;
	while (++i < env->nbr_philos)
	{	
		pthread_mutex_destroy(env->forks + i);
		pthread_mutex_destroy(env->print_msg + i);
		pthread_mutex_destroy(env->shield_mtx + i);
	}
}
