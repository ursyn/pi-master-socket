/***************************Copyright-DO-NOT-REMOVE-THIS-LINE**
  *
  * Condor Software Copyright Notice
  * Copyright (C) 1990-2004, Condor Team, Computer Sciences Department,
  * University of Wisconsin-Madison, WI.
  *
  * This source code is covered by the Condor Public License, which can
  * be found in the accompanying LICENSE.TXT file, or online at
  * www.condorproject.org.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  * AND THE UNIVERSITY OF WISCONSIN-MADISON "AS IS" AND ANY EXPRESS OR
  * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  * WARRANTIES OF MERCHANTABILITY, OF SATISFACTORY QUALITY, AND FITNESS
  * FOR A PARTICULAR PURPOSE OR USE ARE DISCLAIMED. THE COPYRIGHT
  * HOLDERS AND CONTRIBUTORS AND THE UNIVERSITY OF WISCONSIN-MADISON
  * MAKE NO MAKE NO REPRESENTATION THAT THE SOFTWARE, MODIFICATIONS,
  * ENHANCEMENTS OR DERIVATIVE WORKS THEREOF, WILL NOT INFRINGE ANY
  * PATENT, COPYRIGHT, TRADEMARK, TRADE SECRET OR OTHER PROPRIETARY
  * RIGHT.
  *
  ****************************Copyright-DO-NOT-REMOVE-THIS-LINE**/
#include "Worker_pi.h"
#include "Task_pi.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* init */
Worker_pi::Worker_pi()
{
    workingTask = new Task_pi;
}

/* destruct */
Worker_pi::~Worker_pi()
{
    delete workingTask;
}

/* Do benchmark and return result (usually the time to task t), t is supposed
 * to be a benchmark task.  In this app, it just send back a PI. */
double
Worker_pi::benchmark( MWTask *t )
{
        Task_pi *tl = dynamic_cast<Task_pi *> ( t );
        tl->printself(30);
        return 3.14159;
}

/* unpack the init data from the driver */
MWReturn Worker_pi::unpack_init_data( void )
{
	/* As we don'e have init data, we do nothing */
	return OK;
}

/* Execute each task */
void Worker_pi::execute_task( MWTask *t )
{
	int i;

	MWprintf(30, "Enter Worker_pi::execute_task\n");
#ifdef NO_DYN_CAST
	Task_pi *tl = (Task_pi *) t;
#else
    	Task_pi *tl = dynamic_cast<Task_pi *> ( t );
#endif

	MWprintf(30, "\tWorking on task...: \n");

	/* the real work :-) */

	for (;(tl->total) < (tl->size); (tl->total)++) {
		float x = (float)rand()/(float)(RAND_MAX);
		float y = (float)rand()/(float)(RAND_MAX);
		if ((x*x)+(y*y) <= 1) {
			(tl->hits)++;
		}
	}
	tl->pi = ((float)tl->hits / tl->size) * 4;

	MWprintf(30, "Leave Worker_pi::execute_task, total generations = %ld\n", (tl->total));
	MWprintf(30, "Leave Worker_pi::execute_task, hits = %ld\n", tl->hits);
	MWprintf(30, "Leave Worker_pi::execute_task, pi = %f\n", tl->pi);
}

MWTask* Worker_pi::gimme_a_task()
{
	return new Task_pi;
}

/* Just return a newly created application worker object */
MWWorker*
gimme_a_worker ()
{
       	return new Worker_pi;
}
