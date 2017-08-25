#ifndef __list_h
#define __list_h

typedef struct list	list;
typedef struct iterator iterator;

list		*mkList();
void		 append(list *, void*);
iterator	*mkIterator(list *);
void		 delete(list *, int);
int		 empty(struct list *l);
int		 length(struct list *l);
int		 hasMore(struct iterator *i);
void		*next(struct iterator *i);
void		 rmList(struct list *l);
void		 rmIterator(struct iterator *i);

#endif
