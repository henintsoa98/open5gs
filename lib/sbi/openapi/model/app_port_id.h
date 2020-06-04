/*
 * app_port_id.h
 *
 *
 */

#ifndef _OpenAPI_app_port_id_H_
#define _OpenAPI_app_port_id_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_app_port_id_s OpenAPI_app_port_id_t;
typedef struct OpenAPI_app_port_id_s {
    int destination_port;
    int originator_port;
} OpenAPI_app_port_id_t;

OpenAPI_app_port_id_t *OpenAPI_app_port_id_create(
    int destination_port,
    int originator_port
    );
void OpenAPI_app_port_id_free(OpenAPI_app_port_id_t *app_port_id);
OpenAPI_app_port_id_t *OpenAPI_app_port_id_parseFromJSON(cJSON *app_port_idJSON);
cJSON *OpenAPI_app_port_id_convertToJSON(OpenAPI_app_port_id_t *app_port_id);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_app_port_id_H_ */

