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
/* These methods will be implemented to reflect the application behavior */

#include "MW.h"
#include "Driver_pi.h"
#include "Worker_pi.h"
#include "Task_pi.h"
#include <unistd.h>

/* initialization */
Driver_pi::Driver_pi()
{
	/* For statically generated tasks, you can decide how many tasks
	 * you want to use based on the input information. However, you can
	 * also dynamically generate tasks (either when init, or when
	 * acr_on_completed_task, and add them to TODO queue by pushTask. */
	num_tasks = 0;
	job_size = 0;
	pi = 0;
}

/* destruction */
Driver_pi::~Driver_pi()
{

}

/* Here the application can (1) get per-run information from stdin (the input
 * file redirected by Condor), or (2) get configuration info from user-defined
 * config file; or (3) just hard-code your config here. The app should tell MW
 * (or RMC the Resource Manager and Communicator, which is a class member)
 * some basic info by calling the functions below:
 * (a) RMC->set_num_exec_classes()      num of different processes you have
 * (b) RMC->set_num_arch_classes() 	num of different platforms you have
 * (c) RMC->set_arch_class_attributes()  	for each platform
 * (d) RMC->add_executable() 	for combination of exec_class, arch_class;
 * (e) set_checkpoint_freqency(), ... and other information.  */

MWReturn Driver_pi::get_userinfo( int argc, char *argv[] )
{
	int i, j;
	int num_exec = 0;
	int num_arch = 0;
	char exec[_POSIX_PATH_MAX];

	MWprintf(30, "Enter Driver_pi::get_userinfo\n");
	for ( i=0; i<argc; i++ ) {
		MWprintf( 70, "arg %d: %s\n", i, argv[i] );
	}

	/* exec classes */
	RMC->set_num_exec_classes(1);

	/* arch classes */
	scanf ("%d", &num_arch);
	RMC->set_num_arch_classes(num_arch);
	MWprintf( 10, "Set the arch class to %d.\n", num_arch);

	/* Should have a better way to read attributes and set_arch_class_attributes */
	for ( i=0; i<num_arch; i++) {
		if (i==0)
			RMC->set_arch_class_attributes (0, "((Arch==\"x86_64\") && (Opsys==\"LINUX\"))");
		else RMC->set_arch_class_attributes (1, "((Arch==\"INTEL\") && (Opsys==\"SOLARIS26\"))");
	}

	/* executables */
	scanf ("%d", &num_exec);
	RMC->set_num_executables(num_exec);
	for ( i=0; i<num_exec; i++) {
		scanf("%s %d", exec, &j);
		MWprintf( 30, " %s\n", exec);
		RMC->add_executable(0, j, exec, "");
	}

	/* checkpoint requirement */
	set_checkpoint_frequency (10);

	/* Now there are application specific configurations.
	 * Please replace them with the application logic !! */
	scanf( "%ld", &job_size);
	scanf( "%d", &num_tasks);

	if (job_size <= 0) {
		MWprintf(10, "The job size is let 0, so I quit\n");
		return QUIT;
	}
	if (num_tasks <= 0) {
		MWprintf(10, "The task number is le 0, so I quit\n");
		return QUIT;
	}

	RMC->set_target_num_workers(num_tasks);
	MWprintf(30, "Patitioned into %d tasks\n", num_tasks);

	MWprintf(30, "Leave Driver_pi::get_userinfo\n");
	return OK;
}

/* setup (generate and push) the first batch of tasks in the beginning */
MWReturn Driver_pi::setup_initial_tasks(int *n_init , MWTask ***init_tasks)
{
	int i;

	*n_init = num_tasks;
    *init_tasks = new MWTask *[num_tasks];

	for ( i=0; i<num_tasks; i++) {
    		(*init_tasks)[i] = new Task_pi(job_size/num_tasks);
	}

	return OK;
}

/* Implement application behavior to process a just completed task */
MWReturn Driver_pi::act_on_completed_task( MWTask *t )
{
#ifdef NO_DYN_CAST
	Task_pi *tf = (Task_pi*) t;
#else
	Task_pi *tf = dynamic_cast<Task_pi *> (t);
#endif

	pi+= (tf->pi)/num_tasks;

	MWprintf(30, "Driver_pi::act_on_completed_task: total pi = %f\n", this->pi);
	MWprintf(30, "Driver_pi::act_on_completed_task: task pi = %f\n", tf->pi);

	return OK;
}

/* The first batch of data for a newly spawned worker, e.g. init data */
MWReturn Driver_pi::pack_worker_init_data( void )
{
	/* Nothing for this application */
	return OK;
}

/* Print out the result when MW is done. MW assume that the application
 * is keeping track of the results :-) */
void Driver_pi::printresults()
{
	MWprintf ( 10, "The pi number is %f.\n", this->pi);
}

/* Write app-specific master checkpoint info */
void
Driver_pi::write_master_state( FILE *fp )
{
	fprintf(fp, "%f", pi);
}

/* Read app-specific master checkpoint info */
void
Driver_pi::read_master_state( FILE *fp )
{
	fscanf(fp, "%f", &pi);
}

/* Return a new application task object */
MWTask*
Driver_pi::gimme_a_task()
{
    return new Task_pi;
}

/* Return a new driver object */
MWDriver* gimme_the_master()
{
	return new Driver_pi;
}
