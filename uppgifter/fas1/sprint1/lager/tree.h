#ifndef __tree_h__
#define __tree_h__

#include <stdbool.h>

/// Change this definition and replace int with the appropriate type
/// in your program. Note, however, that your implementation of tree.c
/// should treat T as if it did not know the type.
typedef int T;
/// For now, let an element's key be string 
typedef char *K;

/// Define struct tree in your .c file not here! (why?)
typedef struct tree tree_t;

/// This function is used in tree_delete() to allow the trees which are
/// the sole owners of their data to free the data on delete.
typedef void(*tree_action)(K key, T elem);

/// \file tree.h
///
/// \author Tobias Wrigstad
/// \version 1.2
/// \date 2017-09-18
///
/// Changelog 2017-09-13
/// Updated the documentation
///
/// Changelog 2017-09-18
/// Review changes (docs only)
/// Fixed macro bug in tree_update
/// Added new helper functions


/// Creates a new tree
///
/// \returns: empty tree
tree_t *tree_new();

/// Remove a tree along with all T elements.
///
/// \param tree the tree
/// \param cleanup a function that takes a key and element as
///        argument, to be used to free memory. If this param is 
///        NULL, no cleanup of keys or elements will happen.
void tree_delete(tree_t *tree, tree_action cleanup);

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
/// \param key the key to check for inclusion in the tree
/// \returns: true if key is a key in the tree
bool tree_has_key(tree_t *tree, K key);

/// Returns the element for a given key in tree.
/// (The implementation may assume that the key exists, or reserve
/// e.g. NULL as a value to indicate failure)
/// 
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \returns: the element associated wity key key
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
  __extension__({ T tmp = tree_remove(t, k);    \
                  tree_insert(t, k, e);         \
                  tmp; })                       \

//////////// ================= Added in version 1.2
///
/// NOTE: Implementing these functions is NOT mandatory
///

/// Returns an array holding all the keys in the tree
/// in ascending order.
///
/// \param tree pointer to the tree
/// \returns: array of tree_size() keys
K *tree_keys(tree_t *tree);

/// Returns an array holding all the elements in the tree
/// in ascending order of their keys (which are not part
/// of the value).
///
/// \param tree pointer to the tree
/// \returns: array of tree_size() elements
T *tree_elements(tree_t *tree);

/// This function is used in tree_apply() to allow applying a function
/// to all elements in a tree. 
typedef void(*tree_action2)(K key, T elem, void *data);

enum tree_order { inorder = 0, preorder = -1, postorder = 1 };

/// Applies a function to all elements in the tree in a specified order.
/// Example (using shelf as key):
///
///     tree_t *t = tree_new();
///     tree_insert(t, "A25", some_item);
///     int number = 0;
///     tree_apply(t, inorder, print_item, &number);
///
/// where print_item is a function that prints the number and increments it,
/// and prints the item passed to it. 
///
/// \param tree the tree
/// \param order the order in which the elements will be visited
/// \param fun the function to apply to all elements
/// \param data an extra argument passed to each call to fun (may be NULL)
void tree_apply(tree_t *tree, enum tree_order order, tree_action2 fun, void *data);

#endif

