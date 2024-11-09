/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:35:05 by yalechin          #+#    #+#             */
/*   Updated: 2024/11/09 14:27:44 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

// prints an error message in red
void	error(char *error_text)
{
	printf(COLOUR_RED "%s\n" COLOUR_RESET, error_text);
}
