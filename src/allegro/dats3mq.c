/*  _______         ____    __         ___    ___
 * \    _  \       \    /  \  /       \   \  /   /       '   '  '
 *  |  | \  \       |  |    ||         |   \/   |         .      .
 *  |  |  |  |      |  |    ||         ||\  /|  |
 *  |  |  |  |      |  |    ||         || \/ |  |         '  '  '
 *  |  |  |  |      |  |    ||         ||    |  |         .      .
 *  |  |_/  /        \  \__//          ||    |  |
 * /_______/ynamic    \____/niversal  /__\  /____\usic   /|  .  . ibliotheque
 *                                                      /  \
 *                                                     / .  \
 * dats3mq.c - Integration of S3M files with          / / \  \
 *             Allegro's datafiles.                  | <  /   \_
 *                                                   |  \/ /\   /
 * By entheh.                                         \_  /  > /
 *                                                      | \ / /
 *                                                      |  ' /
 *                                                       \__/
 */

#include <allegro.h>

#include "aldumb-classic.h"
#include "internal/aldumb-classic.h"



static void *dat_read_s3m_quick(PACKFILE *f, long size)
{
	DUMBFILE *df;
	DUH *duh;

	(void)size;

	df = dumbfile_open_packfile(f);

	if (!df)
		return NULL;

	duh = dumb_read_s3m_quick(df);

	dumbfile_close(df);

	return duh;
}



/* dumb_register_dat_s3m_quick(): tells Allegro about the S3M datafile object.
 * If you intend to load a datafile containing an S3M object, you must call this
 * function first. It is recommended you pass DUMB_DAT_S3M, but you may have
 * a reason to use a different type (perhaps you already have a datafile with
 * S3M files in and they use a different type).
 *
 * This installs the quick loader: the song length and fast seek points are
 * not calculated.
 */
void dumb_register_dat_s3m_quick(long type)
{
	register_datafile_object(
		type,
		&dat_read_s3m_quick,
		&_dat_unload_duh
	);
}
