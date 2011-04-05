#pragma once
/*
 *      Copyright (C) 2011 Tobias Arrskog
 *      https://github.com/topfs2/essentials
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include <stdlib.h>

// Opaque structures.
typedef struct essentials_linkedlist_t *          essentials_linkedlist;
typedef struct essentials_linkedlist_iterator_t * essentials_linkedlist_iterator;

#define FOREACH(iterator, value) for (value = essentials_linkedlist_value(iterator); essentials_linkedlist_has_next(iterator) ; value = essentials_linkedlist_value(iterator = essentials_linkedlist_next(iterator)) )

typedef void (*essentials_linkedlist_free_value) (void *value, void *cls);

essentials_linkedlist           essentials_linkedlist_create    ();
void                            essentials_linkedlist_free      (essentials_linkedlist list, essentials_linkedlist_free_value free_value, void *cls);

void                            essentials_linkedlist_append    (essentials_linkedlist list, void *value);
essentials_linkedlist           essentials_linkedlist_merge     (essentials_linkedlist a, essentials_linkedlist b);

unsigned int                    essentials_linkedlist_length    (essentials_linkedlist list);
void *                          essentials_linkedlist_nth       (essentials_linkedlist list, unsigned int n);

essentials_linkedlist_iterator  essentials_linkedlist_begin     (essentials_linkedlist list);
essentials_linkedlist_iterator  essentials_linkedlist_next      (essentials_linkedlist_iterator iterator);
int                             essentials_linkedlist_has_next  (essentials_linkedlist_iterator iterator);
void *                          essentials_linkedlist_value     (essentials_linkedlist_iterator iterator);
