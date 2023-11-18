/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_diff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/18 13:53:38 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

float	kdo_compatibility_weight(t_kdo_link *link1, t_kdo_link *link2)
{
	return (ft_abs_float(link1->weight - link2->weight));
}

float	kdo_compatibility_bias(t_kdo_node *node1, t_kdo_node *node2)
{
	return (ft_abs_float(node1->bias - node2->bias));
}

void	kdo_compatibility_node(t_kdo_compatibility *compatibility,
		t_kdo_node *node1, t_kdo_node *node2)
{
	t_list	*current1;
	t_list	*current2;
	int		cmp;

	current1 = node1->link;
	current2 = node2->link;
	while (current1 && current2)
	{
		cmp = kdo_link_cmp(current1->data, current2->data);
		if (cmp <= 0)
			current1 = current1->next;
		if (0 <= cmp)
			current2 = current2->next;
		if (cmp == 0)
		{
			compatibility->diff_weight
				+= kdo_compatibility_weight(current1->data, current2->data);
			compatibility->same_link += 1.0f;
		}
	}
}

void	kdo_compatibility_genome(t_kdo_compatibility *compatibility,
		t_kdo_genome *genome1, t_kdo_genome *genome2)
{
	t_list	*current1;
	t_list	*current2;
	int		cmp;

	current1 = genome1->node;
	current2 = genome2->node;
	while (current1 && current2)
	{
		cmp = kdo_node_id_cmp(current1->data, current2->data);
		if (cmp <= 0)
			current1 = current1->next;
		if (0 <= cmp)
			current2 = current2->next;
		if (cmp == 0)
			kdo_compatibility_node(compatibility, current1->data, current2->data);
		if (cmp == 0)
		{
			compatibility->diff_bias
				+= kdo_compatibility_bias(current1->data, current2->data);
			compatibility->same_node += 1.0f;
		}
	}
}

t_bool	is_same_species(t_kdo_neat *nn, t_kdo_genome *genome1, t_kdo_genome *genome2)
{
	t_kdo_compatibility	compatibility;
	float				delta;

	compatibility.same_link = 0.0f;
	compatibility.same_node = 0.0f;
	compatibility.diff_weight = 0.0f;
	compatibility.diff_bias = 0.0f;
	kdo_compatibility_genome(&compatibility, genome1, genome2);
	compatibility.diff_link = (float)(genome1->link_count + genome2->link_count)
		- 2.0f * compatibility.same_link;
	compatibility.diff_node = (float)(genome1->node_count + genome2->node_count)
		- 2.0f * compatibility.same_node;
	compatibility.diff_weight /= compatibility.same_link;
	compatibility.diff_bias /= compatibility.same_node;
}
