/*
 * dnn_configuration.h
 *
 *
 */

#ifndef _OpenAPI_dnn_configuration_H_
#define _OpenAPI_dnn_configuration_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "acs_info.h"
#include "ambr.h"
#include "frame_route_info.h"
#include "ip_address.h"
#include "nidd_information.h"
#include "pdu_session_continuity_ind.h"
#include "pdu_session_types.h"
#include "ssc_modes.h"
#include "subscribed_default_qos.h"
#include "up_security.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_dnn_configuration_s OpenAPI_dnn_configuration_t;
typedef struct OpenAPI_dnn_configuration_s {
    struct OpenAPI_pdu_session_types_s *pdu_session_types;
    struct OpenAPI_ssc_modes_s *ssc_modes;
    int iwk_eps_ind;
    struct OpenAPI_subscribed_default_qos_s *_5g_qos_profile;
    struct OpenAPI_ambr_s *session_ambr;
    char *_3gpp_charging_characteristics;
    OpenAPI_list_t *static_ip_address;
    struct OpenAPI_up_security_s *up_security;
    OpenAPI_pdu_session_continuity_ind_e pdu_session_continuity_ind;
    int invoke_nef_selection;
    char *nidd_nef_id;
    struct OpenAPI_nidd_information_s *nidd_info;
    int redundant_session_allowed;
    struct OpenAPI_acs_info_s *acs_info;
    OpenAPI_list_t *ipv4_frame_route_list;
    OpenAPI_list_t *ipv6_frame_route_list;
    int atsss_allowed;
} OpenAPI_dnn_configuration_t;

OpenAPI_dnn_configuration_t *OpenAPI_dnn_configuration_create(
    OpenAPI_pdu_session_types_t *pdu_session_types,
    OpenAPI_ssc_modes_t *ssc_modes,
    int iwk_eps_ind,
    OpenAPI_subscribed_default_qos_t *_5g_qos_profile,
    OpenAPI_ambr_t *session_ambr,
    char *_3gpp_charging_characteristics,
    OpenAPI_list_t *static_ip_address,
    OpenAPI_up_security_t *up_security,
    OpenAPI_pdu_session_continuity_ind_e pdu_session_continuity_ind,
    int invoke_nef_selection,
    char *nidd_nef_id,
    OpenAPI_nidd_information_t *nidd_info,
    int redundant_session_allowed,
    OpenAPI_acs_info_t *acs_info,
    OpenAPI_list_t *ipv4_frame_route_list,
    OpenAPI_list_t *ipv6_frame_route_list,
    int atsss_allowed
    );
void OpenAPI_dnn_configuration_free(OpenAPI_dnn_configuration_t *dnn_configuration);
OpenAPI_dnn_configuration_t *OpenAPI_dnn_configuration_parseFromJSON(cJSON *dnn_configurationJSON);
cJSON *OpenAPI_dnn_configuration_convertToJSON(OpenAPI_dnn_configuration_t *dnn_configuration);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_dnn_configuration_H_ */

