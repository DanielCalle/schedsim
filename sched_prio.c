#include "sched.h"

//this function chooses the most appropriate task eligible to run next.
//Note, that this is not the same as enqueuing and dequeuing tasks
static task_t* pick_next_task_prio(runqueue_t* rq,int cpu)
{
  task_t* t=head_slist(&rq->tasks);

	/* Current is not on the rq -> let's remove it */
	if (t) {
		remove_slist(&rq->tasks,t);
    /* Complete here  */

  }

	return t;
}

/*
Called when a task enters a runnable state.
It puts the scheduling entity (task) into the run queue and
increments the nr_running (number of runnable processes in
a run queue) variable;
*/
static void enqueue_task_prio(task_t* t,int cpu, int runnable)
{
  runqueue_t* rq=get_runqueue_cpu(cpu);

	if (t->on_rq || is_idle_task(t))
		return;


  if (t->flags & TF_INSERT_FRONT) {
  	//Clear flag
    t->flags&=~TF_INSERT_FRONT;
    sorted_insert_slist_front(&rq->tasks, t, 1, compare_tasks_cpu_prio);  //Push task
  } else
    sorted_insert_slist(&rq->tasks, t, 1, compare_tasks_cpu_prio);  //Push task

  t->on_rq=TRUE
  rq->nr_runnable++;

  /* Complete here  */

}

static task_t* steal_task_prio(runqueue_t* rq,int cpu)
{
  task_t* t=tail_slist(&rq->tasks);

  if (t) {
    remove_slist(&rq->tasks,t);
    t->on_rq=FALSE
    rq->nr_runnable--;
  }

  return t;
}

static int compare_tasks_cpu_xxx(void *t1,void *t2)
{
	task_t* tsk1=(task_t*)t1;
	task_t* tsk2=(task_t*)t2;
	return  tsk1->prio-tsk2->prio;
}

/*
Mostly called from time tick functions;
it mi ght lead to process switch.
Thi s drives the running preemption;
*/
static void task_tick_prio(runqueue_t* rq,int cpu)
{
	task_t* current=rq->cur_task;

	if (is_idle_task(current))
		return;

  /* Complete here */

}

sched_class_t sjf_sched= {
  .pick_next_task=pick_next_task_prio,
  .enqueue_task=enqueue_task_prio,
  .steal_task=steal_task_prio
  .task_tick=task_tick_prio,
};
