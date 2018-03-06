#ifndef WIFI_CMD_NT_H
#define WIFI_CMD_NT_H

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

struct nt_cli_command
{
    /** The name of the CLI command */
    const char *name;
    /** The help text associated with the command */
    const char *help;
    /** The function that should be invoked for this command. */
    void (*function) (char *cmd);
};


void wifi_cmd_task(void *arg);


#if defined(__cplusplus)
  }
#endif

#endif // avoid multiple inclusion



