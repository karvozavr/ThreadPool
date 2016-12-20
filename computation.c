#include "computation.h"

void thpool_init_computation(struct Computation *computation,
                             OnComputationComplete on_complete,
                             void *on_complete_arg
) {
    computation->computed = false;
    pthread_mutex_init(&(computation->guard), NULL);
    pthread_cond_init(&(computation->cond), NULL);
    computation->task.f = computation->f;
    computation->task.arg = computation->arg;
    computation->on_complete = on_complete;
    computation->on_complete_arg = on_complete_arg;
}

void thpool_submit_computation(
        struct ThreadPool *pool,
        struct Computation *computation,
        OnComputationComplete on_complete,
        void *on_complete_arg
) {
    thpool_init_computation(computation,
                            on_complete,
                            on_complete_arg);

    thpool_submit(pool, &computation->task);
}

void thpool_complete_computation(struct Computation *computation) {
    computation->on_complete(computation->on_complete_arg);
    pthread_mutex_lock(&computation->guard);
    computation->computed = true;
    pthread_cond_broadcast(&computation->cond);
    pthread_mutex_unlock(&computation->guard);
}

void thpool_wait_computation(struct Computation *computation) {
    pthread_mutex_lock(&computation->guard);
    while (!computation->computed) {
        pthread_cond_wait(&computation->cond, &computation->guard);
    }
    thpool_wait(&computation->task);
    pthread_mutex_unlock(&computation->guard);
    pthread_cond_destroy(&computation->cond);
    pthread_mutex_destroy(&computation->guard);
}