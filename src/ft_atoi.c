/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpizzolo <mpizzolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 04:09:13 by mpizzolo          #+#    #+#             */
/*   Updated: 2023/06/06 18:14:16 by mpizzolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_err(char *str, int i, int j)
{
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		i++;
	while (str[i] && str[i] == 32)
		i++;
	if (str[i] && (str[i] == 43 || str[i] == 45))
		return (9999);
	if (str[i] && (str[i] >= '0' && str[i] <= '9'))
		return (9999);
	return (j);
}

int	whitespaces(char *str, int *ptr_i)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	j = 0;
	count = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while ((str[i] == 43 || str[i] == 45))
	{
		if (str[i] == 45)
			count *= -1;
		i++;
		j++;
	}
	*ptr_i = i;
	j = check_err(str, i, j);
	if (j > 1)
		return (9999);
	else
		return (count);
}

int	ft_atoi(char *str)
{
	int						sign;
	unsigned long long int	result;
	int						i;

	result = 0;
	sign = whitespaces(str, &i);
	if (sign != 9999)
	{
		while (str[i] && str[i] >= 48 && str[i] <= 57 && result < 2147483648)
		{
			result *= 10;
			result += str[i] - 48;
			i++;
		}
		if ((sign > 0 && result > INT32_MAX)
			|| (sign < 0 && result > 2147483648))
		{
			return (0);
		}
		return ((int)result * sign);
	}
	return (0);
}
