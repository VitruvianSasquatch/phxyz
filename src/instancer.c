#include "instancer.h"

#define VERBOSE 1

Instancer_t instancer_init(void)
{
	Instancer_t instancer = {
		//TODO
		.maxId = 0, 
		.freeIds = idHeap_init(),

		.numAllocated = 1, //This is minimum
		.array = calloc(1, sizeof(Instance_t))
	};
	//.array cleared, so [0] points to itself forwards and backwards. 
	return instancer;
}


Id_t instancer_add(Instancer_t *instancer, INSTANCER_DATA_T instance)
{
	Id_t id;

	if (idHeap_isEmpty(&instancer->freeIds)) { //Heap empty, so no gaps in our array exist. 
		id = instancer->maxId + 1;
		instancer->maxId++;
	} else {
		id = idHeap_popMin(&instancer->freeIds);
	}

	if (instancer->maxId >= instancer->numAllocated) {
		instancer->numAllocated *= 2;
		instancer->array = reallocarray(instancer->array, instancer->numAllocated, sizeof(Instance_t));
	}

	instancer->array[id].next = instancer->array[id-1].next; //As using minheap, can be sure this exists. 
	instancer->array[id].prev = id - 1;
	instancer->array[id-1].next = id;
	instancer->array[id].data = instance;
	#ifdef VERBOSE
		printf("Added instance id %zu\n", id);
	#endif
	return id;
}


void instancer_remove(Instancer_t *instancer, Id_t id)
{
	instancer->array[instancer->array[id].prev].next = instancer->array[id].next;
	instancer->array[instancer->array[id].next].prev = instancer->array[id].prev;
	idHeap_push(&instancer->freeIds, id);
	memset(&instancer->array[id], 0, sizeof(Instance_t)); //TODO: decide if I need to actually clear this. 
	#ifdef VERBOSE
		printf("Removed instance id %zu\n", id);
	#endif
}


INSTANCER_DATA_T *instancer_get(const Instancer_t *instancer, Id_t id)
{
	return &instancer->array[id].data;
}


Id_t instancer_getNext(const Instancer_t *instancer, Id_t prevId)
{
	return instancer->array[prevId].next;
}