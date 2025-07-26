/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dt <dt@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:11:33 by dt                #+#    #+#             */
/*   Updated: 2025/07/26 18:50:13 by dt               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		exit(1);
	while (*s != '\0' && *s != 32)
	{
		i++;
		s++;
	}
	return (i);
}

// int main(int argc, char **argv)
// {
// 	const char *s;
	
// 	s = "MAMA";
// 	printf("\n%d", (int)ft_strlen(s));
// 	return 0;
// }