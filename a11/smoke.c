#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"

#define NUM_ITERATIONS 1000

#ifdef VERBOSE
#define VERBOSE_PRINT(S, ...) printf (S, ##__VA_ARGS__);
#else
#define VERBOSE_PRINT(S, ...) ;
#endif

struct Agent {
    uthread_mutex_t mutex;
    uthread_cond_t match;
    uthread_cond_t paper;
    uthread_cond_t tobacco;
    uthread_cond_t smoke;
};

struct Agent *createAgent() {
    struct Agent *agent = malloc(sizeof(struct Agent));
    agent->mutex = uthread_mutex_create();
    agent->paper = uthread_cond_create(agent->mutex);
    agent->match = uthread_cond_create(agent->mutex);
    agent->tobacco = uthread_cond_create(agent->mutex);
    agent->smoke = uthread_cond_create(agent->mutex);
    return agent;
}

struct Smoker {
    struct Agent *ag;
    int hasTobacco;
    int hasPaper;
    int hasMatch;
	int hasSmoked;
	int update_count;
	uthread_cond_t distributed;
	uthread_mutex_t smoke_mutex;
};

struct Smoker *createSmoker(struct Agent *a) {
    struct Smoker *smoker = malloc(sizeof(struct Smoker));
    smoker->ag = a;
    smoker->hasTobacco = 0;
    smoker->hasMatch = 0;
    smoker->hasPaper = 0;
	smoker->hasSmoked = 0;
	smoker->update_count = 0;
	smoker->distributed = uthread_cond_create(smoker->ag->mutex);
	smoker->smoke_mutex = uthread_mutex_create();
    return smoker;
}

void* t_update(void *av) {
    //printf("+ update tobacco\n");
    struct Smoker *a = av;
    uthread_mutex_lock(a->ag->mutex);
    //printf("+ Tobacco mutex locked\n");
    while(1) {
		//printf("+ Waiting for tobacco signal.\n");
        uthread_cond_wait(a->ag->tobacco);
        //printf("+ Tobacco signal received.\n");
        a->hasTobacco = 1;
		a->update_count++;
		if (a->update_count == 2) {
			//printf("+ Signal all distributed\n");
			a->hasSmoked = 0;
			uthread_cond_broadcast (a->distributed);
		}
    }
    uthread_mutex_unlock(a->ag->mutex);
}

void* p_update(void *av) {
	//printf("+ update paper\n");
    struct Smoker *a = av;
    uthread_mutex_lock(a->ag->mutex);
	//printf("+ Paper mutex locked\n");
    while(1) {
		//printf("+ Waiting for paper signal.\n");
        uthread_cond_wait(a->ag->paper);
		//printf("+ Paper signal received.\n");
        a->hasPaper = 1;
		a->update_count++;
		if (a->update_count == 2) {
			//printf("+ Signal all distributed\n");
			a->hasSmoked = 0;
			uthread_cond_broadcast (a->distributed);
		}
    }
    uthread_mutex_unlock(a->ag->mutex);
}

void* m_update(void *av) {
	//printf("+ update match\n");
    struct Smoker *a = av;
    uthread_mutex_lock(a->ag->mutex);
	//printf("+ Match mutex locked\n");
    while(1) {
		//printf("+ Waiting for match signal.\n");
        uthread_cond_wait(a->ag->match);
		//printf("+ Match signal received.\n");
        a->hasMatch = 1;
		a->update_count++;
		if (a->update_count == 2) {
			//printf("+ Signal all distributeD\n");
			a->hasSmoked = 0;
			uthread_cond_broadcast (a->distributed);
		}
    }
    uthread_mutex_unlock(a->ag->mutex);
}



//
// TODO
// You will probably need to add some procedures and struct etc.
//

/**
 * You might find these declarations helpful.
 *   Note that Resource enum had values 1, 2 and 4 so you can combine resources;
 *   e.g., having a MATCH and PAPER is the value MATCH | PAPER == 1 | 2 == 3
 */
enum Resource {
    MATCH = 1, PAPER = 2, TOBACCO = 4
};
char *resource_name[] = {"", "match", "paper", "", "tobacco"};

int signal_count[5];  // # of times resource signalled
int smoke_count[5];  // # of times smoker with resource smoked

/**
 * This is the agent procedure.  It is complete and you shouldn't change it in
 * any material way.  You can re-write it if you like, but be sure that all it does
 * is choose 2 random reasources, signal their condition variables, and then wait
 * wait for a smoker to smoke.
 */
void *agent(void *av) {
    struct Agent *a = av;
    static const int choices[] = {MATCH | PAPER, MATCH | TOBACCO, PAPER | TOBACCO};
    static const int matching_smoker[] = {TOBACCO, PAPER, MATCH};

    //printf("agent\n");
    uthread_mutex_lock(a->mutex);
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        int r = random() % 3;
        signal_count[matching_smoker[r]]++;
        int c = choices[r];
        if (c & MATCH) { VERBOSE_PRINT ("match available\n");
			//printf("signal match available\n");
            uthread_cond_signal(a->match);
        }
        if (c & PAPER) { VERBOSE_PRINT ("paper available\n");
			//printf("signal paper available\n");
            uthread_cond_signal(a->paper);
        }
        if (c & TOBACCO) { VERBOSE_PRINT ("tobacco available\n");
			//printf("signal tobacco available\n");
            uthread_cond_signal(a->tobacco);
        }VERBOSE_PRINT ("agent is waiting for smoker to smoke\n");
		
		//printf("waiting for smoker to smoke\n");
        uthread_cond_wait(a->smoke);
		//printf("received smoke signal\n");
    }
    uthread_mutex_unlock(a->mutex);
    return NULL;
}

void* t_smoke(void *av) {
    struct Smoker *a = av;
    //printf("_ start smoke\n");
    uthread_mutex_lock(a->ag->mutex);
    while(1) {
		//printf("_ tobacco waiting for all distributed signal.\n");
		uthread_cond_wait(a->distributed);
		//printf("_ received all distributed signal.\n");
		uthread_mutex_lock (a->smoke_mutex);
		if (a->hasSmoked == 0) {
			if (a->hasTobacco == 0){ // if tobacco not distributed, then paper and match must get distributed
				a->hasSmoked = 1;
				a->hasMatch = 0; // set resources back to empty
				a->hasPaper = 0;
				a->update_count = 0;
			
				VERBOSE_PRINT ("smoker with tobacco now smoke\n");
				smoke_count [TOBACCO] ++;
				uthread_cond_signal (a->ag->smoke);
			
				//printf("_ tobacco signal smoke\n");
			}
		}
		uthread_mutex_unlock (a->smoke_mutex);
		
    }
    uthread_mutex_unlock(a->ag->mutex);
}
void* p_smoke(void *av) {
    struct Smoker *a = av;
    //printf("_ start smoke\n");
    uthread_mutex_lock(a->ag->mutex);
    while(1) {
		//printf("_ paper waiting for all distributed signal.\n");
		uthread_cond_wait(a->distributed);
		//printf("_ received all distributed signal.\n");
		uthread_mutex_lock (a->smoke_mutex);
		if (a->hasSmoked == 0) {
			if (a->hasPaper == 0) { // if paper not distributed, then tobacco and match must get distributed
				a->hasSmoked = 1;
				a->hasMatch = 0; // set resources back to empty
				a->hasTobacco = 0;
				a->update_count = 0;
				
				VERBOSE_PRINT ("smoker with paper now smoke\n");
				smoke_count [PAPER] ++;
				uthread_cond_signal (a->ag->smoke);
				
				//printf("_ paper signal smoke\n");
			}
		}
		uthread_mutex_unlock (a->smoke_mutex);
		
    }
    uthread_mutex_unlock(a->ag->mutex);
}
void* m_smoke(void *av) {
    struct Smoker *a = av;
    //printf("_ start smoke\n");
    uthread_mutex_lock(a->ag->mutex);
    while(1) {
		//printf("_ match waiting for all distributed signal.\n");
		uthread_cond_wait(a->distributed);
		//printf("_ received all distributed signal.\n");
		uthread_mutex_lock (a->smoke_mutex);
		if (a->hasSmoked == 0) {
			if (a->hasMatch == 0){ // if match not distributed, then paper and tobacco must get distributed
				a->hasSmoked = 1;
				a->hasTobacco = 0; // set resources back to empty
				a->hasPaper = 0;
				a->update_count = 0;
				
				VERBOSE_PRINT ("smoker with match now smoke\n");
				smoke_count [MATCH] ++;
				uthread_cond_signal (a->ag->smoke);
				
				//printf("_ match signal smoke\n");
			}
		}
		uthread_mutex_unlock (a->smoke_mutex);
    }
    uthread_mutex_unlock(a->ag->mutex);
}

int main(int argc, char **argv) {
    uthread_init(7);
    struct Agent *a = createAgent();
    struct Smoker * s = createSmoker(a);
    uthread_create(t_update,s);
    uthread_create(p_update,s);
    uthread_create(m_update,s);
    uthread_create(t_smoke,s);
	uthread_create(p_smoke,s);
	uthread_create(m_smoke,s);
    uthread_join(uthread_create(agent, a), 0);
    assert(signal_count[MATCH] == smoke_count[MATCH]);
    assert(signal_count[PAPER] == smoke_count[PAPER]);
    assert(signal_count[TOBACCO] == smoke_count[TOBACCO]);
    assert(smoke_count[MATCH] + smoke_count[PAPER] + smoke_count[TOBACCO] == NUM_ITERATIONS);
    printf("Smoke counts: %d matches, %d paper, %d tobacco\n",
           smoke_count[MATCH], smoke_count[PAPER], smoke_count[TOBACCO]);
}