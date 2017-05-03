#include "sched.h"

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

static void enqueue_task_prio(task_t* t,int cpu, int runnable)
{
  runqueue_t* rq=get_runqueue_cpu(cpu);

	if (t->on_rq || is_idle_task(t))
		return;

  /* Complete here  */

}

static task_t* steal_task_prio(runqueue_t* rq,int cpu)
{
  task_t* t=tail_slist(&rq->tasks);

  if (t) {
    remove_slist(&rq->tasks,t);

    /* Complete here  */

  }

  return t;
}

static int compare_tasks_cpu_xxx(void *t1,void *t2)
{
	task_t* tsk1=(task_t*)t1;
	task_t* tsk2=(task_t*)t2;
	return   /* Complete here  */
}

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
