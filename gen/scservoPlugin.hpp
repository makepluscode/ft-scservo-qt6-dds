

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from scservo.idl
using RTI Code Generator (rtiddsgen) version 4.5.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#ifndef scservoPlugin_1338806988_h
#define scservoPlugin_1338806988_h

#include "scservo.hpp"

struct RTICdrStream;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

namespace scservo {

    #define String64Plugin_get_sample PRESTypePluginDefaultEndpointData_getSample

    #define String64Plugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define String64Plugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define String64Plugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define String64Plugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern String64*
    String64PluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern String64*
    String64PluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern String64*
    String64PluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    String64PluginSupport_copy_data(
        String64 *out,
        const String64 *in);

    NDDSUSERDllExport extern void 
    String64PluginSupport_destroy_data_w_params(
        String64 *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    String64PluginSupport_destroy_data_ex(
        String64 *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    String64PluginSupport_destroy_data(
        String64 *sample);

    NDDSUSERDllExport extern void 
    String64PluginSupport_print_data(
        const String64 *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    String64Plugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        String64 *out,
        const String64 *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern unsigned int 
    String64Plugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    String64Plugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    String64Plugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    String64Plugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    #define String256Plugin_get_sample PRESTypePluginDefaultEndpointData_getSample

    #define String256Plugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define String256Plugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define String256Plugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define String256Plugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern String256*
    String256PluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern String256*
    String256PluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern String256*
    String256PluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    String256PluginSupport_copy_data(
        String256 *out,
        const String256 *in);

    NDDSUSERDllExport extern void 
    String256PluginSupport_destroy_data_w_params(
        String256 *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    String256PluginSupport_destroy_data_ex(
        String256 *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    String256PluginSupport_destroy_data(
        String256 *sample);

    NDDSUSERDllExport extern void 
    String256PluginSupport_print_data(
        const String256 *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    String256Plugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        String256 *out,
        const String256 *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern unsigned int 
    String256Plugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    String256Plugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    String256Plugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    String256Plugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    #define ServoStatePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample

    #define ServoStatePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define ServoStatePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define ServoStatePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define ServoStatePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern ServoState*
    ServoStatePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern ServoState*
    ServoStatePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern ServoState*
    ServoStatePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    ServoStatePluginSupport_copy_data(
        ServoState *out,
        const ServoState *in);

    NDDSUSERDllExport extern void 
    ServoStatePluginSupport_destroy_data_w_params(
        ServoState *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    ServoStatePluginSupport_destroy_data_ex(
        ServoState *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    ServoStatePluginSupport_destroy_data(
        ServoState *sample);

    NDDSUSERDllExport extern void 
    ServoStatePluginSupport_print_data(
        const ServoState *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    ServoStatePlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    ServoStatePlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    ServoStatePlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    ServoStatePlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    ServoStatePlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        ServoState *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    ServoStatePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        ServoState *out,
        const ServoState *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    ServoStatePlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const ServoState *sample,
        ::dds::core::policy::DataRepresentationId representation
        = ::dds::core::policy::DataRepresentation::xcdr()); 

    NDDSUSERDllExport extern RTIBool 
    ServoStatePlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        ServoState **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    ServoStatePlugin_deserialize_from_cdr_buffer(
        ServoState *sample,
        const char * buffer,
        unsigned int length);    

    NDDSUSERDllExport extern unsigned int 
    ServoStatePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    ServoStatePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    ServoStatePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    ServoStatePlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    ServoStatePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        ServoState ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    ServoStatePlugin_new(void);

    NDDSUSERDllExport extern void
    ServoStatePlugin_delete(struct PRESTypePlugin *);

    #define MemoryValPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample

    #define MemoryValPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define MemoryValPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define MemoryValPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define MemoryValPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern MemoryVal*
    MemoryValPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern MemoryVal*
    MemoryValPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern MemoryVal*
    MemoryValPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    MemoryValPluginSupport_copy_data(
        MemoryVal *out,
        const MemoryVal *in);

    NDDSUSERDllExport extern void 
    MemoryValPluginSupport_destroy_data_w_params(
        MemoryVal *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    MemoryValPluginSupport_destroy_data_ex(
        MemoryVal *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    MemoryValPluginSupport_destroy_data(
        MemoryVal *sample);

    NDDSUSERDllExport extern void 
    MemoryValPluginSupport_print_data(
        const MemoryVal *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    MemoryValPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    MemoryValPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    MemoryValPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    MemoryValPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    MemoryValPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        MemoryVal *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    MemoryValPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        MemoryVal *out,
        const MemoryVal *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    MemoryValPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const MemoryVal *sample,
        ::dds::core::policy::DataRepresentationId representation
        = ::dds::core::policy::DataRepresentation::xcdr()); 

    NDDSUSERDllExport extern RTIBool 
    MemoryValPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        MemoryVal **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    MemoryValPlugin_deserialize_from_cdr_buffer(
        MemoryVal *sample,
        const char * buffer,
        unsigned int length);    

    NDDSUSERDllExport extern unsigned int 
    MemoryValPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    MemoryValPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    MemoryValPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    MemoryValPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    MemoryValPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        MemoryVal ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    MemoryValPlugin_new(void);

    NDDSUSERDllExport extern void
    MemoryValPlugin_delete(struct PRESTypePlugin *);

    #define ServoCommandPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample

    #define ServoCommandPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define ServoCommandPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define ServoCommandPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define ServoCommandPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern ServoCommand*
    ServoCommandPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern ServoCommand*
    ServoCommandPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern ServoCommand*
    ServoCommandPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    ServoCommandPluginSupport_copy_data(
        ServoCommand *out,
        const ServoCommand *in);

    NDDSUSERDllExport extern void 
    ServoCommandPluginSupport_destroy_data_w_params(
        ServoCommand *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    ServoCommandPluginSupport_destroy_data_ex(
        ServoCommand *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    ServoCommandPluginSupport_destroy_data(
        ServoCommand *sample);

    NDDSUSERDllExport extern void 
    ServoCommandPluginSupport_print_data(
        const ServoCommand *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    ServoCommandPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    ServoCommandPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    ServoCommandPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    ServoCommandPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    ServoCommandPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        ServoCommand *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    ServoCommandPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        ServoCommand *out,
        const ServoCommand *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    ServoCommandPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const ServoCommand *sample,
        ::dds::core::policy::DataRepresentationId representation
        = ::dds::core::policy::DataRepresentation::xcdr()); 

    NDDSUSERDllExport extern RTIBool 
    ServoCommandPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        ServoCommand **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    ServoCommandPlugin_deserialize_from_cdr_buffer(
        ServoCommand *sample,
        const char * buffer,
        unsigned int length);    

    NDDSUSERDllExport extern unsigned int 
    ServoCommandPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    ServoCommandPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    ServoCommandPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    ServoCommandPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    ServoCommandPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        ServoCommand ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    ServoCommandPlugin_new(void);

    NDDSUSERDllExport extern void
    ServoCommandPlugin_delete(struct PRESTypePlugin *);

    #define ServoFeedbackPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample

    #define ServoFeedbackPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define ServoFeedbackPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define ServoFeedbackPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define ServoFeedbackPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern ServoFeedback*
    ServoFeedbackPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern ServoFeedback*
    ServoFeedbackPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern ServoFeedback*
    ServoFeedbackPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    ServoFeedbackPluginSupport_copy_data(
        ServoFeedback *out,
        const ServoFeedback *in);

    NDDSUSERDllExport extern void 
    ServoFeedbackPluginSupport_destroy_data_w_params(
        ServoFeedback *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    ServoFeedbackPluginSupport_destroy_data_ex(
        ServoFeedback *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    ServoFeedbackPluginSupport_destroy_data(
        ServoFeedback *sample);

    NDDSUSERDllExport extern void 
    ServoFeedbackPluginSupport_print_data(
        const ServoFeedback *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    ServoFeedbackPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    ServoFeedbackPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    ServoFeedbackPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    ServoFeedbackPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    ServoFeedbackPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        ServoFeedback *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    ServoFeedbackPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        ServoFeedback *out,
        const ServoFeedback *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    ServoFeedbackPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const ServoFeedback *sample,
        ::dds::core::policy::DataRepresentationId representation
        = ::dds::core::policy::DataRepresentation::xcdr()); 

    NDDSUSERDllExport extern RTIBool 
    ServoFeedbackPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        ServoFeedback **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    ServoFeedbackPlugin_deserialize_from_cdr_buffer(
        ServoFeedback *sample,
        const char * buffer,
        unsigned int length);    

    NDDSUSERDllExport extern unsigned int 
    ServoFeedbackPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    ServoFeedbackPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    ServoFeedbackPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    ServoFeedbackPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    ServoFeedbackPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        ServoFeedback ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    ServoFeedbackPlugin_new(void);

    NDDSUSERDllExport extern void
    ServoFeedbackPlugin_delete(struct PRESTypePlugin *);

} /* namespace scservo  */

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* scservoPlugin_1338806988_h */
