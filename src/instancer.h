#ifndef INSTANCES_H
#define INSTANCER_H

#include "common.h"
#include "idHeap.h"

#include "body.h"
#define INSTANCER_DATA_T Body_t


typedef size_t InstanceId_t; //Should be capped by max possible instances. 


typedef struct Instance_s Instance_t;
struct Instance_s {
	INSTANCER_DATA_T data;
	InstanceId_t next;
	InstanceId_t prev;
};


typedef struct {
	InstanceId_t firstOccupied;
	InstanceId_t lastOccupied;

	IdHeap_t freeIds;

	InstanceId_t numAllocated;
	Instance_t *array;
} Instancer_t;



Instancer_t instancer_init(InstanceId_t initAlloc);

InstanceId_t instancer_add(Instancer_t *instancer, INSTANCER_DATA_T instance);

void instancer_remove(Instancer_t *instancer, InstanceId_t id);

INSTANCER_DATA_T *instancer_get(const Instancer_t *instancer, InstanceId_t id);





#endif //INSTANCER_H