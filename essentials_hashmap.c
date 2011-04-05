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

#include "essentials_hashmap.h"
#include "essentials_linkedlist.h"
#include <string.h>

struct essentials_hashmap_node_t
{
  const char *key;
  void *value;
};

struct essentials_hashmap_t
{
  essentials_linkedlist *buckets;
  int number_of_buckets;
};

essentials_hashmap essentials_hashmap_create(int number_of_buckets)
{
  essentials_hashmap map = malloc(sizeof(struct essentials_hashmap_t));

  map->number_of_buckets = number_of_buckets;
  map->buckets           = malloc(sizeof(essentials_linkedlist) * number_of_buckets);

  int i;
  for (i = 0; i < number_of_buckets; i++)
    map->buckets[i] = essentials_linkedlist_create();

  return map;
}

int essentials_hashmap_generate_hashcode(const char *key)
{
  int length = strlen(key);
  int hashcode = 0;

  while (length > 0)
  {
    hashcode += key[length - 1];
    length--;
  }

  return hashcode;
}

void essentials_hashmap_put(essentials_hashmap map, const char *key, void *value)
{
  if (map)
  {
    essentials_linkedlist bucket = map->buckets[essentials_hashmap_generate_hashcode(key) % map->number_of_buckets];

    struct essentials_hashmap_node_t *node = malloc(sizeof(struct essentials_hashmap_node_t));
    int keylength = strlen(key);
    node->key     = malloc(sizeof(char) * keylength);
    strcpy((char *)node->key, key);
    node->value   = value;

    essentials_linkedlist_append(bucket, node);
  }
}

void *essentials_hashmap_find(essentials_hashmap map, const char *key)
{
  if (map)
  {
    essentials_linkedlist bucket = map->buckets[essentials_hashmap_generate_hashcode(key) % map->number_of_buckets];

    essentials_linkedlist_iterator iterator = essentials_linkedlist_begin(bucket);
    struct essentials_hashmap_node_t *node;
    FOREACH(iterator, node)
    {
      if (strcmp(node->key, key) == 0)
        return node->value;
    }
  }

  return NULL;
}

void essentials_hashmap_free_key_value_pair(void *data, void *cls)
{
  struct essentials_hashmap_node_t *node = data;
  essentials_hashmap_free_value free_value = cls;

  if (node)
  {
    if (free_value && node->value)
      free_value(node->value);

    free((char *)node->key);
    free(node);
  }
}

void essentials_hashmap_free(essentials_hashmap map, essentials_hashmap_free_value free_value)
{
  if (map)
  {
    int bucket;
    for (bucket = 0; bucket < map->number_of_buckets; bucket++)
      essentials_linkedlist_free(map->buckets[bucket], essentials_hashmap_free_key_value_pair, free_value);

    free(map);
  }
}
