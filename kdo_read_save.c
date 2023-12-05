/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_read_save.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/05 03:00:49 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

static int	_error(t_kdo_save_neat *save, int fd)
{
	close(fd);
	kdo_free_save(save);
	return (EXIT_FAILURE);
}

static t_bool	_good_extension(char *file_name)
{
	file_name = ft_strrchr(file_name, '.');
	if (!file_name)
		return (FT_FALSE);
	if (ft_strcmp(file_name, ".pop"))
		return (FT_FALSE);
	return (FT_TRUE);
}

static int	_alloc(t_kdo_save_neat *save)
{
	save->genome = malloc(save->population.genome_count
			* sizeof(t_kdo_save_genome));
	save->node = malloc(save->population.node_count
			* sizeof(t_kdo_save_node));
	save->link = malloc(save->population.link_count
			* sizeof(t_kdo_save_link));
	if (!save->genome || !save->node || !save->link)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	_read(t_kdo_save_neat *save, int fd)
{
	if (read(fd, save->genome, save->population.genome_count
			* sizeof(t_kdo_save_genome)) == INVALID_SIZE)
		return (EXIT_FAILURE);
	if (read(fd, save->node, save->population.node_count
			* sizeof(t_kdo_save_node)) == INVALID_SIZE)
		return (EXIT_FAILURE);
	if (read(fd, save->link, save->population.link_count
			* sizeof(t_kdo_save_link)) == INVALID_SIZE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	kdo_read_save(t_kdo_save_neat *save, char *file_name)
{
	int		fd;

	ft_bzero(save, sizeof(t_kdo_save_neat));
	if (!_good_extension(file_name))
		return (EXIT_FAILURE);
	fd = open(file_name, O_RDONLY);
	if (fd == INVALID_FD)
		return (EXIT_FAILURE);
	if (read(fd, &save->population, sizeof(t_kdo_save_population))
		== INVALID_SIZE)
		return (_error(save, fd));
	if (_alloc(save))
		return (_error(save, fd));
	if (_read(save, fd))
		return (_error(save, fd));
	close(fd);
	return (EXIT_SUCCESS);
}
