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
	if (j > 1)
		return (9999);
	else
		return (count);
}

int	ft_atoi(char *str)
{
	int	sign;
	int	result;
	int	i;

	result = 0;
	sign = whitespaces(str, &i);
	if (sign != 9999)
	{
		while (str[i] && str[i] >= 48 && str[i] <= 57)
		{
			result *= 10;
			result += str[i] - 48;
			i++;
		}
		result *= sign;
	}
	return (result);
}
