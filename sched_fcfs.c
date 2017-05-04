#include "sched.h"

/*
pick_next_task() se invocará cuando se deba escoger una nueva tarea para ejecutar
en la CPU. Seleccionará una tarea de la run queue, la eliminará de la run queue y
devolverá dicha tarea. Es la función que realmente lleva a cabo la política de
planificación deseada.
*/
static task_t* pick_next_task_fcfs(runqueue_t* rq,int cpu)
{

	// Obtenemos la tarea de la primera que esta para ser procesada en la lista.
	// Toda run_queue tiene una task_list.
	task_t* t = head_slist(&rq->tasks);

	// Si hay una tarea encolada, la sacamos de la run_queue y la devolvemos.
	if (t) remove_slist(&rq->tasks,t);

	return t;

}

/*
enqueue_task() se invocará cada vez que debamos encolar una tarea en la run queue
de una CPU, bien porque acaba de crearse, porque sale de un bloqueo o porque se ha
migrado desde otra run queue.
*/
static void enqueue_task_fcfs(task_t* t,int cpu, int runnable)
{

	// Obtenemos la runqueue de una determinada CPU.
	runqueue_t* rq = get_runqueue_cpu(cpu);

	// Cada run queue tiene su propia idle_task que tomará la CPU cuando no haya
	// ninguna tarea runnable, esto es, en disposición de ejecutarse.

	// Si la tarea ya esta en la run_queue o no hay tareas en disposición
	// de ejecutarse acabamos.
	if(t->on_rq || is_idle_task(t)) return;

	// Si la tarea no esta encolada en la run_queue de la cpu especificada,
	// encolamos dicha tarea.
	insert_slist(&rq->tasks,t);

}

/*
steal_task() se invocará cuando se lleve a cabo una migración que exija robar una
tarea de la run queue rq. La tarea escogida se sacará de la run queue y se devolverá como
argumento de salida de la función.
 */
static task_t* steal_task_fcfs(runqueue_t* rq,int cpu)
{

	// Devuelve el último elemento de la lista (pero no lo saca de ella).
	task_t* t = tail_slist(&rq->tasks);

	// Removemos de la run_queue la tarea especificada.
	if(t) remove_slist(&rq->tasks,t);

	return t;

}

sched_class_t fcfs_sched= {
  .pick_next_task=pick_next_task_fcfs,
  .enqueue_task=enqueue_task_fcfs,
  .steal_task=steal_task_fcfs
};
