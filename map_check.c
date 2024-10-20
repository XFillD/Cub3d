/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalechin <yalechin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:46:46 by yalechin          #+#    #+#             */
/*   Updated: 2024/10/20 16:51:55 by yalechin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Ignore all leading whitespaces.
//If the current row is the 0th row or the final row, only accept '1's and ' 's.
//else, The first and final character should always be a '1'.
//In the case of any non leading whitespaces, the only acceptable characters adjacent to the space are '1's or ' 's.
//If strlen(curr_row) > strlen(row_on_top) && current col > strlen(row_on_top), current character should be '1'
//If strlen(curr_row) > strlen(row_on_bottom) && current col > strlen(row_on_bottom), current character should be '1'

int check_border(char *line)
{
    size_t x; 

    x = 0; 
    while(x < ft_strlen(line) - 1)
    {
        if(line[x] != '1')
        {
            printf("Border error at row [%zu], its [%d]!\n", x, line[x]);
            return(0);
        }
        x++; 
    }
    return(1);
}

int map_check(t_game *game)
{
    int row; 
    int col; 
    int last_c; 

    row = 0; 
    last_c = 0; 

    while(row < game->map_h)
    {
        col = 0; 
        while(game->map[row][col] == ' ')
            col++; 
        
        if(row == 0 || row == game->map_h-1){
            if(!check_border(game->map[row]))
            {
                printf("error on line [%d]\n", row);
                printf("line is [%s]\n", game->map[row]);
                return (0); // border error 
            }
        } else {
            if(game->map[row][col] != '1')
            {
                printf("first 0 error\n");
                return(0); // starts with 0
            }
        }
        //printf("map h [%d]\n", game->map_h);
        if(row == game->map_h - 1)
        {
            last_c = ft_strlen(game->map[row]) - 1;
            //printf("1 last c is [%d]\n", last_c);
            //printf("map h [%d]\n", game->map_h);
        }
        else 
        {
            last_c = ft_strlen(game->map[row]) - 2;
            //printf("2 last c is [%d]\n", last_c);
        }
        

        while(col < last_c)
        {
            if (game->map[row][col] == ' ') 
            {
                // Check adjacency to the spaces
                if (game->map[row][col - 1] != '1' && game->map[row][col - 1] != ' ') {
                    return 0;  // Invalid character before space
                    }
                    if (game->map[row][col + 1] != '1' && game->map[row][col + 1] != ' ') {
                        return 0;  // Invalid character after space
                     }
            }
            col++;
        }
        if(game->map[row][last_c] != '1')
            {
                printf("last 0 error, its [%d], col[%d]\n", game->map[row][last_c], last_c);
                return(0); // starts with 0
            }
        if (row > 0) { // Check the row above
                int upper_length = strlen(game->map[row - 1]);
                if (col > upper_length && game->map[row][col] != '1') {
                    return 0;  // Invalid character based on upper row
                }
            }

            if (row < game->map_h - 1) { // Check the row below
                int lower_length = strlen(game->map[row + 1]);
                if (col > lower_length && game->map[row][col] != '1') {
                    return 0;  // Invalid character based on lower row
                }
            }
        row++; 
    }
    return(1);
}