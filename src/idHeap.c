#include "common.h"
#include "idHeap.h"

#define MIN_ALLOC 16

#define PARENT(child) (((child) - 1) / 2)
#define CHILD_LEFT(parent) (2*(parent) + 1)
#define CHILD_RIGHT(parent) (2*(parent) + 2)


static inline void idHeap_swap(IdHeap_t *heap, size_t i, size_t j)
{
	InstanceId_t tmp = heap->data[i];
	heap->data[i] = heap->data[j];
	heap->data[j] = tmp;
}


static void bubbleUp(IdHeap_t *heap, size_t idIndex)
{
	while (idIndex != 0 && heap->data[PARENT(idIndex)] > heap->data[idIndex]) {
		idHeap_swap(heap, PARENT(idIndex), idIndex);
		idIndex = PARENT(idIndex);
	}
}


static void bubbleDown(IdHeap_t *heap, size_t idIndex)
{
	while (idIndex < heap->numOccupied && (heap->data[CHILD_LEFT(idIndex)] < heap->data[idIndex] || heap->data[CHILD_RIGHT(idIndex)] < heap->data[idIndex])) {
		//In loop, so we can assume a parent should be swapped with a child. 

		if (CHILD_RIGHT(idIndex) >= heap->numOccupied) { //If there is no right child
			idHeap_swap(heap, CHILD_LEFT(idIndex), idIndex);
			idIndex = CHILD_LEFT(idIndex);
		} else { //Then there must be two children
			if (heap->data[CHILD_LEFT(idIndex)] < heap->data[CHILD_RIGHT(idIndex)]) {
				idHeap_swap(heap, CHILD_LEFT(idIndex), idIndex);
				idIndex = CHILD_LEFT(idIndex);
			} else {
				idHeap_swap(heap, CHILD_RIGHT(idIndex), idIndex);
				idIndex = CHILD_RIGHT(idIndex);
			}
		}
	}
}




IdHeap_t idHeap_init(void)
{
	IdHeap_t idHeap = {
		.data = calloc(MIN_ALLOC, sizeof(InstanceId_t)), 
		.numAllocated = MIN_ALLOC,
		.numOccupied = 0
	};
	return idHeap;
}

void idHeap_push(IdHeap_t *heap, InstanceId_t id)
{
	if (heap->numOccupied >= heap->numAllocated) {
		heap->numAllocated *= 2; //TODO: Is it better to only increase one tree level at a time?
		heap->data = reallocarray(heap->data, heap->numAllocated, sizeof(InstanceId_t));
		assert(heap->data != NULL); 
	}
	heap->data[heap->numOccupied] = id;
	heap->numOccupied++;
	bubbleUp(heap, id);
}

InstanceId_t idHeap_popMin(IdHeap_t *heap)
{
	assert(!idHeap_isEmpty(heap));
	
	InstanceId_t retVal = heap->data[0];
	heap->data[0] = heap->data[heap->numOccupied - 1];
	heap->numOccupied--;
	bubbleDown(heap, 0);
	//TODO: Resize allocated block?
	return retVal;
}

inline bool idHeap_isEmpty(const IdHeap_t *heap)
{
	return (heap->numOccupied == 0);
}