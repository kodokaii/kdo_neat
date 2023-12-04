/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_genome_utlis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/04 17:59:24 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

t_kdo_genome	*kdo_get_genome(t_kdo_neat *nn)
{
	t_kdo_genome	*genome;

	if (nn->population.genome_count < nn->params.genome_target_count)
	{
		genome = nn->population.genome + nn->population.genome_count;
		ft_bzero(genome, sizeof(t_kdo_genome));
		nn->population.genome_count++;
		return (genome);
	}
	return (NULL);
}

void	kdo_genome_init(t_kdo_neat *nn, t_kdo_genome *genome)
{
	t_list	*current;
	t_uint	id;
	t_uint	i;

	i = 0;
	id = 0;
	while (i++ < nn->params.input_count)
		kdo_add_node(nn, genome, kdo_get_node(nn, 0, INPUT_NODE, id++));
	i = 0;
	while (i++ < nn->params.output_count)
		kdo_add_node(nn, genome, kdo_get_node(nn, 1, OUTPUT_NODE, id++));
	current = genome->node;
	while (current)
	{
		kdo_node_init(nn, genome, current->data);
		current = current->next;
	}
}
