/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:16:57 by jaeklee           #+#    #+#             */
/*   Updated: 2025/04/18 10:41:10 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	d;
	size_t	s;
	size_t	i;

	d = 0;
	s = 0;
	i = 0;
	while (d < size && dest[d] != '\0')
		d++;
	while (src[s] != '\0')
		s++;
	if (d == size)
	{
		return (size + s);
	}
	while (src[i] != '\0' && d + i < size - 1)
	{
		dest [d + i] = src [i];
		i++;
	}
	dest[d + i] = '\0';
	return (d + s);
}
