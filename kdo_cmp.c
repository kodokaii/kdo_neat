/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_cmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/15 21:14:16 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

int	kdo_link_cmp(t_kdo_link *link1, t_kdo_link *link2)
{
	return (link1->to->id - link2->to->id);
}

int	kdo_node_layer_cmp(t_kdo_node *node1, t_kdo_node *node2)
{
	return (node1->layer - node2->layer);
}

int	kdo_node_id_cmp(t_kdo_node *node1, t_kdo_node *node2)
{
	return (node1->id - node2->id);
}

int	kdo_genome_cmp(t_kdo_genome *genome1, t_kdo_genome *genome2)
{
	if (genome1->fitness < genome2->fitness)
		return (-1);
	if (genome1->fitness > genome2->fitness)
		return (1);
	return (0);
}
