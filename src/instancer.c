#include "instancer.h"


Instancer_t instancer_init(InstanceId_t initAlloc)
{
	Instancer_t instancer = {
		//TODO
	}
}


InstanceId_t instancer_add(Instancer_t *instancer, INSTANCER_DATA_T instance)
{
	InstanceId_t id;

	if (!idHeap_isEmpty(&instancer->freeIds)) {
		id = 0;
		instancer->array[0].next = instancer->firstOccupied;
		instancer->firstOccupied = 0;
		instancer->array[0].prev = 0; //FIXME: work out a better way to encode NULL for an index.
		//Maybe just use pointers? TODO: USE pointers. 
	} else {
		id = idHeap_popMin(&instancer->freeIds);
		instancer->array[id].next = instancer->array[id-1].next; //As using minheap, can be sure this exists. 
		instancer->array[id].prev = id - 1;
		instancer->array[id-1].next = id;
	}
	instancer->array[id].data = instance;
	instancer->firstOccupied = id;
}


void instancer_remove(Instancer_t *instancer, InstanceId_t id)
{
	instancer->array[instancer->array[id].prev].next = instancer->array[id].next;
	idHeap_push(&instancer->freeIds, id);
	//No need to actually clear data. 
}


INSTANCER_DATA_T *instancer_get(const Instancer_t *instancer, InstanceId_t id)
{
	//TODO
}