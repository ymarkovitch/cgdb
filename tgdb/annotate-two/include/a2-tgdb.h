#ifndef __A2_TGDB_H__
#define __A2_TGDB_H__

#if HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif /* HAVE_SYS_TYPES_H */

#include "types.h"
#include "tgdb_interface.h"

#if 0
	/* Here is a prototype of the interface planned for .4.0 
	 *
	 */

	/* annotate-two
	 * ------------
	 *
	 * This struct is a reference to a libannotate-two instance.
	 */
	 struct annotate_two;

    /* a2_create_instance
	 * ------------------
	 *
	 * This invokes a libannotate_two library instance.
	 *
	 * The client must call this function before any other function in the 
	 * tgdb library.
	 *
	 * debugger
	 * --------
     *  The path to the desired debugger to use. If this is NULL, then just
	 *  "gdb" is used.
	 *
	 * argc
	 * ----
	 *  The number of arguments to pass to the debugger
	 *
	 * argv
	 * ----
	 *  The arguments to pass to the debugger    
     *
     * debugger_stdin
     * --------------
     *  Writing writes to debugger's stdin
     *
     * debugger_fd
     * -----------
	 *  The descriptor to the debugger's I/O
     *
     * config_dir
     * ----------
     *  The current config directory. Files can be stored here.
     *
     *  Returns
     *  -------
     *      NULL on error, A valid descriptor upon success
     *
	 */
	struct annotate_two* tgdb_create_instance ( 
		const char *debugger, 
		int argc, char **argv,
		int *debugger_stdin, int *debugger_fd, const char *config_dir );

	
	/* a2_tgdb_initialize
	 * ------------------
	 *
	 *  This initializes the libannotate_two libarary.
	 *  
	 *  a2
	 *  --
	 *   The annotate two context.
	 *
	 *  inferior_tty_name
	 *  -----------------
	 *   The name of the tty to use for the inferior.
	 */
	int a2_tgdb_initialize ( struct annotate_two *a2, const char *inferior_tty_name );

	/* a2_tgdb_shutdown
	 * ----------------
	 *
	 *  Shuts down the annotate two context. No more calls can be made on the
	 *  current context.
	 *
	 *  a2
	 *  --
	 *   The annotate two context.
	 */
	int a2_tgdb_shutdown ( struct annotate_two *a2 );

	/* a2_tgdb_get_source_absolute_filename
	 * ------------------------------------
	 *
	 *  Gets the Absolute path of FILE.
	 *  
	 *  a2
	 *  --
	 *   The annotate two context.
	 *
	 *  file
	 *  ----
	 *   The relative path that gdb outputted.
	 */
	int a2_tgdb_get_source_absolute_filename ( struct annotate_two *a2, const char *file );

	/* a2_tgdb_get_sources
	 * -------------------
	 *
	 *  Gets all the source files that the inferior makes up.
	 *
	 *  a2
	 *  --
	 *   The annotate two context.
	 */
	int a2_tgdb_get_sources ( struct annotate_two *a2 );

	/* a2_set_inferior_tty
	 * -------------------
	 *
	 *  Sets the inferior's new tty name.
	 *
	 *  a2
	 *  --
	 *   The annotate two context.
	 *
 	 *  inferior_tty_name
	 *  -----------------
	 *   The name of the tty that the inferior should use.
	 */
	int a2_set_inferior_tty ( struct annotate_two *a2, const char *inferior_tty_name );

	/* a2_tgdb_err_msg
	 * ---------------
	 *
	 * Returns the last error message ?
	 * Not implemented yet.
	 *
	 * a2
	 * --
	 *  The annotate two context.
	 */
	int a2_tgdb_err_msg ( struct annotate_two *a2 );

	/* a2_tgdb_change_prompt
	 * ---------------------
	 *
	 *  This will change the prompt the user sees to PROMPT.
	 *
	 * a2
	 * --
	 *  The annotate two context.
	 *
	 * prompt
	 * ------
	 *  The new prompt to change too.
	 */
	int a2_tgdb_change_prompt(struct annotate_two *a2, const char *prompt);

	/* a2_tgdb_command_callback
	 * ------------------------
	 *
 	 * This is called when readline determines a command has been typed. 
	 *
	 * a2
	 * --
	 *  The annotate two context.
	 *
 	 * command
	 * ---- 
	 *  The command the user typed without the '\n'.
	 */
	int a2_tgdb_command_callback(struct annotate_two *a2, const char *command);

	/* a2_tgdb_completion_callback
	 * ---------------------------
	 *
 	 * This is called when readline determines a command needs to be completed.
	 *
	 * a2
	 * --
	 *  The annotate two context.
	 *
 	 * command
	 * ----
	 *  The command to be completed
	 */
	int a2_tgdb_completion_callback(struct annotate_two *a2, const char *command);

	/* a2_is_ready
	 * -----------
	 *
	 * Returns 1 if ready to recieve data, otherwise 0
	 *
	 * a2
	 * --
	 *  The annotate two context.
	 */
	int a2_is_ready ( struct annotate_two *a2 );

	/* a2_commands_typed_at_prompt
	 * ---------------------------
	 *
 	 * This functions recieves the characters the user has typed.
 	 * It only gets called if it is not busy ( the function above )
	 *
	 * This functions is a hack, and must be removed.
	 *
	 * a2
	 * --
	 *  The annotate two context.
	 *
	 * i
	 * -
	 *  ???
	 */
	void a2_command_typed_at_prompt ( struct annotate_two *a2, int i );

	/* a2_tgdb_is_debugger_ready
	 * -------------------------
	 *
 	 * This determines if the annotate two subsystem is ready to have gdb recieve
 	 * another command.
	 *
	 * a2
	 * --
	 *  The annotate two context.
	 *
     * Returns
	 * -------
	 *  1 if it is ready, 0 if it is not.
	 */
	int a2_tgdb_is_debugger_ready(struct annotate_two *a2);

	/* a2_tgdb_return_client_command
	 * -----------------------------
	 *
 	 *  This returns the command to send to gdb for the enum C.
 	 *  It will return NULL on error, otherwise correct string on output.
	 *
	 * a2
	 * --
	 *  The annotate two context.
	 *
	 * c
	 * -
	 *  The command to run.
	 */
	char *a2_tgdb_return_client_command ( struct annotate_two *a2, enum tgdb_command c );

	/* a2_tgdb_client_modify_breakpoint
	 * --------------------------------
	 *
	 * a2
	 * --
	 *  The annotate two context.
	 *
 	 * Look at tgdb.h
	 *
	 */
	char *a2_tgdb_client_modify_breakpoint ( struct annotate_two *a2, const char *file, int line, enum tgdb_breakpoint_action b );

#endif

/*  The only commands used
    ----------------------------
    info breakpoints    -> Get a list of breakpoints
    tty                 -> Tell gdb where to send inferior's output
    complete            -> Complete the current console line
    info sources        -> Show all the sources inferior is made of
    info source         -> Shows information on the current source file
    list                -> displays the contents of current source file
    complete arg        -> completes the argument arg
*/

enum annotate_commands {
    ANNOTATE_VOID = 0,
    ANNOTATE_INFO_BREAKPOINTS,
    ANNOTATE_TTY,
    ANNOTATE_COMPLETE,
    ANNOTATE_INFO_SOURCES,
    ANNOTATE_INFO_SOURCE_RELATIVE,
    ANNOTATE_INFO_SOURCE_ABSOLUTE,
    ANNOTATE_INFO_SOURCE,
    ANNOTATE_LIST,
    ANNOTATE_SET_PROMPT
};

/* a2_find_valid_debugger:
 * -----------------------
 *  Determines if there is a gdb that supports annotate = 2.
 *
 *  debugger:   - The path to the desired debugger to use.  
 *                If this is NULL then just "gdb" is used.
 *  argc:       - The number of arguments passed to the debugger.
 *  argv:       - The arguments passed to the debugger.
 *
 *  debugger_stdin: - writing writes to debugger's stdin
 *  gdb:        - The debugger's descriptor to select on.
 *  readline:   - Readline's descriptor to select on.
 *  config_dir  - This is the directory to write configuration files to
 *
 *  Returns 
 *      1 if there is, 
 *      0 if there isn't
 *      -1 on error
 */
int a2_find_valid_debugger ( 
            char *debugger,
            int argc, char **argv,
            int *debugger_stdin, int *gdb,
            char *config_dir);

/* a2_tgdb_init:
 * -------------
 *
 * This initializes libannotate.
 *
 * inferior_tty_name: The name of the tty that the inferior should use.
 *
 * Returns: -1 on error, 0 on success
 */
int a2_tgdb_init( const char *inferior_tty_name );

/* a2_tgdb_shutdown:
 * -----------------
 *
 *  This properly shuts down the annotate two subsystem.
 */
int a2_tgdb_shutdown(void);

/* a2_tgdb_get_source_absolute_filename:
 * -------------------------------------
 *
 * file: The relative name of the filename to get.
 */
int a2_tgdb_get_source_absolute_filename(char *file);

/* a2_tgdb_get_sources:
 * --------------------
 *
 */
int a2_tgdb_get_sources(void);

/* a2_set_inferior_tty:
 * --------------------
 *
 *  Sets the inferior's new tty name.
 *
 *  inferior_tty_name: The name of the tty that the inferior should use.
 *
 *  Returns: -1 on error, 0 on success
 */
int a2_set_inferior_tty ( const char *inferior_tty_name );

/* a2_tgdb_err_msg:
 * ----------------
 *
 */
char *a2_tgdb_err_msg(void);

/* These are called from within annotate-two-src for now 
 * A better approach will be given in the future.
 */
int a2_tgdb_change_prompt(char *prompt);

/* a2_tgdb_command_callback: 
 * -------------------------
 *
 * This is called when readline determines a command has been typed. 
 *
 *      line - The command the user typed without the '\n'.
 */
int a2_tgdb_command_callback(const char *line);

/* a2_tgdb_completion_callback: 
 * ----------------------------
 *
 *  This is called when readline determines a command needs to be completed.
 *
 *      line - The command to be completed
 */
int a2_tgdb_completion_callback(const char *line);

/* Returns 1 if ready to recieve data, otherwise 0 */
int a2_is_ready ( void );

/* a2_command_typed_at_prompt:
 *      This functions recieves the characters the user has typed.
 *      It only gets called if it is not busy ( the function above )
 */
void a2_command_typed_at_prompt ( int i );

/* a2_tgdb_is_debugger_ready:
 * --------------------------
 *
 * This determines if the annotate two subsystem is ready to have gdb recieve
 * another command.
 *
 * Returns: 1 if it is ready, 0 if it is not.
 */
int a2_tgdb_is_debugger_ready(void);

/* a2_tgdb_return_client_command
 * -----------------------------
 *
 *  This returns the command to send to gdb for the enum C.
 *
 *  It will return NULL on error, otherwise correct string on output.
 */
char *a2_tgdb_return_client_command ( enum tgdb_command c );

/* a2_tgdb_client_modify_breakpoint
 * --------------------------------
 *
 * Look at tgdb.h
 */
char *a2_tgdb_client_modify_breakpoint ( const char *file, int line, enum tgdb_breakpoint_action b );

#endif /* __A2_TGDB_H__ */