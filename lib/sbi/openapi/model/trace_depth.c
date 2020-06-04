
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "trace_depth.h"

OpenAPI_trace_depth_t *OpenAPI_trace_depth_create(
    )
{
    OpenAPI_trace_depth_t *trace_depth_local_var = OpenAPI_malloc(sizeof(OpenAPI_trace_depth_t));
    if (!trace_depth_local_var) {
        return NULL;
    }

    return trace_depth_local_var;
}

void OpenAPI_trace_depth_free(OpenAPI_trace_depth_t *trace_depth)
{
    if (NULL == trace_depth) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(trace_depth);
}

cJSON *OpenAPI_trace_depth_convertToJSON(OpenAPI_trace_depth_t *trace_depth)
{
    cJSON *item = NULL;

    if (trace_depth == NULL) {
        ogs_error("OpenAPI_trace_depth_convertToJSON() failed [TraceDepth]");
        return NULL;
    }

    item = cJSON_CreateObject();
end:
    return item;
}

OpenAPI_trace_depth_t *OpenAPI_trace_depth_parseFromJSON(cJSON *trace_depthJSON)
{
    OpenAPI_trace_depth_t *trace_depth_local_var = NULL;
    trace_depth_local_var = OpenAPI_trace_depth_create (
        );

    return trace_depth_local_var;
end:
    return NULL;
}

