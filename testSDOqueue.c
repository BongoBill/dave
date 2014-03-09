#include <stdio.h>	//  for printf
#include <stdlib.h>	//  for exit
//  make a good queue size for testing
#define SDO_Q_SIZE	2

#include "SDOqueue.h"

int	main()
{
	//  make some SDOs
	SDO B = {SENDINTR, 2, "BB", 20, 200} ;
	SDO A = {SENDINTR, 1, "AA", 10, 100} ;
	SDO D = {SENDINTR, 4, "DD", 40, 400} ;
	SDO C = {SENDINTR, 3, "CC", 30, 300} ;
	SDOqueue_t	Q ;

	//  Must alway initialize the Queue; if not, results are undefined.
	printf ("Initializing Queue\n") ;
	//  Make sure queue initialization works
	if (!SDOqueueInit(&Q))
	{
		printf("SDOqueueInit failed!\n") ;
		exit(0) ;
	}

	SDOqueueDump("empty queue", &Q) ;

	printf ("reading from empty Queue\n") ;
	//  Make sure popping and peeking an empty queue fails as expected
	if (SDOqueuePop(&Q) || SDOqueuePeek(&Q))
	{
		printf("Either Popping or Peeking failed to fail on an empty queue\n") ;
		exit(0) ;
	}
	SDOqueueDump("after popping from empty queue, before filling", &Q) ;
	printf ("Check if filling and overfilling a Queue works as expected:\n") ;
	int result = SDOqueuePush(&Q, &A) ;
	if (result!=1)
	{
		printf("Adding A to a queue failed with %d\n", result) ;
		exit(0) ;
	}
	else
		printf("Added SDO \"A\"\n") ;
	result = SDOqueuePush(&Q, &B) ;
	if (result!=2)
	{
		printf("Adding B to a queue failed with %d\n", result) ;
		exit(0) ;
	}
	else
		printf("Added SDO \"B\"\n") ;
	result = SDOqueuePush(&Q, &C) ;
	if (result!=2)
	{
		printf("Adding C to a queue failed with %d\n", result) ;
		exit(0) ;
	}
	else
		printf("Added SDO \"C\"\n") ;
	result = SDOqueuePush(&Q, &D) ;
	if (result!=2)
	{
		printf("Adding D to a queue failed with %d\n", result) ;
		exit(0) ;
	}
	else
		printf("Added SDO \"D\"\n") ;

	//  verify the queue contains what it should
	result = SDOqueueSize(&Q) ;
	if (result!=2)
	{
		printf("adding 4 things to a queue of size 2 incorrectly had %d items\n", result) ;
		exit(0) ;
	}
	SDOqueueDump("prior to popping a C", &Q) ;
	printf ("and size is %d\n", SDOqueueSize(&Q)) ;
	SDOptr_t ptr = SDOqueuePop(&Q) ;
	SDOqueueDump("after popping a C", &Q) ;
	printf ("size is now %d\n", SDOqueueSize(&Q)) ;
	if (ptr==&C)
		printf("Queue popped a C SDO\n") ;
	else
	{
		printf("Queue failed to pop a C SDO\n") ;
		if (ptr==&D)
			printf("got a D instead\n") ;
		else if (ptr==&B)
			printf("got a B instead\n") ;
		else if (ptr==&A)
			printf("got a A instead\n") ;
		else if (ptr==0)
			printf("got an error instead\n") ;
		else
			printf("got a weird pointer %p, where queue=%p and e-o-q=%p\n", 
				ptr, Q.queue, Q.queue + SDO_Q_SIZE) ;
		exit(0) ;
	}
	ptr = SDOqueuePeek(&Q) ;
	if (ptr==&D)
		printf("Peeked in Queue and it had a D SDO\n") ;
	else
	{
		printf("Queue failed to peek a D SDO\n") ;
		exit(0) ;
	}
	result = SDOqueueSize(&Q) ;
	if (result!=1)
	{
		printf("adding 4 things to a queue of size 2, popping one, and peeking at another should have 1 item, but had %d instead\n", result) ;
		exit(0) ;
	}
	ptr = SDOqueuePop(&Q) ;
	if (ptr==&D)
		printf("Queue popped a D SDO\n") ;
	else
	{
		printf("Queue failed to pop a D SDO\n") ;
		exit(0) ;
	}
	ptr = SDOqueuePop(&Q) ;
	if (ptr!=0)
		printf("Popping from an empty queue failed as expected\n") ;
	else
	{
		printf("Popping from an empty queue did't fail as expected\n") ;
		exit(0) ;
	}
	ptr = SDOqueuePeek(&Q) ;
	if (ptr!=0)
		printf("Peeking from an empty queue failed as expected\n") ;
	else
	{
		printf("Peeking from an empty queue did't fail as expected\n") ;
		exit(0) ;
	}
	result = SDOqueueSize(&Q) ;
	if (result==0)
		printf("SDO queue tests succeeded\n") ;
	{
		printf("The queue should be empty, but instead contained %d SDOs\n", result) ;
		exit(0) ;
	}
}	//  main
