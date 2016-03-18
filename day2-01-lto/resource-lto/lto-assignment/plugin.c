/*-----------------------------------------------------------------------------
 *  "gcc-plugin.h" must be the FIRST file to be included 
 *-----------------------------------------------------------------------------*/
#include "gcc-plugin.h"
#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "diagnostic.h"
#include "tree-flow.h"
#include "tree-pass.h"
#include "toplev.h"

/*-----------------------------------------------------------------------------
 *  Each plugin MUST define this global int to assert compatibility with GPL; 
 *  else the compiler throws a fatal error 
 *-----------------------------------------------------------------------------*/
int plugin_is_GPL_compatible;

extern void print_gimple_stmt (FILE *file, gimple g, int spc, int flags);

/* ------------------------------------------------
 *   The main driver function to perform analysis.
 * ------------------------------------------------*/

static unsigned int execute_gimple_manipulation (void)
{
	struct cgraph_node *node;
        basic_block bb;
        gimple stmt;
        gimple_stmt_iterator gsi;

	if (!dump_file)
		return 1;

	/* Iterating over all the functions */
	for (node = cgraph_nodes; node; node = node->next)
	{
		/* Nodes without a body, and clone nodes are not interesting. */
		if (!gimple_has_body_p (node->decl) || node->clone_of)
			continue;

		/* Print the name of function if function body is available */
		fprintf (dump_file, "----------Function : %s body loaded ---------\n",cgraph_node_name(node));


	}
	return 0;
}

/* ---------------------------------------------
 *  Structure of the pass we want to insert.
 * ---------------------------------------------*/

/* A pass structure for a plugin to dump gimple statements after pta pass */

struct simple_ipa_opt_pass pass_gimple_stmts1 =
{
  {
   SIMPLE_IPA_PASS,
   "dump-fns-after-pta",         /* name */
   NULL,     			 /* gate */
   execute_gimple_manipulation,  /* execute */
   NULL,                         /* sub */
   NULL,                         /* next */
   0,                            /* static pass number */
   TV_INTEGRATION,               /* tv_id */
   0,                            /* properties required */
   0,                            /* properties provided */
   0,                            /* properties destroyed */
   0,                            /* todo_flags start */
   0                             /* todo_flags end */
  }
};

/* A pass structure for a plugin to dump gimple statements after inline pass */

struct ipa_opt_pass_d pass_gimple_stmts2 =
{
  {
   IPA_PASS,
   "dump-fns-after-inline",      /* name */
   NULL,     			 /* gate */
   execute_gimple_manipulation,	 /* execute */
   NULL,                         /* sub */
   NULL,                         /* next */
   0,                            /* static pass number */
   TV_INTEGRATION,               /* tv_id */
   0,                            /* properties required */
   0,                            /* properties provided */
   0,                            /* properties destroyed */
   0,                            /* todo_flags start */
   0                             /* todo_flags end */
  },
 NULL,                           /* generate_summary */
 NULL,                           /* write_summary */
 NULL,                           /* read_summary */
 NULL,                           /* write_optimization_summary */
 NULL,                           /* read_optimization_summary */
 NULL,                           /* stmt_fixup */
 0,                              /* TODOs */
 NULL,                           /* function_transform */
 NULL                            /* variable_transform */
};



/*-----------------------------------------------------------------------------
 *  This structure provides the information about inserting the pass in the
 *  pass manager. 
 *-----------------------------------------------------------------------------*/


struct register_pass_info pass_info1 = {
 &(pass_gimple_stmts1.pass),      /* Address of new pass, here, the 'struct
                                     opt_pass' field of 'gimple_opt_pass'
                                     defined above */
  "pta",                          /* Name of the reference pass for hooking up
                                     the new pass.   ??? */
  0,                              /* Insert the pass at the specified instance
                                     number of the reference pass. Do it for
                                     every instance if it is 0. */
  PASS_POS_INSERT_AFTER           /* how to insert the new pass: before,
                                     after, or replace. Here we are inserting
                                     a pass names 'plug' after the pass named
                                     'pta' */
};

struct register_pass_info pass_info2 = {
  &(pass_gimple_stmts2.pass),     /* Address of new pass, here, the 'struct
                                     opt_pass' field of 'gimple_opt_pass'
                                     defined above */
  "inline",                       /* Name of the reference pass for hooking up
                                     the new pass.   ??? */
  0,                              /* Insert the pass at the specified instance
                                     number of the reference pass. Do it for
                                     every instance if it is 0. */
  PASS_POS_INSERT_AFTER           /* how to insert the new pass: before,
                                     after, or replace. Here we are inserting
                                     a pass names 'plug' after the pass named
                                     'pta' */
};



/*-----------------------------------------------------------------------------
 *  plugin_init is the first function to be called after the plugin is loaded
 *-----------------------------------------------------------------------------*/
int
plugin_init(struct plugin_name_args *plugin_info,
    struct plugin_gcc_version *version)
{

  /*-----------------------------------------------------------------------------
   * Plugins are activiated using this callback 
   *-----------------------------------------------------------------------------*/
  register_callback (
      plugin_info->base_name,     /* char *name: Plugin name, could be any
                                     name. plugin_info->base_name gives this
                                     filename */
      PLUGIN_PASS_MANAGER_SETUP,  /* int event: The event code. Here, setting
                                     up a new pass */
      NULL,                       /* The function that handles event */
      &pass_info1);                /* plugin specific data */

 register_callback (
      plugin_info->base_name,     /* char *name: Plugin name, could be any
                                     name. plugin_info->base_name gives this
                                     filename */
      PLUGIN_PASS_MANAGER_SETUP,  /* int event: The event code. Here, setting
                                     up a new pass */
      NULL,                       /* The function that handles event */
      &pass_info2);                /* plugin specific data */


  return 0;
}

