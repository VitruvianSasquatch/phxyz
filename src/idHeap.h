#ifndef HEAP_H
#define HEAP_H

typedef size_t Id_t; //Should be capped by max possible instances. 

typedef struct {
	Id_t *data;
	size_t numOccupied;
	size_t numAllocated;
} IdHeap_t;

IdHeap_t idHeap_init(void);

void idHeap_push(IdHeap_t *heap, Id_t id);

Id_t idHeap_popMin(IdHeap_t *heap);

bool idHeap_isEmpty(const IdHeap_t *heap);

#endif //HEAP_H