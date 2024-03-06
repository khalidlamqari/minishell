/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamqari <klamqari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:54:25 by zel-ouad          #+#    #+#             */
/*   Updated: 2024/02/27 08:55:56 by klamqari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_fill_num(unsigned int n, long int len, char *r)
{
	while (n > 0)
	{
		r[len--] = (n % 10) + 48;
		n = n / 10;
	}
	return (r);
}

static long int	ft_count_digit(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
	{
		count = 1;
	}
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*r;
	long int		size;
	unsigned int	num;

	size = ft_count_digit(n);
	r = (char *)malloc(sizeof(char) * (size + 1));
	if (!r)
		return (ft_throw(strerror(errno), NULL, 0, 1), NULL);
	r[size--] = '\0';
	if (n == 0)
		r[0] = '0';
	if (n < 0)
	{
		num = n * -1;
		r[0] = '-';
	}
	else
		num = n;
	r = ft_fill_num(num, size, r);
	return (r);
}
