/*
 * Copyright (c) 2013 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: L. Felipe Perrone (perrone@bucknell.edu)
 */

#include <stdlib.h>
#include "circular-list.h" 
#include <stdio.h>

int circular_list_create(struct circular_list *l, int size) {
  l->buffer = calloc(size, sizeof(item));
  l->start = -1;
  l->end = -1;
  l->elems = 0;
  l->size = size;

  return 0;
}

int circular_list_insert(struct circular_list *l, item i) {
  if (i){
  	if(l->size > 0){
  		for(int x = 0; x < l->size; x++){
  			l->buffer[x+1] = l->buffer[x];
  		}
  		l->buffer[0] = i;
  	}
  	else{
  		l->buffer[0] = i;
  	}
  	l->elems +=1;
  }
  return 0;
}

int circular_list_remove(struct circular_list *l, item *i) {
	if(l->size >0){
		i = &l->buffer[l->start];
		for(int y = 0; y<l->size -1; y++){
			l->buffer[y] = l->buffer[y+1];
		}
		printf("%f",*i);
	}
	else{
		i = &l->buffer[l->start];
	}
	l->size -=1;

  return 0;
}
