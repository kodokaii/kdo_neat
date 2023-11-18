/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_diff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/18 02:24:40 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

float	kdo_diff_weight(t_kdo_link *link1, t_kdo_link *link2)
{
	return (ft_abs_float(link1->weight - link2->weight));
}

float	kdo_diff_bias(t_kdo_node *node1, t_kdo_node *node2)
{
	return (ft_abs_float(node1->bias - node2->bias));
}

void	kdo_diff_node(t_kdo_diff *diff, t_kdo_node *node1, t_kdo_node *node2)
{
	t_list	*current1;
	t_list	*current2;
	t_uint	same_link;
	int		cmp;

	same_link = 0;
	current1 = node1->link;
	current2 = node2->link;
	while (current1 && current2)
	{
		cmp = kdo_link_cmp(current1->content, current2->content);
		if (cmp <= 0)
			current1 = current1->next;
		if (0 <= cmp)
			current2 = current2->next;
		if (cmp == 0)
		{
			diff->weight
				+= kdo_diff_weight(current1->content, current2->content);
			same_link++;
		}
	}
	diff->link += node1->link_count + node2->link_count - 2 * same_link;
	diff->weight += kdo_diff_bias(node1, node2);
}

void	kdo_diff_genome(t_kdo_diff *diff,
		t_kdo_genome *genome1, t_kdo_genome *genome2)
{
	t_list	*current1;
	t_list	*current2;
	t_uint	same_node;
	int		cmp;

	same_node = 0;
	current1 = genome1->node;
	current2 = genome2->node;
	while (current1 && current2)
	{
		cmp = kdo_node_id_cmp(current1->content, current2->content);
		if (cmp < 0)
			diff->link += ((t_kdo_node *)current1->content)->link_count;
		if (cmp <= 0)
			current1 = current1->next;
		if (0 < cmp)
			diff->link += ((t_kdo_node *)current2->content)->link_count;
		if (0 <= cmp)
			current2 = current2->next;
		if (cmp == 0)
			kdo_diff_node(diff, current1->content, current2->content);
		if (cmp == 0)
			same_node++;
	}
	diff->node += genome1->node_count + genome2->node_count - 2 * same_node;
}

t_bool	is_same_species(t_kdo_neat *nn, t_kdo_genome *genome1, t_kdo_genome *genome2)
{
	t_kdo_diff	diff;
	float		delta;

	diff.link = 0;
	diff.node = 0;
	diff.weight = 0;
	diff.bias = 0;
	kdo_diff_genome(&diff, genome1, genome2);
	delta = 
}
