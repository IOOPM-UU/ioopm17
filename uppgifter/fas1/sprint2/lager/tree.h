#ifndef __tree_h__
#define __tree_h__

#include <stdbool.h>
#include "common.h"

typedef elem_t key_t;
typedef element_free_fun key_free_fun;

/// Define struct tree in your .c file not here! (why?)
typedef struct tree tree_t;

/// This function is used in tree_delete() to allow the trees which are
/// the sole owners of their data to free the data on delete.
typedef void(*tree_action)(key_t key, elem_t elem);

/// Creates a new tree
///
/// \param copy (may be NULL) a function applied to all elements when stored in the tree
/// \param key_free (may be NULL) used to free keys in tree_delete
/// \param elem_free (may be NULL) used to free elements in tree_delete
/// \param compare (may be NULL) used to compare keys
/// \returns: empty tree
tree_t *tree_new(element_copy_fun element_copy, key_free_fun key_free, element_free_fun elem_free, element_comp_fun compare);

/// Remove a tree along with all elem_t elements.
///
/// \param tree the tree
/// \param delete_keys if true, run tree's key_free function on all keys
/// \param delete_elements if true, run tree's elem_free function on all elements
void tree_delete(tree_t *tree, bool delete_keys, bool delete_elements);

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
/// Uses the tree's compare function to compare keys.
///
/// If tree's copy function is non-NULL, it will be applied to elem and its result
/// stored in the tree. Otherwise, elem will be stored in the tree. Note that keys are
/// never copied and are assumed to be immutable. 
///
/// \param tree pointer to the tree
/// \param key the key of element to be appended -- this is assumed to be an immutable value
/// \param elem the element 
/// \returns: true if successful, else false
bool tree_insert(tree_t *tree, key_t key, elem_t elem);

/// Checks whether a key is used in a tree
///
/// Uses the tree's compare function to compare keys.
/// 
/// \param tree pointer to the tree
/// \param key the key to check for inclusion in the tree
/// \returns: true if key is a key in the tree
bool tree_has_key(tree_t *tree, key_t key);

/// Finds the element for a given key in tree.
/// 
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \param result a pointer to where result can be stored (only defined when result is true)
/// \returns: true if key is a key in the tree
bool tree_get(tree_t *tree, key_t key, elem_t *result);

/// Removes the element for a given key in tree.
///
/// \param tree pointer to the tree
/// \param key the key of elem to be removed
/// \param result a pointer to where result can be stored (only defined when result is true)
/// \returns: true if key is a key in the tree
bool tree_remove(tree_t *tree, key_t key, elem_t *result);

/// Swap the element for a given key for another.
///
/// \param t pointer to the tree
/// \param k the key of elem to be changed
/// \param e the updated element 
/// \param result a elem_t where result will be stored (only defined when result is true)
/// \returns true if both operations succeeded
#define tree_update(t, k, e, tmp) \
  (tree_remove(t, k, &tmp) ? tree_insert(t, k, e) : false)

/// Returns an array holding all the keys in the tree
/// in ascending order.
///
/// \param tree pointer to the tree
/// \returns: array of tree_size() keys
key_t *tree_keys(tree_t *tree);

/// Returns an array holding all the elements in the tree
/// in ascending order of their keys (which are not part
/// of the value).
///
/// \param tree pointer to the tree
/// \returns: array of tree_size() elements
elem_t *tree_elements(tree_t *tree);

/// This function is used in tree_apply() to allow applying a function
/// to all elements in a tree. 
typedef bool(*key_elem_apply_fun)(key_t key, elem_t elem, void *data);

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
void tree_apply(tree_t *tree, enum tree_order order, key_elem_apply_fun fun, void *data);

#endif

