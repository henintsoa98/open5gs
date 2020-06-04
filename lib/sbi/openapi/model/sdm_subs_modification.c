
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sdm_subs_modification.h"

OpenAPI_sdm_subs_modification_t *OpenAPI_sdm_subs_modification_create(
    char *expires,
    OpenAPI_list_t *monitored_resource_uris
    )
{
    OpenAPI_sdm_subs_modification_t *sdm_subs_modification_local_var = OpenAPI_malloc(sizeof(OpenAPI_sdm_subs_modification_t));
    if (!sdm_subs_modification_local_var) {
        return NULL;
    }
    sdm_subs_modification_local_var->expires = expires;
    sdm_subs_modification_local_var->monitored_resource_uris = monitored_resource_uris;

    return sdm_subs_modification_local_var;
}

void OpenAPI_sdm_subs_modification_free(OpenAPI_sdm_subs_modification_t *sdm_subs_modification)
{
    if (NULL == sdm_subs_modification) {
        return;
    }
    OpenAPI_lnode_t *node;
    ogs_free(sdm_subs_modification->expires);
    OpenAPI_list_for_each(sdm_subs_modification->monitored_resource_uris, node) {
        ogs_free(node->data);
    }
    OpenAPI_list_free(sdm_subs_modification->monitored_resource_uris);
    ogs_free(sdm_subs_modification);
}

cJSON *OpenAPI_sdm_subs_modification_convertToJSON(OpenAPI_sdm_subs_modification_t *sdm_subs_modification)
{
    cJSON *item = NULL;

    if (sdm_subs_modification == NULL) {
        ogs_error("OpenAPI_sdm_subs_modification_convertToJSON() failed [SdmSubsModification]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (sdm_subs_modification->expires) {
        if (cJSON_AddStringToObject(item, "expires", sdm_subs_modification->expires) == NULL) {
            ogs_error("OpenAPI_sdm_subs_modification_convertToJSON() failed [expires]");
            goto end;
        }
    }

    if (sdm_subs_modification->monitored_resource_uris) {
        cJSON *monitored_resource_uris = cJSON_AddArrayToObject(item, "monitoredResourceUris");
        if (monitored_resource_uris == NULL) {
            ogs_error("OpenAPI_sdm_subs_modification_convertToJSON() failed [monitored_resource_uris]");
            goto end;
        }

        OpenAPI_lnode_t *monitored_resource_uris_node;
        OpenAPI_list_for_each(sdm_subs_modification->monitored_resource_uris, monitored_resource_uris_node)  {
            if (cJSON_AddStringToObject(monitored_resource_uris, "", (char*)monitored_resource_uris_node->data) == NULL) {
                ogs_error("OpenAPI_sdm_subs_modification_convertToJSON() failed [monitored_resource_uris]");
                goto end;
            }
        }
    }

end:
    return item;
}

OpenAPI_sdm_subs_modification_t *OpenAPI_sdm_subs_modification_parseFromJSON(cJSON *sdm_subs_modificationJSON)
{
    OpenAPI_sdm_subs_modification_t *sdm_subs_modification_local_var = NULL;
    cJSON *expires = cJSON_GetObjectItemCaseSensitive(sdm_subs_modificationJSON, "expires");

    if (expires) {
        if (!cJSON_IsString(expires)) {
            ogs_error("OpenAPI_sdm_subs_modification_parseFromJSON() failed [expires]");
            goto end;
        }
    }

    cJSON *monitored_resource_uris = cJSON_GetObjectItemCaseSensitive(sdm_subs_modificationJSON, "monitoredResourceUris");

    OpenAPI_list_t *monitored_resource_urisList;
    if (monitored_resource_uris) {
        cJSON *monitored_resource_uris_local;
        if (!cJSON_IsArray(monitored_resource_uris)) {
            ogs_error("OpenAPI_sdm_subs_modification_parseFromJSON() failed [monitored_resource_uris]");
            goto end;
        }
        monitored_resource_urisList = OpenAPI_list_create();

        cJSON_ArrayForEach(monitored_resource_uris_local, monitored_resource_uris) {
            if (!cJSON_IsString(monitored_resource_uris_local)) {
                ogs_error("OpenAPI_sdm_subs_modification_parseFromJSON() failed [monitored_resource_uris]");
                goto end;
            }
            OpenAPI_list_add(monitored_resource_urisList, ogs_strdup(monitored_resource_uris_local->valuestring));
        }
    }

    sdm_subs_modification_local_var = OpenAPI_sdm_subs_modification_create (
        expires ? ogs_strdup(expires->valuestring) : NULL,
        monitored_resource_uris ? monitored_resource_urisList : NULL
        );

    return sdm_subs_modification_local_var;
end:
    return NULL;
}

