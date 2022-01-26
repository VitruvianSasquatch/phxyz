#ifndef INSTANCES_H
#define INSTANCER_H

#include "common.h"
#include "idHeap.h"

// We define the type of data we want to store in the instancer here:
#include "body.h"
#define INSTANCER_DATA_T Body_t

//Note zero is a reserved value ID, used to reset the iterator and such. 

typedef struct Instance_s Instance_t;
struct Instance_s {
	INSTANCER_DATA_T data;
	Id_t next;
	Id_t prev;
};


typedef struct {
	Id_t maxId;
	IdHeap_t freeIds;

	Id_t numAllocated;
	Instance_t *array;
} Instancer_t;


/**
 * @brief Creates an empty instance manager. 
 * 
 * @return Instancer_t The created instance manager. 
 */
Instancer_t instancer_init(void);


/**
 * @brief Add an instance to the manager. 
 * 
 * @param instancer The instancer to add the instance to. 
 * @param instance The data of the entity to be stored. 
 * @return InstanceId_t The id assigned to the added instance. 
 */
Id_t instancer_add(Instancer_t *instancer, INSTANCER_DATA_T instance);

void instancer_remove(Instancer_t *instancer, Id_t id);

INSTANCER_DATA_T *instancer_get(const Instancer_t *instancer, Id_t id);

Id_t instancer_getNext(const Instancer_t *instancer, Id_t prevId);




#endif //INSTANCER_H