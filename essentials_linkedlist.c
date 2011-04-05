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

#include "essentials_linkedlist.h"

struct essentials_linkedlist_iterator_t
{
  void *value;
  struct essentials_linkedlist_iterator_t *next;
};

struct essentials_linkedlist_t
{
  essentials_linkedlist_iterator first;
  essentials_linkedlist_iterator last;
  unsigned int length;
};

essentials_linkedlist essentials_linkedlist_create()
{
  essentials_linkedlist list = malloc(sizeof(struct essentials_linkedlist_t));

  list->first   = NULL;
  list->last    = NULL;
  list->length  = 0;

  return list;
}

void essentials_linkedlist_free_node(struct essentials_linkedlist_iterator_t *node, essentials_linkedlist_free_value free_value, void *cls)
{
  if (node)
  {
    essentials_linkedlist_free_node(node->next, free_value, cls);

    if (free_value && node->value)
      free_value(node->value, cls);

    free(node);
  }
}

void essentials_linkedlist_free(essentials_linkedlist list, essentials_linkedlist_free_value free_value, void *cls)
{
  if (list)
  {
    essentials_linkedlist_free_node(list->first, free_value, cls);
    free(list);
  }
}

void essentials_linkedlist_append(essentials_linkedlist list, void *value)
{
  if (list)
  {
    essentials_linkedlist_iterator item = malloc(sizeof(struct essentials_linkedlist_iterator_t));
    item->value = value;

    if (list->last)
    {
      list->last->next = item;
      list->last = item;
    }
    else // Should only happen if first is also NULL
      list->last = list->first = item;

    list->length++;
  }
}

essentials_linkedlist essentials_linkedlist_merge(essentials_linkedlist a, essentials_linkedlist b)
{
  if (a)
  {
    if (b)
    {
      if (a->last)
      {
        a->last->next = b->first;
        a->last = b->last;
      }
      else
      {
        a->first = b->first;
        a->last  = b->last;
      }

      a->length += b->length;
    }

    return a;
  }
  else
    return b;
}

unsigned int essentials_linkedlist_length(essentials_linkedlist list)
{
  if (list)
    return list->length;
  else
    return 0;
}

void *essentials_linkedlist_nth(essentials_linkedlist list, unsigned int n)
{
  if (list)
  {
    if (n < essentials_linkedlist_length(list))
    {
      int i = 0;
      essentials_linkedlist_iterator iterator = essentials_linkedlist_begin(list);

      for (i = 0; i < n; i++)
        iterator = essentials_linkedlist_next(iterator);

      return essentials_linkedlist_value(iterator);
    }
  }

  return NULL;
}

essentials_linkedlist_iterator essentials_linkedlist_begin(essentials_linkedlist list)
{
  if (list)
    return list->first;
  else
    return NULL;
}

essentials_linkedlist_iterator essentials_linkedlist_next(essentials_linkedlist_iterator iterator)
{
  if (iterator)
    return iterator->next;
  else
    return NULL;
}

int essentials_linkedlist_has_next(essentials_linkedlist_iterator iterator)
{
  if (iterator)
    return 1;
  else
    return 0;
}

void *essentials_linkedlist_value(essentials_linkedlist_iterator iterator)
{
  if (iterator)
    return iterator->value;
  else
    return NULL;
}
