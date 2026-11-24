
#include <stdio.h>
#include <stdlib.h>
#include <csp/csp.h>
#include <slash/slash.h>
#include <slash/optparse.h>
#include <slash/dflopt.h>

void libinfo(void) {

	printf("This APM contains custom functionality to support the NTU SAP2 missions\n");
}

static int music4u_update_cmd(struct slash *slash)
{

	unsigned int node = slash_dfl_node;
	unsigned int timeout = slash_dfl_timeout;

    optparse_t * parser = optparse_new("music4u update", "<filename> <slot>");
    optparse_add_help(parser);
    optparse_add_unsigned(parser, 'n', "node", "NUM", 0, &node, "node (default = 16383, broadcast to all)");
    optparse_add_unsigned(parser, 't', "timeout", "NUM", 0, &timeout, "timeout [ms] (default = 1000)");

    int argi = optparse_parse(parser, slash->argc - 1, (const char **) slash->argv + 1);
    if (argi < 0) {
        optparse_del(parser);
	    return SLASH_EINVAL;
    }

	/* Expect filename */
	if (++argi >= slash->argc) {
		printf("missing filename\n");
		optparse_del(parser);
		return SLASH_EINVAL;
	}

	char * file;
	file = slash->argv[argi];

	/* Expect slot */
	if (++argi >= slash->argc) {
		printf("missing slot number\n");
        optparse_del(parser);
		return SLASH_EINVAL;
	}

	char *end = NULL;
	int slot = strtol(slash->argv[argi], &end, 10);
    if (*end != '\0') {
		printf("Cannot interpret '%s' as a valid slot number\n", slash->argv[argi]);
        optparse_del(parser);
		return SLASH_EINVAL;
	}

	if (slot < 0 || slot > 1) {
		printf("'slot' must be between 0 and 1\n");
        optparse_del(parser);
		return SLASH_EINVAL;
	}

	printf("Uploading MUSIC4U application %s to slot %d\n", file, slot);
	/* TODO: Custom CSP code that uploads file to the MUSIC4U thruster, located at node <node> */

	optparse_del(parser);
	return SLASH_SUCCESS;
}
slash_command_sub(music4u, update, music4u_update_cmd, "", "Program MUSIC4U thruster");
