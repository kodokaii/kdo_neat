/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_mutate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/17 00:48:18 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_add_random_link(t_kdo_neat *nn, t_kdo_genome *genome)
{
	t_list		*node_from;
	t_list		*node_to;
	t_kdo_link	*link;

	if (genome->link_count < genome->node_count * genome->node_count)
	{
		node_from = kdo_get_node_free_link(genome);
		node_to = kdo_get_node_no_link_yet(node_from);
		link = kdo_get_link(nn, node_to->content);
		kdo_add_link(nn, node_from->content, link);
		genome->link_count++;
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
		node_from = kdo_get_linked_node(genome);
		link = kdo_get_random_link(node_from->content);
		new_link = kdo_get_link(nn, ((t_kdo_link *)link->content)->to);
		new_link->weight = 1.0f;
		new_node = kdo_get_node(nn,
				(((t_kdo_node *)node_from->content)->layer
					+ ((t_kdo_link *)link->content)->to->layer) / 2.0L,
				HIDDEN_NODE, genome->node_count);
		((t_kdo_link *)link->content)->to = new_node;
		kdo_add_link(nn, new_node, new_link);
		kdo_add_node(nn, genome, new_node, &kdo_node_layer_cmp);
		genome->link_count++;
	}
}

void	kdo_mutate(t_kdo_neat *nn, t_kdo_genome *genome)
{
	if (ft_randf() <= nn->params.mutate_link_prob)
		kdo_mutate_link(nn,
			kdo_get_random_link(kdo_get_random_node(genome)->content)->content);
	if (ft_randf() <= nn->params.link_add_prob)
		kdo_add_random_link(nn, genome);
	if (ft_randf() <= nn->params.mutate_node_prob)
		kdo_mutate_node(nn, kdo_get_random_node(genome)->content);
	if (ft_randf() <= nn->params.node_add_prob)
		kdo_add_random_node(nn, genome);
}
