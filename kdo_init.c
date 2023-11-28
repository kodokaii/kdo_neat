/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/28 14:41:15 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_init(t_kdo_neat *nn, t_kdo_neat_params *params)
{
	ft_bzero(nn, sizeof(t_kdo_neat));
	kdo_population_init(nn, &nn->population);
	kdo_population_alloc(nn, &nn->old_population);
	nn->params = *params;
	nn->input = ft_calloc(params->input_count, sizeof(float));
	nn->output = ft_calloc(params->output_count, sizeof(float));
}
