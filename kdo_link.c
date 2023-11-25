/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/24 21:33:09 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_feed_forward_link(t_kdo_link *link, float input)
{
	if (link->enable)
		link->to->input += input * link->weight;
}

void	kdo_crossover_link(t_kdo_link *link1, t_kdo_link *link2)
{
	if (ft_randf() < 0.5)
	{
		link1->weight = link2->weight;
		link1->enable = link2->enable;
	}
}

void	kdo_mutate_link(t_kdo_neat *nn, t_kdo_link *link)
{
	float	rng;

	rng = ft_randf();
	if (rng <= nn->params.link_toggle_prob)
		link->enable = !link->enable;
	if (rng <= nn->params.weight_random_prob)
		link->weight = (ft_randf() * 2) - 1;
	else if (rng <= nn->params.weight_shift_prob)
		link->weight += ((ft_randf_norm() * 2) - 1) / 10;
}
