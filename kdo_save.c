/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/04 18:59:19 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

static int	_alloc(t_kdo_save_neat *save)
{
	save->genome = malloc(save->population.genome_count
			* sizeof(t_kdo_save_genome));
	save->node = malloc(save->population.node_count
			* sizeof(t_kdo_save_node));
	save->link = malloc(save->population.link_count
			* sizeof(t_kdo_save_link));
	if (!save->genome || !save->node || !save->link)
	{
		free(save->genome);
		free(save->node);
		free(save->link);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	kdo_save(t_kdo_neat *nn)
{
	t_uint				i;

	ft_bzero(nn->params.save, sizeof(t_kdo_save_neat));
	kdo_save_population(nn);
	if (_alloc(nn->params.save))
		kdo_neat_cleanup(nn, ERRLOC, EXIT_FAILURE);
	i = 0;
	while (i < nn->population.genome_count)
		kdo_save_genome(nn, nn->population.genome + i++);
}
