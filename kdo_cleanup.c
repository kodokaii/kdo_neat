/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/30 23:13:56 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_free_population(t_kdo_population *population)
{
	ft_free(&population->alloc);
	free(population->genome);
	free(population->spacies);
	population->genome_count = 0;
	population->spacies_count = 0;
}

void	kdo_neat_cleanup(t_kdo_neat *nn, char *str_error, int error)
{
	kdo_free_population(&nn->population);
	kdo_free_population(&nn->old_population);
	free(nn->input);
	nn->input = NULL;
	nn->params.input_count = 0;
	free(nn->output);
	nn->output = NULL;
	nn->params.output_count = 0;
	ft_dprintf(STDERR_FILENO, "neat: %s\n", str_error);
	if (error)
		exit(error);
}
