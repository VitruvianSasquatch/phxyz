#include "common.h"
#include "idHeap.h"

#define MIN_ALLOC 16

#define PARENT(child) (((child) - 1) / 2)
#define LCHILD(parent) (2*(parent) + 1)
#define RCHILD(parent) (2*(parent) + 2)


static inline void idHeap_swap(IdHeap_t *heap, size_t i, size_t j)
{
	Id_t tmp = heap->data[i];
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
	while (LCHILD(idIndex) < heap->numOccupied) { //We have at least one child

		if (RCHILD(idIndex) >= heap->numOccupied) { //If there is no right child
			if (heap->data[LCHILD(idIndex)] < heap->data[idIndex]) {
				idHeap_swap(heap, LCHILD(idIndex), idIndex);
				idIndex = LCHILD(idIndex);
			} else {
				break;
			}
		} else { //Then there must be two children
			if (heap->data[LCHILD(idIndex)] < heap->data[RCHILD(idIndex)]) {
				idHeap_swap(heap, LCHILD(idIndex), idIndex);
				idIndex = LCHILD(idIndex);
			} else if (heap->data[RCHILD(idIndex)] < heap->data[idIndex]) {
				idHeap_swap(heap, RCHILD(idIndex), idIndex);
				idIndex = RCHILD(idIndex);
			} else {
				break;
			}
		}
	}
}




IdHeap_t idHeap_init(void)
{
	IdHeap_t idHeap = {
		.data = calloc(MIN_ALLOC, sizeof(Id_t)), 
		.numAllocated = MIN_ALLOC,
		.numOccupied = 0
	};
	return idHeap;
}

void idHeap_push(IdHeap_t *heap, Id_t id)
{
	if (heap->numOccupied >= heap->numAllocated) {
		heap->numAllocated *= 2; //TODO: Is it better to only increase one tree level at a time?
		heap->data = reallocarray(heap->data, heap->numAllocated, sizeof(Id_t));
		assert(heap->data != NULL); 
	}
	heap->data[heap->numOccupied] = id;
	bubbleUp(heap, heap->numOccupied);
	heap->numOccupied++;
}

Id_t idHeap_popMin(IdHeap_t *heap)
{
	assert(!idHeap_isEmpty(heap));

	Id_t retVal = heap->data[0];
	heap->data[0] = heap->data[heap->numOccupied - 1];
	heap->numOccupied--;
	bubbleDown(heap, 0);
	//TODO: Resize allocated block?
	return retVal;
}

bool idHeap_isEmpty(const IdHeap_t *heap)
{
	return (heap->numOccupied == 0);
}