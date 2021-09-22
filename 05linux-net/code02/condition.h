#ifndef CONDITION_H_
#define CONDITION_H_

struct _Condition;
typedef struct _Condition Condition;

Condition* condition_create();
void condition_destroy(Condition *thiz);

void condition_lock(Condition *thiz);
void condition_unlock(Condition *thiz);
void condition_wait(Condition *thiz);
void condition_signal(Condition *thiz);
void condition_broadcast(Condition *thiz);

#endif