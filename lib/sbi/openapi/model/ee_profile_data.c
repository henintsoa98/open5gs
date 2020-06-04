
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ee_profile_data.h"

OpenAPI_ee_profile_data_t *OpenAPI_ee_profile_data_create(
    OpenAPI_list_t *restricted_event_types,
    char *supported_features
    )
{
    OpenAPI_ee_profile_data_t *ee_profile_data_local_var = OpenAPI_malloc(sizeof(OpenAPI_ee_profile_data_t));
    if (!ee_profile_data_local_var) {
        return NULL;
    }
    ee_profile_data_local_var->restricted_event_types = restricted_event_types;
    ee_profile_data_local_var->supported_features = supported_features;

    return ee_profile_data_local_var;
}

void OpenAPI_ee_profile_data_free(OpenAPI_ee_profile_data_t *ee_profile_data)
{
    if (NULL == ee_profile_data) {
        return;
    }
    OpenAPI_lnode_t *node;
    OpenAPI_list_for_each(ee_profile_data->restricted_event_types, node) {
        OpenAPI_event_type_free(node->data);
    }
    OpenAPI_list_free(ee_profile_data->restricted_event_types);
    ogs_free(ee_profile_data->supported_features);
    ogs_free(ee_profile_data);
}

cJSON *OpenAPI_ee_profile_data_convertToJSON(OpenAPI_ee_profile_data_t *ee_profile_data)
{
    cJSON *item = NULL;

    if (ee_profile_data == NULL) {
        ogs_error("OpenAPI_ee_profile_data_convertToJSON() failed [EeProfileData]");
        return NULL;
    }

    item = cJSON_CreateObject();
    if (ee_profile_data->restricted_event_types) {
        cJSON *restricted_event_typesList = cJSON_AddArrayToObject(item, "restrictedEventTypes");
        if (restricted_event_typesList == NULL) {
            ogs_error("OpenAPI_ee_profile_data_convertToJSON() failed [restricted_event_types]");
            goto end;
        }

        OpenAPI_lnode_t *restricted_event_types_node;
        if (ee_profile_data->restricted_event_types) {
            OpenAPI_list_for_each(ee_profile_data->restricted_event_types, restricted_event_types_node) {
                cJSON *itemLocal = OpenAPI_event_type_convertToJSON(restricted_event_types_node->data);
                if (itemLocal == NULL) {
                    ogs_error("OpenAPI_ee_profile_data_convertToJSON() failed [restricted_event_types]");
                    goto end;
                }
                cJSON_AddItemToArray(restricted_event_typesList, itemLocal);
            }
        }
    }

    if (ee_profile_data->supported_features) {
        if (cJSON_AddStringToObject(item, "supportedFeatures", ee_profile_data->supported_features) == NULL) {
            ogs_error("OpenAPI_ee_profile_data_convertToJSON() failed [supported_features]");
            goto end;
        }
    }

end:
    return item;
}

OpenAPI_ee_profile_data_t *OpenAPI_ee_profile_data_parseFromJSON(cJSON *ee_profile_dataJSON)
{
    OpenAPI_ee_profile_data_t *ee_profile_data_local_var = NULL;
    cJSON *restricted_event_types = cJSON_GetObjectItemCaseSensitive(ee_profile_dataJSON, "restrictedEventTypes");

    OpenAPI_list_t *restricted_event_typesList;
    if (restricted_event_types) {
        cJSON *restricted_event_types_local_nonprimitive;
        if (!cJSON_IsArray(restricted_event_types)) {
            ogs_error("OpenAPI_ee_profile_data_parseFromJSON() failed [restricted_event_types]");
            goto end;
        }

        restricted_event_typesList = OpenAPI_list_create();

        cJSON_ArrayForEach(restricted_event_types_local_nonprimitive, restricted_event_types ) {
            if (!cJSON_IsObject(restricted_event_types_local_nonprimitive)) {
                ogs_error("OpenAPI_ee_profile_data_parseFromJSON() failed [restricted_event_types]");
                goto end;
            }
            OpenAPI_event_type_t *restricted_event_typesItem = OpenAPI_event_type_parseFromJSON(restricted_event_types_local_nonprimitive);

            OpenAPI_list_add(restricted_event_typesList, restricted_event_typesItem);
        }
    }

    cJSON *supported_features = cJSON_GetObjectItemCaseSensitive(ee_profile_dataJSON, "supportedFeatures");

    if (supported_features) {
        if (!cJSON_IsString(supported_features)) {
            ogs_error("OpenAPI_ee_profile_data_parseFromJSON() failed [supported_features]");
            goto end;
        }
    }

    ee_profile_data_local_var = OpenAPI_ee_profile_data_create (
        restricted_event_types ? restricted_event_typesList : NULL,
        supported_features ? ogs_strdup(supported_features->valuestring) : NULL
        );

    return ee_profile_data_local_var;
end:
    return NULL;
}

