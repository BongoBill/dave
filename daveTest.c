#include <stdio.h>  //  for printf
#include <stdlib.h> //  for exit
#include "SDOqueue.h"   //  for SDO Queue functcionatliry

int main()
{
    //  make some SDOs
    SDO A = {SENDINTR, 1, "A", 10, 100} ;
    SDO B = {SENDINTR, 2, "B", 20, 200} ;
    SDO C = {SENDINTR, 3, "C", 30, 300} ;
    SDO D = {SENDINTR, 4, "D", 40, 400} ;
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

    printf("\nFirst, push all four items\n") ;
    //  Because SDOqueuePush returns the resultant number items in the queue, you can test
    //  the first add like a boolean if convenient
    int ok = SDOqueuePush(&Q, &A) ;
    if (ok)
        ok = SDOqueuePush(&Q, &B) ;
    if (ok==2)
        ok = SDOqueuePush(&Q, &C) ;
    if (ok==3)
        ok = SDOqueuePush(&Q, &D) ;
    SDOqueueDump("After adding \"A\"-\"D\"", &Q) ;
    if (ok!=4)
    {
        printf("Adding A..D failed at some point!  E-mail Bil!\n") ;
        exit(0) ;
    }

    printf("\nNext, pop all four items\n") ;
    SDOptr_t    SDO ;
    //  Because SDOqueuePop returns NULL when it's empty, you can use it in a while loop.
    while ((SDO = SDOqueuePop(&Q)))  //  "=" intentional
        printf("Popped item with this pCmd: %s", SDO->pCmd) ;

    printf("\n\nRe-add \"A\"-\"D\", but in a different order\n") ;
    //  Not checking the output, I'm *that* confident.  :)
    (void) SDOqueuePush(&Q, &C) ;
    (void) SDOqueuePush(&Q, &D) ;
    (void) SDOqueuePush(&Q, &A) ;
    (void) SDOqueuePush(&Q, &B) ;
    SDOqueueDump("Queue now contains", &Q) ;

    printf("\nNext, pop only two items\n") ;
    int i ;
    for (i=0 ; i<2 ; i++)
        (void) SDOqueuePop(&Q) ;

    printf("\nRe-add \"A\" and \"B\" -- yes, you can have multiple copies of the same SDO if you want\n") ;
    //  Not checking the output, I'm *that* confident.  :)
    (void) SDOqueuePush(&Q, &B) ;
    (void) SDOqueuePush(&Q, &A) ;

    SDOqueueDump("\nThe queue should now contain Dave's favorite Swedish Pop Group!\n\t", &Q) ;

    printf("Which contains %d members\n", SDOqueueSize(&Q)) ;

}   //  main
