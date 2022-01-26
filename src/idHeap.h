#ifndef HEAP_H
#define HEAP_H

#include "instancer.h"


typedef struct {
	InstanceId_t *data;
	size_t numOccupied;
	size_t numAllocated;
} IdHeap_t;

IdHeap_t idHeap_init(void);

void idHeap_push(IdHeap_t *heap, InstanceId_t id);

InstanceId_t idHeap_popMin(IdHeap_t *heap);

inline bool idHeap_isEmpty(const IdHeap_t *heap);

#endif //HEAP_H