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
#ifndef _pi_TASK_H
#define _pi_TASK_H

#include <stdio.h>
#include "MWTask.h"

class Task_pi : public MWTask
{
public:
	/* constructors */
    Task_pi();
    Task_pi(long size);

	/* destructor */
    ~Task_pi();

	/* App is required to implement the following functions. */
    void pack_work( void );
    void unpack_work( void );
    void pack_results( void );
    void unpack_results( void );

	/* The following functions have default implementation. */
	void printself( int level = 70 );
    void write_ckpt_info( FILE *fp );
    void read_ckpt_info( FILE *fp );

    /* The application specific information goes here */
    long size;     /* How many pi generations */
    long total;    /* How many generated */
	long hits;     /* How many hits inside the circle */
	float pi;      /* Pi value */
};

#endif
