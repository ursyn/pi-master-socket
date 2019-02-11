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
#include "Task_pi.h"
#include "MW.h"

/* init */
Task_pi::Task_pi()
{
	size = 0;
	total = 0;
	hits = 0;
	pi = 0;
}

/* init too */
Task_pi::Task_pi(long size)
{
	this->size = size;
    total = 0;
	hits = 0;
	pi = 0;
    printself(30);
}

/* destruction */
Task_pi::~Task_pi() {
}

/* print the task to stdout */
void
Task_pi::printself( int level )
{
	MWprintf ( level, "size=%ld, total=%ld, hits=%ld, pi=%f\n", size, total, hits, pi);
}

/* The driver packs the input data via RMC, the data which will be sent to a worker. */
void Task_pi::pack_work( void )
{
	RMC->pack(&size, 1, 1);
	RMC->pack(&total, 1, 1);
	RMC->pack(&hits, 1, 1);
	RMC->pack(&pi, 1, 1);
}

/* The worker unpacks input data via RMC, need to allocate space for data */
void Task_pi::unpack_work( void )
{
	RMC->unpack(&size, 1, 1);
	RMC->unpack(&total, 1, 1);
	RMC->unpack(&hits, 1, 1);
	RMC->unpack(&pi, 1, 1);
}

/* The worker packs result data via RMC, the result will be sent back to driver */
void Task_pi::pack_results( void )
{
	RMC->pack(&size, 1, 1);
	RMC->pack(&total, 1, 1);
	RMC->pack(&hits, 1, 1);
	RMC->pack(&pi, 1, 1);
}

/* The driver unpacks result data via RMC */
void Task_pi::unpack_results( void )
{
	RMC->unpack(&size, 1, 1);
	RMC->unpack(&total, 1, 1);
	RMC->unpack(&hits, 1, 1);
	RMC->unpack(&pi, 1, 1);
}

/* write checkpoint info per task, for each task haven't been finished */
void Task_pi::write_ckpt_info( FILE *fp )
{
    fprintf(fp, "%ld %ld %ld %f", size, total, hits, pi);
}

/* Read checkpoint info, in the order written into the file */
void Task_pi::read_ckpt_info( FILE *fp )
{
    fscanf(fp, "%ld %ld %ld %f", &size, &total, &hits, &pi);
}
