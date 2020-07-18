#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

#ifdef VERBOSE
#define VERBOSE_PRINT(S, ...) printf (S, ##__VA_ARGS__);
#else
#define VERBOSE_PRINT(S, ...) ;
#endif

#define MAX_OCCUPANCY      3
#define NUM_ITERATIONS     100
#define NUM_PEOPLE         20
#define FAIR_WAITING_COUNT 4

/**
 * You might find these declarations useful.
 */
enum Endianness {LITTLE = 0, BIG = 1};
const static enum Endianness oppositeEnd [] = {BIG, LITTLE};

struct Well {
  // TODO
  uthread_mutex_t mutex;
  uthread_cond_t changeEndianness;
  uthread_cond_t empty;
  uthread_cond_t notFull;
  int occupancy;
  int endianness;
  int deniedEntry_count;
};

struct Well* createWell() {
  struct Well* Well = malloc (sizeof (struct Well));
  // TODO
  Well->mutex = uthread_mutex_create();
  Well->changeEndianness = uthread_cond_create(Well->mutex);
  Well->empty = uthread_cond_create(Well->mutex);
  Well->notFull = uthread_cond_create(Well->mutex);
  Well->occupancy = 0;
  Well->endianness = NULL;
  int deniedEntry_count = 0;
  return Well;
}

struct Person {
	int endianness;
};

struct Person* createPerson() {
	struct Person *person = malloc(sizeof(struct Person));
	person->endianness = random() % 2;
	return person;
}

struct Well* Well;

#define WAITING_HISTOGRAM_SIZE (NUM_ITERATIONS * NUM_PEOPLE)
int             entryTicker;                                          // incremented with each entry
int             waitingHistogram         [WAITING_HISTOGRAM_SIZE];
int             waitingHistogramOverflow;
uthread_mutex_t waitingHistogrammutex;
int             occupancyHistogram       [2] [MAX_OCCUPANCY + 1];

void enterWell (enum Endianness g) {
  // TODO
  
	printf("entering well\n");
	Well->occupancy += 1;
    assert (Well->endianness == g);
    assert (Well->occupancy <= MAX_OCCUPANCY);
    occupancyHistogram [Well->endianness] [Well->occupancy] ++;
}

void* tryEnter (void* person) {
	struct Person* p = person;
	uthread_mutex_lock (Well->mutex);
	if (Well->occupancy == 0) {
		Well->endianness = p->endianness;
		uthread_cond_signal (Well->changeEndianness);
		enterWell(p->endianness);
	} else if (Well->endianness == p->endianness) {
		if (Well->occupancy >= 3) {
			uthread_cond_wait (Well->notFull);
		}
		enterWell(p->endianness);
	} else {
		Well->deniedEntry_count++;
		uthread_cond_wait (Well->empty);
		Well->deniedEntry_count = 0;
		Well->endianness = p->endianness;
		uthread_cond_signal (Well->changeEndianness);
		enterWell(p->endianness);
	}
	uthread_mutex_unlock (Well->mutex);
}

void leaveWell() {
  // TODO
	printf("leaving well\n");
	uthread_mutex_lock (Well->mutex);
	Well->occupancy -=1;
	uthread_cond_signal (Well->notFull);
	if (Well->occupancy == 0) {
		uthread_cond_signal (Well->empty);
	}
	uthread_mutex_unlock (Well->mutex);
}

void recordWaitingTime (int waitingTime) {
  uthread_mutex_lock (waitingHistogrammutex);
  if (waitingTime < WAITING_HISTOGRAM_SIZE)
    waitingHistogram [waitingTime] ++;
  else
    waitingHistogramOverflow ++;
  uthread_mutex_unlock (waitingHistogrammutex);
}

//
// TODO
// You will probably need to create some additional produres etc.
//

void* person (void *p) {
	for (int n=0; n<NUM_ITERATIONS; n++) {
		uthread_mutex_lock (Well->mutex);
        int startTime = entryTicker;
		if (Well->deniedEntry_count == 3) {
			uthread_cond_wait(Well->changeEndianness);
		}
		uthread_mutex_unlock (Well->mutex);
		tryEnter(p);
        recordWaitingTime (entryTicker - startTime - 1);
		for (int i=0; i<NUM_PEOPLE; i++) {
			uthread_yield();
		}
		leaveWell();

		for (int i=0; i<NUM_PEOPLE; i++) {
			uthread_yield();
		}
	}
}

int main (int argc, char** argv) {
  uthread_init (1);
  Well = createWell();
  uthread_t pt [NUM_PEOPLE];
  waitingHistogrammutex = uthread_mutex_create ();

  // TODO
  for (int i=0; i<NUM_PEOPLE; i++) {
      struct Person *p = createPerson();
      pt[i] = uthread_create(person, p);
      printf("%d\n",p->endianness);
  }
  uthread_join(pt[1], 0);
  printf ("Times with 1 little endian %d\n", occupancyHistogram [LITTLE]   [1]);
  printf ("Times with 2 little endian %d\n", occupancyHistogram [LITTLE]   [2]);
  printf ("Times with 3 little endian %d\n", occupancyHistogram [LITTLE]   [3]);
  printf ("Times with 1 big endian    %d\n", occupancyHistogram [BIG] [1]);
  printf ("Times with 2 big endian    %d\n", occupancyHistogram [BIG] [2]);
  printf ("Times with 3 big endian    %d\n", occupancyHistogram [BIG] [3]);
  printf ("Waiting Histogram\n");
  for (int i=0; i<WAITING_HISTOGRAM_SIZE; i++)
    if (waitingHistogram [i])
      printf ("  Number of times people waited for %d %s to enter: %d\n", i, i==1?"person":"people", waitingHistogram [i]);
  if (waitingHistogramOverflow)
    printf ("  Number of times people waited more than %d entries: %d\n", WAITING_HISTOGRAM_SIZE, waitingHistogramOverflow);
}
