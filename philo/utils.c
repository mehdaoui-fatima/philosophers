/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 17:39:24 by fmehdaou          #+#    #+#             */
/*   Updated: 2021/06/19 20:18:14 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_atoi(char *s)
{
	int				i;
	unsigned long	res;
	int				n;

	i = 0;
	res = 0;
	n = 1;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'
		|| s[i] == '\v' || s[i] == '\f' || s[i] == '\r')
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i++] == '-')
			n = -1;
	}
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		res = (res * 10) + (s[i] - '0');
		if (res > LONG_MAX && n == 1)
			return (-1);
		if (res > LONG_MAX && n == -1)
			return (0);
		i++;
	}
	return ((int)(res * n));
}

int	ft_ispositive(int *s, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (s[i] < 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] > '9' || s[i] < '0') && s[0] != '-' && s[0] != '+')
			return (0);
		i++;
	}
	return (1);
}

int	is_digits(char **argv, int c)
{
	int	i;

	i = 1;
	while (i < c)
	{
		if (!check_digit(argv[i]))
			return (0);
		i++;
	}
	return (1);
}
