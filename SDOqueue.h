#ifndef SDO_Q_H
#define SDO_Q_H

#include "SDO.h"

//  if a Queue size isn't defined, default to a nice number
#ifndef SDO_Q_SIZE
#define SDO_Q_SIZE	14
#endif

//  SDO Queue structure
typedef	struct 
{	
	SDOptr_t	 queue[SDO_Q_SIZE+1] ;
	SDOptr_t 	*front ;
	SDOptr_t 	*back ;

}	SDOqueue_t ;

typedef SDOqueue_t	*SDOqueuePtr_t ;

int SDOqueueInit(SDOqueuePtr_t q)
{
	if (q)
	{
		q->front = q->queue ;
		q->back = q->queue ;
		return 1 ;
	}
	else
		return 0 ;	//  bad queue pointer passed in

}	//  SDOqueueInit

int SDOqueueSize(const SDOqueuePtr_t q)
{
	if (!q || !q->front || !q->back)
		return -1 ;	//  bad queue pointer or uninitialized queue passed in

	if (q->back >= q->front)
			return (q->back - q->front) ;
		else
			return (q->back - q->queue + q->queue+SDO_Q_SIZE + 1 - q->front) ;

}	//  SDOqueueSize

void SDOqueueDump(const char *preamble, const SDOqueuePtr_t q)
{
	int frontLoc = -1 ;
	int backLoc = -1 ;
	int i ;
	for (i=0 ; i<=SDO_Q_SIZE ; i++)
	{
		if (q->front==q->queue+i)
			frontLoc = i ;
		if (q->back==q->queue+i)
			backLoc = i ;
	}
	printf("%s: SDOqueue's front pointer is at element %d, and back pointer is at element %d\n",
		preamble, frontLoc, backLoc) ;

}	//  SDOqueueDump

SDOptr_t SDOqueuePeek(const SDOqueuePtr_t q)
{
	if (!q || SDOqueueSize(q)<=0)
		return 0 ;	//  bad pointer or empty queue, return NULL
	
	//  return the front of the queue without decrementing it
	return *(q->front) ;

}	//  SDOqueuePeek

SDOptr_t SDOqueuePop(SDOqueuePtr_t q)
{
	if (!q || SDOqueueSize(q)<=0)
		return 0 ;	//  bad pointer or empty queue, return NULL
	
	//  save the front of the queue to return
	SDOptr_t	ptr = SDOqueuePeek(q) ;

	//  decrement the front of the queue
	if (q->front>=q->queue+SDO_Q_SIZE)
		q->front = q->queue ;
	else
		q->front++ ;

	return ptr ;

}	//  SDOqueuePop

int SDOqueuePush(SDOqueuePtr_t q, SDOptr_t item)
{
	if (!q || !q->front || !q->back)
		return -1 ;	//  bad queue pointer or uninitialized queue passed in

	//  dump location of pointers
	SDOqueueDump("Push starting", q) ;

	//  if queue is full, make room
	while (SDOqueueSize(q)>=SDO_Q_SIZE)
	{
		SDOqueueDump("Queue full prior to push", q) ;
		(void) SDOqueuePop(q) ;	//  pop the oldest
		SDOqueueDump("Queue after popping an item to make room", q) ;
	}
			
	if (q->back==q->queue+SDO_Q_SIZE)
		q->back = q->queue ;
	else
		q->back++ ;

	//  Assign item to the back of the queue
	*(q->back) = item ;

	//  dump location of pointers
	SDOqueueDump("Push completed", q) ;

	//  return the current length of the queue
	return SDOqueueSize(q) ;
}	//  SDOqueuePush
#endif //  SDO_Q_H
