/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_error_managment.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <lagonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 15:57:22 by lagonzal          #+#    #+#             */
/*   Updated: 2023/01/30 19:35:03 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *ft_triple_free(char ***ptr)
{
    int     i;
    int     j;
    int     k;

    i = 0;
    while (ptr[i])
    {
        j = 0;
        while (ptr[i][j])
        {
            free(ptr[i][j]);
            j++;
        }
        free(ptr[i]);
        i++;
    }
    free(ptr);
    return (NULL);
}