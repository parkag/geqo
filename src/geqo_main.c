/*------------------------------------------------------------------------
 *
 * geqo_main.c
 *	  setup for extracted GEQO
 *
 *
 * src/geqo_main.c
 *
 *-------------------------------------------------------------------------
 */


#include "postgres.h"

#include <limits.h>

#include "utils/guc.h"
#include "optimizer/paths.h"
#include "optimizer/geqo.h"

#include "geqo.h"


PG_MODULE_MAGIC;

/* GUC variables */
bool	enable_geqo_extension = false;


/* Saved hook value in case of unload */
static join_search_hook_type prev_join_search_hook = NULL;


static RelOptInfo *
geqo_main(PlannerInfo *root, int levels_needed, List *initial_rels)
{
	if (enable_geqo_extension)
		return geqo_extension(root, levels_needed, initial_rels);
	else if (enable_geqo_extension && levels_needed >= geqo_threshold)
		return geqo(root, levels_needed, initial_rels);
	else
		return standard_join_search(root, levels_needed, initial_rels);
}

/* Module load */
void
_PG_init(void)
{
	/* Install hook */
	prev_join_search_hook = join_search_hook;
	join_search_hook = geqo_main;


	//elog(ERROR, "im using external GEQO");
	DefineCustomBoolVariable("geqo_extension", "Use external GEQO for query planning.", NULL,
							 &enable_geqo_extension, true,
							 PGC_USERSET,
							 0, GEQO2_GUC_HOOK_VALUES);
	//load_parameters();
}

/* Module unload */
void
_PG_fini(void)
{
	/* Uninstall hook */
	join_search_hook = prev_join_search_hook;
}