#ifndef LIST_H
#define LIST_H

typedef struct {
	void **data;
	size_t currentLength; 
	size_t allocatedLength;
} List_t;


List_t list_init(size_t length);


void list_free(List_t *list);


void *list_get(size_t index);


void list_append(void *element);


void list_removeIndex(size_t index);


void list_removeItem(void *element);



#endif //LIST_H