/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeklee <jaeklee@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:22:59 by jaeklee           #+#    #+#             */
/*   Updated: 2025/04/24 11:24:04 by jaeklee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_len(const char *s, unsigned int start, size_t len)
{
	size_t	str_len;

	str_len = ft_strlen(s);
	if (start >= str_len)
		return (0);
	if (str_len - start < len)
		return (str_len - start);
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*tmp;
	size_t	sub_len;

	i = 0;
	if (!s)
		return (NULL);
	sub_len = get_len(s, start, len);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	tmp = malloc(sizeof(char) * ((sub_len) + 1));
	if (!tmp)
		return (NULL);
	while (i < sub_len)
	{
		tmp[i] = s[start + i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
