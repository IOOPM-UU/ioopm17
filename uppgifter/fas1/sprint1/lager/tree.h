#ifndef __tree_h__
#define __tree_h__

#include <stdbool.h>

/// Define struct tree in your .c file not here! (why?)
typedef struct tree tree_t;

/// For now, let an element's key be string 
typedef char *K;

/// Change this definition and replace int with the appropriate type
/// in your program. Note, however, that your implementation of list.c
/// should treat T as if it did not know the type.
typedef int T;

/// \file tree.h
///
/// \author Tobias Wrigstad
/// \version 1.1
/// \date 2017-09-03


/// Creates a new tree
///
/// \returns: empty tree
tree_t *tree_new();

/// Remove a tree along with all T elements.
/// Note, if T is a pointer, elements will not
/// be removed. 
///
/// \returns: empty tree
void tree_delete(tree_t *tree);

/// Get the size of the tree 
///
/// \returns: the number of nodes in the tree
int tree_size(tree_t *tree);

/// Get the depth of the tree 
///
/// \returns: the depth of the deepest subtree
int tree_depth(tree_t *tree);

/// Insert element into the tree. Returns false if the key is already used.
///
/// \param tree pointer to the tree
/// \param key the key of element to be appended
/// \param elem the element 
/// \returns: true if successful, else false
bool tree_insert(tree_t *tree, K key, T elem);

/// Checks whether a key is used in a tree
///
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \returns: true if key is a key in tree
bool tree_has_key(tree_t *tree, K key);

/// Returns the element for a given key in tree.
/// (The implementation may assume that the key exists.)
/// 
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \returns: true if key is a key in tree
T tree_get(tree_t *tree, K key);

/// This does not need implementation until Assignment 2
///
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \returns: the removed element
T tree_remove(tree_t *tree, K key);

/// Swap the element for a given key for another.
///
/// \param tree pointer to the tree
/// \param key the key of elem to be changed
/// \param elem the updated element 
/// \returns: the updated element
#define tree_update(t, k, e)                    \
  { T tmp = tree_remove(t, k);                  \
    tree_insert(t, k, e);                       \
    tmp; }                                      \

#endif
