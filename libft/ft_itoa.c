/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:45:09 by jaeklee           #+#    #+#             */
/*   Updated: 2025/04/24 17:41:23 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_num(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int			len;
	int			sign;
	char		*tmp;
	long int	num;

	sign = 0;
	num = n;
	len = count_num(num);
	tmp = malloc(len + 1);
	if (!tmp)
		return (NULL);
	if (num < 0)
	{
		sign = -1;
		num = num * -1;
	}
	tmp[len] = '\0';
	while (--len >= 0)
	{
		tmp[len] = (num % 10) + '0';
		num = num / 10 ;
		if (len == 0 && sign == -1)
			tmp[0] = '-';
	}
	return (tmp);
}
