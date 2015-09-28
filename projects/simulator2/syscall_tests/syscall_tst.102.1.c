/*
 * Copyright (c) Wipro Technologies Ltd, 2002.  All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write the Free Software Foundation, Inc., 59
 * Temple Place - Suite 330, Boston MA 02111-1307, USA.
 *
 */
/**************************************************************************
 *
 *    TEST IDENTIFIER	: socketcall01
 *
 *    EXECUTED BY	: All user
 *
 *    TEST TITLE	: Basic test for socketcall(2) for socket(2)
 *
 *    TEST CASE TOTAL	: 4
 *
 *    AUTHOR		: sowmya adiga<sowmya.adiga@wipro.com>
 *
 *    SIGNALS
 *	Uses SIGUSR1 to pause before test if option set.
 *	(See the parse_opts(3) man page).
 *
 *    DESCRIPTION
 *	This is a phase I test for the socketcall(2) system call.
 *	It is intended to provide a limited exposure of the system call.
 *
 *	Setup:
 *	  Setup signal handling.
 *	  Pause for SIGUSR1 if option specified.
 *
 *	Test:
 *	  Execute system call
 *	  Check return code, if system call failed (return=-1)
 *	  Log the errno and Issue a FAIL message.
 *	  Otherwise, Issue a PASS message.
 *
 *	Cleanup:
 *	  Print errno log and/or timing stats if options given
 *
 * USAGE:  <for command-line>
 *  socketcall01 [-c n] [-e] [-i n] [-I x] [-p x] [-t]
 *		where,		-c n : Run n copies concurrently
 *				-e   : Turn on errno logging.
 *				-h   : Show this help screen
 *				-i n : Execute test n times.
 *				-I x : Execute test for x seconds.
 *				-p   : Pause for SIGUSR1 before starting
 *				-P x : Pause for x seconds between iterations.
 *				 t   : Turn on syscall timing.
 *
 * RESTRICTIONS
 * None
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/net.h>
#include <sys/un.h>
#include <netinet/in.h>

#include "test.h"
#include "usctest.h"

char *TCID = "socketcall01";	/* Test program identifier.    */

#ifdef __NR_socketcall

#define socketcall(call, args) syscall(__NR_socketcall, call, args)

void setup();
void cleanup();

extern int Tst_count;		/* TestCase counter for tst_* routine */

struct test_case_t {
	int call;
	unsigned long args[3];
	char *desc;
} TC[] = {
	{
		SYS_SOCKET, {
	PF_INET, SOCK_STREAM, 0}, "TCP stream"}, {
		SYS_SOCKET, {
	PF_UNIX, SOCK_DGRAM, 0}, "unix domain dgram"}, {
		SYS_SOCKET, {
#if 0 /* Requires root euid, so skip it for ROSE. [RPM 2011-01-04] */
	AF_INET, SOCK_RAW, 6}, "Raw socket"}, {
		SYS_SOCKET, {
#endif
	PF_INET, SOCK_DGRAM, 17}, "UDP dgram"}
};

int TST_TOTAL = sizeof(TC) / sizeof(TC[0]);

int main(int ac, char **av)
{
	int lc;			/* loop counter */
	char *msg;		/* message returned from parse_opts */
	int i;			/* s is socket descriptor */

	if ((msg = parse_opts(ac, av, NULL, NULL)) != (char *)NULL) {
		tst_brkm(TBROK, NULL, "OPTION PARSING ERROR - %s", msg);
		tst_exit();
	}

	/* perform global setup for test */
	setup();

	/* check looping state */
	for (lc = 0; TEST_LOOPING(lc); lc++) {

		/* reset Tst_count in case we are looping. */
		Tst_count = 0;

		for (i = 0; i < TST_TOTAL; i++) {

			TEST(socketcall(TC[i].call, TC[i].args));

			/* check return code */
			if (TEST_RETURN == -1) {
				tst_resm(TFAIL|TTERRNO, "socketcall() Failed with"
					 " return=%ld",
					 TEST_RETURN);
                                exit(1);
			} else {
				tst_resm(TPASS, "socketcall() passed for"
					 " :%s with return=%ld ",
					 TC[i].desc, TEST_RETURN);
				close(TEST_RETURN);
			}
		}		/* End for TEST_LOOPING */
	}

	/* cleanup and exit */
	cleanup();

	return 0;
}				/* End main */

/* setup() - performs all ONE TIME setup for this test. */
void setup()
{

	/* capture signals */
	tst_sig(NOFORK, DEF_HANDLER, cleanup);

	/* pause if that option was specified */
	TEST_PAUSE;
}

/*
 * cleanup() - performs all ONE TIME cleanup for this test at
 *		completion or premature exit.
 */
void cleanup()
{
	TEST_CLEANUP;

	/* exit with return code appropriate for results */
	tst_exit();
}

#else

int TST_TOTAL = 0;		/* Total number of test cases. */

int main()
{
	tst_resm(TPASS, "socket call test on this architecture disabled.");
	tst_exit();
	return 0;
}

#endif
