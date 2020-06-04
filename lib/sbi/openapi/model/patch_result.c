
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "patch_result.h"

OpenAPI_patch_result_t *OpenAPI_patch_result_create(
    OpenAPI_list_t *report
    )
{
    OpenAPI_patch_result_t *patch_result_local_var = OpenAPI_malloc(sizeof(OpenAPI_patch_result_t));
    if (!patch_result_local_var) {
        return NULL;
    }
    patch_result_local_var->report = report;

    return patch_result_local_var;
}

void OpenAPI_patch_result_free(OpenAPI_patch_result_t *patch_result)
{
    if (NULL == patch_result) {
        return;
    }
    OpenAPI_lnode_t *node;
    OpenAPI_list_for_each(patch_result->report, node) {
        OpenAPI_report_item_free(node->data);
    }
    OpenAPI_list_free(patch_result->report);
    ogs_free(patch_result);
}

cJSON *OpenAPI_patch_result_convertToJSON(OpenAPI_patch_result_t *patch_result)
{
    cJSON *item = NULL;

    if (patch_result == NULL) {
        ogs_error("OpenAPI_patch_result_convertToJSON() failed [PatchResult]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (!patch_result->report) {
        ogs_error("OpenAPI_patch_result_convertToJSON() failed [report]");
        goto end;
    }
    cJSON *reportList = cJSON_AddArrayToObject(item, "report");
    if (reportList == NULL) {
        ogs_error("OpenAPI_patch_result_convertToJSON() failed [report]");
        goto end;
    }

    OpenAPI_lnode_t *report_node;
    if (patch_result->report) {
        OpenAPI_list_for_each(patch_result->report, report_node) {
            cJSON *itemLocal = OpenAPI_report_item_convertToJSON(report_node->data);
            if (itemLocal == NULL) {
                ogs_error("OpenAPI_patch_result_convertToJSON() failed [report]");
                goto end;
            }
            cJSON_AddItemToArray(reportList, itemLocal);
        }
    }

end:
    return item;
}

OpenAPI_patch_result_t *OpenAPI_patch_result_parseFromJSON(cJSON *patch_resultJSON)
{
    OpenAPI_patch_result_t *patch_result_local_var = NULL;
    cJSON *report = cJSON_GetObjectItemCaseSensitive(patch_resultJSON, "report");
    if (!report) {
        ogs_error("OpenAPI_patch_result_parseFromJSON() failed [report]");
        goto end;
    }

    OpenAPI_list_t *reportList;

    cJSON *report_local_nonprimitive;
    if (!cJSON_IsArray(report)) {
        ogs_error("OpenAPI_patch_result_parseFromJSON() failed [report]");
        goto end;
    }

    reportList = OpenAPI_list_create();

    cJSON_ArrayForEach(report_local_nonprimitive, report ) {
        if (!cJSON_IsObject(report_local_nonprimitive)) {
            ogs_error("OpenAPI_patch_result_parseFromJSON() failed [report]");
            goto end;
        }
        OpenAPI_report_item_t *reportItem = OpenAPI_report_item_parseFromJSON(report_local_nonprimitive);

        OpenAPI_list_add(reportList, reportItem);
    }

    patch_result_local_var = OpenAPI_patch_result_create (
        reportList
        );

    return patch_result_local_var;
end:
    return NULL;
}

