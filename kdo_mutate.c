/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_mutate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/29 16:28:37 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_add_random_link(t_kdo_neat *nn, t_kdo_genome *genome)
{
	t_list		*node_from;
	t_list		*node_to;
	t_kdo_link	*link;

	if (genome->link_count < genome->node_count * (genome->node_count - 1) / 2)
	{
		ft_lstsort(&genome->node, kdo_node_layer_cmp);
		node_from = kdo_get_node_free_link(genome);
		node_to = kdo_get_no_linked_node(node_from);
		link = kdo_get_link(nn, node_to->data);
		kdo_add_link(nn, genome, node_from->data, link);
	}
}

void	kdo_add_random_node(t_kdo_neat *nn, t_kdo_genome *genome)
{
	t_list		*node_from;
	t_list		*link;
	t_kdo_node	*new_node;
	t_kdo_link	*new_link;

	if (genome->node_count && genome->link_count)
	{
		ft_lstsort(&genome->node, kdo_node_layer_cmp);
		node_from = kdo_get_linked_node(genome);
		link = kdo_get_random_link(node_from->data);
		new_link = kdo_get_link(nn, ((t_kdo_link *)link->data)->to);
		new_link->weight = 1.0f;
		new_node = kdo_get_node(nn,
				((t_kdo_node *)node_from->data)->layer + 1,
				HIDDEN_NODE, genome->node_count);
		((t_kdo_link *)link->data)->to = new_node;
		kdo_add_link(nn, genome, new_node, new_link);
		kdo_add_node(nn, genome, new_node);
		genome->link_count++;
	}
}

void	kdo_mutate(t_kdo_neat *nn)
{
	t_uint	i;

	i = 0;
	while (i < nn->population.genome_count)
		kdo_mutate_genome(nn, &nn->population.genome[i++]);
}
