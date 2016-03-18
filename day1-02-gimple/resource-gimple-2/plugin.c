/*-----------------------------------------------------------------------------
 *  "gcc-plugin.h" must be the FIRST file to be included 
 *-----------------------------------------------------------------------------*/
#include "gcc-plugin.h"
#include "config.h"
#include <stdio.h>
#include "system.h"
#include "coretypes.h"
#include "tm.h"
//#include "tm_p.h"
#include "diagnostic.h"
#include "gimple-pretty-print.h"
#include "tree-flow.h"
#include "tree-pass.h"
#include "toplev.h"
#include "gimple.h"

/*-----------------------------------------------------------------------------
 *  Each plugin MUST define this global int to assert compatibility with GPL; 
 *  else the compiler throws a fatal error 
 *-----------------------------------------------------------------------------*/
int plugin_is_GPL_compatible;

/*function declarations*/
static unsigned int gimple_analysis (void);
static void restore_cfg (void);

basic_block cbb;

/*-----------------------------------------------------------------------------
 *  Structure of the pass we want to insert, identical to a regular ipa pass
 *-----------------------------------------------------------------------------*/

struct simple_ipa_opt_pass pass_plugin = 
{
  {
    SIMPLE_IPA_PASS,
    "gimple-split",                          /*  name */
    NULL,                                 /*  gate */
    gimple_analysis,                      /*  execute */
    NULL,                                 /*  sub */
    NULL,                                 /*  next */
    0,                                    /*  static pass number */
    TV_INTEGRATION,                        /*  tv_id */
    0,                                    /*  properties required */
    0,                                    /*  properties provided */
    0,                                    /*  properties destroyed */
    0,                                    /*  todo_flags start */
    0                                     /*  todo_flags end */
  }
};

/*-----------------------------------------------------------------------------
 *  This structure provides the information about inserting the pass in the
 *  pass manager. 
 *-----------------------------------------------------------------------------*/
struct register_pass_info pass_info = {
  &(pass_plugin.pass),                  /* Address of new pass, here, the 'struct
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
        &pass_info);                /* plugin specific data */

        return 0;
}

/* Execute function */
static unsigned int 
gimple_analysis (void){

   /* Preserve the context before function execution. */
   struct function *old_cfun = cfun;
   tree old_cfundecl = current_function_decl;

   gimple_stmt_iterator gsi;
   struct cgraph_node *node;

    /* Iterating over each basic block of a function */
   for (node = cgraph_nodes; node; node = node->next){

        /* Nodes without a body, and clone nodes are not interesting. */
        if (!gimple_has_body_p (node->decl) || node->clone_of)
                   continue;

        set_cfun (DECL_STRUCT_FUNCTION (node->decl));
        current_function_decl = node->decl;

        fprintf (dump_file,"\n\n------ Function : %s ------\n",cgraph_node_name(node));
        /* Iterating over each basic block of a function */
        FOR_EACH_BB (cbb){

            /*Iterating over each gimple statement in a basic block*/
            for (gsi = gsi_start_bb(cbb); !gsi_end_p(gsi); gsi_next (&gsi)){
	     
		/* Enter your code here */		

 	    }
        }

        if (dump_file) 
           gimple_dump_cfg (dump_file, dump_flags);
    }

   restore_cfg();

   /* Restore the context after function finishes. */
   current_function_decl = old_cfundecl;
   set_cfun (old_cfun);

   return 0;
}

/* ----------------------------------------------------------------
   Restoring the cfg by clearing the aux field of each basic block
   and removing unnecessary (split) blocks.
   ---------------------------------------------------------------*/
static void
restore_cfg (void)
{
   struct cgraph_node *cnode;
   basic_block cbb;   
   for (cnode = cgraph_nodes; cnode; cnode = cnode->next) {
       if (!gimple_has_body_p (cnode->decl) || cnode->clone_of)
           continue;
       current_function_decl = cnode->decl;
       set_cfun (DECL_STRUCT_FUNCTION (cnode->decl));
       /* Free cgraph node's aux field. */
       if (cnode->aux) {
           ggc_free (cnode->aux);
           cnode->aux = NULL;
       }
       /* Free each bb's aux field. */
       FOR_EACH_BB (cbb) {
           if (cbb->aux) {
               ggc_free (cbb->aux);
               cbb->aux = NULL;
           }
       }
       /* Merge bb's if necessary. */
       cleanup_tree_cfg ();
       /* Free the dominator info. */
       free_dominance_info (CDI_DOMINATORS);
       free_dominance_info (CDI_POST_DOMINATORS);
   }
}


