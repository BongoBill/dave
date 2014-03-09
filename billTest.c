#include <stdio.h>  //  for printf
#include <stdlib.h> //  for exit

//  make a more interesting queue size for testing
#define SDO_Q_SIZE  2

#include "SDOqueue.h"

int main()
{
    //  make some SDOs
    SDO B = {SENDINTR, 2, "BB", 20, 200} ;
    SDO A = {SENDINTR, 1, "AA", 10, 100} ;
    SDO D = {SENDINTR, 4, "DD", 40, 400} ;
    SDO C = {SENDINTR, 3, "CC", 30, 300} ;
    SDOqueue_t  Q ;

    //  Must alway initialize the Queue; if not, results are undefined.
    printf ("\nInitializing Queue\n") ;
    //  Make sure queue initialization works
    if (!SDOqueueInit(&Q))
    {
        printf("SDOqueueInit failed!\n") ;
        exit(0) ;
    }
    SDOqueueDump("Queue after initialization", &Q) ;

    printf ("\nReading from empty Queue\n") ;
    //  Make sure popping and peeking an empty queue fails as expected
    if (SDOqueuePop(&Q) || SDOqueuePeek(&Q))
    {
        printf("Either Popping or Peeking failed to fail on an empty queue\n") ;
        exit(0) ;
    }
    SDOqueueDump("After popping from empty queue, before filling", &Q) ;

    printf ("\nCheck if filling and overfilling a Queue works as expected:\n") ;
    printf("Adding SDO \"A\"\n") ;
    int result = SDOqueuePush(&Q, &A) ;
    if (result!=1)
    {
        printf("Adding A to a queue failed with %d\n", result) ;
        exit(0) ;
    }
    SDOqueueDump("After adding \"A\"", &Q) ;
    printf("Adding SDO \"B\"\n") ;
    result = SDOqueuePush(&Q, &B) ;
    if (result!=2)
    {
        printf("Adding B to a queue failed with %d\n", result) ;
        exit(0) ;
    }
    SDOqueueDump("After adding \"B\"", &Q) ;
    result = SDOqueuePush(&Q, &C) ;
    printf("Adding SDO \"C\"\n") ;
    if (result!=2)
    {
        printf("Adding C to a queue failed with %d\n", result) ;
        exit(0) ;
    }
    SDOqueueDump("After adding \"C\"", &Q) ;
    printf("Adding SDO \"D\"\n") ;
    result = SDOqueuePush(&Q, &D) ;
    if (result!=2)
    {
        printf("Adding D to a queue failed with %d\n", result) ;
        exit(0) ;
    }
    SDOqueueDump("After adding \"D\"", &Q) ;

    printf("\nVerify the queue contains what it should...") ;
    result = SDOqueueSize(&Q) ;
    if (result!=2)
    {
        printf("adding 4 things to a queue of size 2 incorrectly had %d items\n", result) ;
        exit(0) ;
    }
    SDOqueueDump("correct...  Queue now contains", &Q) ;

    printf("\nPopping what should be a \"C\"\n") ;
    SDOptr_t ptr = SDOqueuePop(&Q) ;
    SDOqueueDump("After popping a C", &Q) ;
    if (ptr!=&C)
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

    printf("\nPeeking at final element, which should be a \"D\"\n") ;
    ptr = SDOqueuePeek(&Q) ;
    if (ptr==&D)
        printf("Peeked in Queue and it had a D SDO\n") ;
    else
    {
        printf("Queue failed to peek a D SDO\n") ;
        exit(0) ;
    }
    SDOqueueDump("Queue after peek of final item", &Q) ;
    result = SDOqueueSize(&Q) ;
    if (result!=1)
    {
        printf("adding 4 things to a queue of size 2, popping one, and peeking at another should have 1 item, but had %d instead\n", result) ;
        exit(0) ;
    }

    printf("\nPopping the final entry, a \"D\"\n") ;
    ptr = SDOqueuePop(&Q) ;
    if (ptr==&D)
        SDOqueueDump("Queue after pop of \"D\" (final item)", &Q) ;
    else
    {
        printf("Queue failed to pop a D SDO\n") ;
        exit(0) ;
    }

    printf("\nAttempting to pop an empty queue\n") ;
    ptr = SDOqueuePop(&Q) ;
    if (ptr!=0)
    {
        printf("Popping from an empty queue failed as expected\n") ;
        exit(0) ;
    }
    else
        SDOqueueDump("Empty Queue after pop", &Q) ;

    printf("\nAttempting to peek into an empty queue\n") ;
    ptr = SDOqueuePeek(&Q) ;
    if (ptr!=0)
    {
        printf("Peeking from an empty queue failed as expected\n") ;
        exit(0) ;
    }
    else
        SDOqueueDump("Empty Queue after peek", &Q) ;

    result = SDOqueueSize(&Q) ;
    if (result==0)
        printf("\nSDO queue tests succeeded!\n") ;
    else
    {
        printf("The queue should be empty, but instead contained %d SDOs\n", result) ;
        SDOqueueDump("Empty Queue that isn't", &Q) ;
        exit(0) ;
    }
}   //  main
