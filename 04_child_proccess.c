/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_child_proccess.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagonzal <larraingonzalez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:44:27 by lagonzal          #+#    #+#             */
/*   Updated: 2023/02/07 16:44:27 by lagonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	child_proccess(int rp, int fd[2], t_cmnd_line *args)
{
	first_cmnd();
	middle_cmnds();
}
