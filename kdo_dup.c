/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/02 22:46:03 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

static void	_dup_link(t_kdo_neat *nn, t_kdo_genome *genome_dst,
	t_kdo_node *node_dst, t_kdo_node *node_src)
{
	t_list		*current;
	t_kdo_node	*node_to;
	t_kdo_link	*link;

	current = node_src->link;
	while (current)
	{
		node_to = kdo_find_node(genome_dst, ((t_kdo_link *)current->data)->to);
		link = kdo_get_link(nn, node_to);
		link->weight = ((t_kdo_link *)current->data)->weight;
		link->enable = ((t_kdo_link *)current->data)->enable;
		kdo_add_link(nn, genome_dst, node_dst, link);
		current = current->next;
	}
}

static void	_dup_node(t_kdo_neat *nn,
		t_kdo_genome *genome_dst, t_kdo_genome *genome_src)
{
	t_list		*current;	
	t_kdo_node	*node;

	current = genome_src->node;
	while (current)
	{
		node = kdo_get_node(nn,
				((t_kdo_node *)current->data)->layer,
				((t_kdo_node *)current->data)->type,
				((t_kdo_node *)current->data)->id);
		node->bias = ((t_kdo_node *)current->data)->bias;
		node->activation_index
			= ((t_kdo_node *)current->data)->activation_index;
		kdo_add_node(nn, genome_dst, node);
		current = current->next;
	}
}

t_kdo_genome	*kdo_dup_genome(t_kdo_neat *nn, t_kdo_genome *genome_src)
{
	t_kdo_genome	*genome_dst;
	t_list			*current_src;
	t_list			*current_dst;

	genome_dst = kdo_get_genome(nn);
	if (genome_dst)
	{
		_dup_node(nn, genome_dst, genome_src);
		current_src = genome_src->node;
		current_dst = genome_dst->node;
		while (current_src)
		{
			_dup_link(nn, genome_dst, current_dst->data, current_src->data);
			current_src = current_src->next;
			current_dst = current_dst->next;
		}
		genome_dst->fitness = genome_src->fitness;
	}
	return (genome_dst);
}
