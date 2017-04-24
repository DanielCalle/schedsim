#include "sched.h"

static task_t* pick_next_task_fcfs(runqueue_t* rq,int cpu)
{

}

static void enqueue_task_fcfs(task_t* t,int cpu, int runnable)
{

}

static void task_tick_fcfs(runqueue_t* rq,int cpu)
{

}

static task_t* steal_task_fcfs(runqueue_t* rq,int cpu)
{

}

sched_class_t sjf_sched= {
  .pick_next_task=pick_next_task_fcfs,
  .enqueue_task=enqueue_task_fcfs,
  .task_tick=task_tick_fcfs,
  .steal_task=steal_task_fcfs
};
