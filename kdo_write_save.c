/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_write_save.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/05 02:55:32 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

static int	_write(t_kdo_save_neat *save, int fd)
{
	if (write(fd, &save->population,
			sizeof(t_kdo_save_population)) == INVALID_FD)
		return (EXIT_FAILURE);
	if (write(fd, save->genome, save->population.genome_count
			* sizeof(t_kdo_save_genome)) == INVALID_FD)
		return (EXIT_FAILURE);
	if (write(fd, save->node, save->population.node_count
			* sizeof(t_kdo_save_node)) == INVALID_FD)
		return (EXIT_FAILURE);
	if (write(fd, save->link, save->population.link_count
			* sizeof(t_kdo_save_link)) == INVALID_FD)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	kdo_write_save(t_kdo_save_neat *save, char *file_name)
{
	int		fd;

	fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == INVALID_FD)
		return (EXIT_FAILURE);
	if (_write(save, fd))
	{
		close (fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}
