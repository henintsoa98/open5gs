
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lcs_privacy.h"

OpenAPI_lcs_privacy_t *OpenAPI_lcs_privacy_create(
    char *af_instance_id,
    int reference_id,
    OpenAPI_lpi_t *lpi
    )
{
    OpenAPI_lcs_privacy_t *lcs_privacy_local_var = OpenAPI_malloc(sizeof(OpenAPI_lcs_privacy_t));
    if (!lcs_privacy_local_var) {
        return NULL;
    }
    lcs_privacy_local_var->af_instance_id = af_instance_id;
    lcs_privacy_local_var->reference_id = reference_id;
    lcs_privacy_local_var->lpi = lpi;

    return lcs_privacy_local_var;
}

void OpenAPI_lcs_privacy_free(OpenAPI_lcs_privacy_t *lcs_privacy)
{
    if (NULL == lcs_privacy) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(lcs_privacy->af_instance_id);
    OpenAPI_lpi_free(lcs_privacy->lpi);
    ogs_free(lcs_privacy);
}

cJSON *OpenAPI_lcs_privacy_convertToJSON(OpenAPI_lcs_privacy_t *lcs_privacy)
{
    cJSON *item = NULL;

    if (lcs_privacy == NULL) {
        ogs_error("OpenAPI_lcs_privacy_convertToJSON() failed [LcsPrivacy]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (lcs_privacy->af_instance_id) {
        if (cJSON_AddStringToObject(item, "afInstanceId", lcs_privacy->af_instance_id) == NULL) {
            ogs_error("OpenAPI_lcs_privacy_convertToJSON() failed [af_instance_id]");
            goto end;
        }
    }

    if (lcs_privacy->reference_id) {
        if (cJSON_AddNumberToObject(item, "referenceId", lcs_privacy->reference_id) == NULL) {
            ogs_error("OpenAPI_lcs_privacy_convertToJSON() failed [reference_id]");
            goto end;
        }
    }

    if (lcs_privacy->lpi) {
        cJSON *lpi_local_JSON = OpenAPI_lpi_convertToJSON(lcs_privacy->lpi);
        if (lpi_local_JSON == NULL) {
            ogs_error("OpenAPI_lcs_privacy_convertToJSON() failed [lpi]");
            goto end;
        }
        cJSON_AddItemToObject(item, "lpi", lpi_local_JSON);
        if (item->child == NULL) {
            ogs_error("OpenAPI_lcs_privacy_convertToJSON() failed [lpi]");
            goto end;
        }
    }

end:
    return item;
}

OpenAPI_lcs_privacy_t *OpenAPI_lcs_privacy_parseFromJSON(cJSON *lcs_privacyJSON)
{
    OpenAPI_lcs_privacy_t *lcs_privacy_local_var = NULL;
    cJSON *af_instance_id = cJSON_GetObjectItemCaseSensitive(lcs_privacyJSON, "afInstanceId");

    if (af_instance_id) {
        if (!cJSON_IsString(af_instance_id)) {
            ogs_error("OpenAPI_lcs_privacy_parseFromJSON() failed [af_instance_id]");
            goto end;
        }
    }

    cJSON *reference_id = cJSON_GetObjectItemCaseSensitive(lcs_privacyJSON, "referenceId");

    if (reference_id) {
        if (!cJSON_IsNumber(reference_id)) {
            ogs_error("OpenAPI_lcs_privacy_parseFromJSON() failed [reference_id]");
            goto end;
        }
    }

    cJSON *lpi = cJSON_GetObjectItemCaseSensitive(lcs_privacyJSON, "lpi");

    OpenAPI_lpi_t *lpi_local_nonprim = NULL;
    if (lpi) {
        lpi_local_nonprim = OpenAPI_lpi_parseFromJSON(lpi);
    }

    lcs_privacy_local_var = OpenAPI_lcs_privacy_create (
        af_instance_id ? ogs_strdup(af_instance_id->valuestring) : NULL,
        reference_id ? reference_id->valuedouble : 0,
        lpi ? lpi_local_nonprim : NULL
        );

    return lcs_privacy_local_var;
end:
    return NULL;
}

