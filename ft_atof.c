/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiru <abiru@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 22:56:21 by abiru             #+#    #+#             */
/*   Updated: 2023/01/26 21:28:19 by abiru            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int	skip_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

static int	cus_strlen(const char *str)
{
	int	i;
	int	j;

	j = 0;
	i = skip_spaces(str);
	while (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			j++;
		else
			break ;
		i++;
	}
	return (j);
}

static int	ft_sign(const char *str, int i)
{
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return (-1);
	}
	return (1);
}

double	get_float(const char *str, int start, int sign)
{
	int		i;
	double	res;

	i = -1;
	res = 0.0;
	if (str[start] == '\0')
		return (0);
	start++;
	if (str[start] < '0' || str[start] > '9')
		return (3.0);
	while (++i < 6)
	{
		if (str[start] && str[start] >= '0' && str[start] <= '9')
			res = (res * 10) + (str[start] - '0');
		else
			res *= 10;
		start++;
	}
	return (sign * (res / 1000000));
}

double	ft_atof(char *str)
{
	int	result;
	int	i;
	int	sign;

	result = 0;
	sign = 1;
	i = 0;
	i = (int)skip_spaces(str);
	sign = (int)ft_sign(str, i);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (cus_strlen(str) > 19 || !str[i])
		return (3.0);
	while (str[i] && str[i] != '.')
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = (result * 10) + str[i] - '0';
		else
			return (3.0);
		if (result > 0)
			return (3.0);
		i++;
	}
	return (get_float(str, i, sign));
}
