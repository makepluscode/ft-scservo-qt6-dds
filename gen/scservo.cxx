

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from scservo.idl
using RTI Code Generator (rtiddsgen) version 4.5.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#include <iosfwd>
#include <iomanip>
#include <atomic>

#ifndef NDDS_STANDALONE_TYPE
#include "rti/topic/cdr/Serialization.hpp"
#include "scservoPlugin.hpp"
#else
#include "rti/topic/cdr/SerializationHelpers.hpp"
#endif

#include "scservo.hpp"

#include <rti/util/ostream_operators.hpp>

namespace scservo {

    // ---- ServoState: 

    ServoState::ServoState() :
        m_id_ (0) ,
        m_position_ (0) ,
        m_speed_ (0) ,
        m_load_ (0) ,
        m_voltage_ (0) ,
        m_temperature_ (0) ,
        m_current_ (0)  {

    }   

    ServoState::ServoState (int32_t id_,int32_t position_,int32_t speed_,int32_t load_,int32_t voltage_,int32_t temperature_,int32_t current_):
        m_id_(id_), 
        m_position_(position_), 
        m_speed_(speed_), 
        m_load_(load_), 
        m_voltage_(voltage_), 
        m_temperature_(temperature_), 
        m_current_(current_) {
    }

    void ServoState::swap(ServoState& other_)  noexcept 
    {
        using std::swap;
        swap(m_id_, other_.m_id_);
        swap(m_position_, other_.m_position_);
        swap(m_speed_, other_.m_speed_);
        swap(m_load_, other_.m_load_);
        swap(m_voltage_, other_.m_voltage_);
        swap(m_temperature_, other_.m_temperature_);
        swap(m_current_, other_.m_current_);
    }  

    bool ServoState::operator == (const ServoState& other_) const {
        if (m_id_ != other_.m_id_) {
            return false;
        }
        if (m_position_ != other_.m_position_) {
            return false;
        }
        if (m_speed_ != other_.m_speed_) {
            return false;
        }
        if (m_load_ != other_.m_load_) {
            return false;
        }
        if (m_voltage_ != other_.m_voltage_) {
            return false;
        }
        if (m_temperature_ != other_.m_temperature_) {
            return false;
        }
        if (m_current_ != other_.m_current_) {
            return false;
        }
        return true;
    }

    bool ServoState::operator != (const ServoState& other_) const {
        return !this->operator ==(other_);
    }

    std::ostream& operator << (std::ostream& o,const ServoState& sample)
    {
        ::rti::util::StreamFlagSaver flag_saver (o);
        o <<"[";
        o << "id: " << sample.id()<<", ";
        o << "position: " << sample.position()<<", ";
        o << "speed: " << sample.speed()<<", ";
        o << "load: " << sample.load()<<", ";
        o << "voltage: " << sample.voltage()<<", ";
        o << "temperature: " << sample.temperature()<<", ";
        o << "current: " << sample.current();
        o <<"]";
        return o;
    }

    // ---- MemoryVal: 

    MemoryVal::MemoryVal() :
        m_address_ (0) ,
        m_value_ (0)  {

    }   

    MemoryVal::MemoryVal (int32_t address_,int32_t value_):
        m_address_(address_), 
        m_value_(value_) {
    }

    void MemoryVal::swap(MemoryVal& other_)  noexcept 
    {
        using std::swap;
        swap(m_address_, other_.m_address_);
        swap(m_value_, other_.m_value_);
    }  

    bool MemoryVal::operator == (const MemoryVal& other_) const {
        if (m_address_ != other_.m_address_) {
            return false;
        }
        if (m_value_ != other_.m_value_) {
            return false;
        }
        return true;
    }

    bool MemoryVal::operator != (const MemoryVal& other_) const {
        return !this->operator ==(other_);
    }

    std::ostream& operator << (std::ostream& o,const MemoryVal& sample)
    {
        ::rti::util::StreamFlagSaver flag_saver (o);
        o <<"[";
        o << "address: " << sample.address()<<", ";
        o << "value: " << sample.value();
        o <<"]";
        return o;
    }

    // ---- ServoCommand: 

    ServoCommand::ServoCommand() :
        m_command_type_ ("") ,
        m_port_name_ ("") ,
        m_baud_rate_ (0) ,
        m_servo_id_ (0) ,
        m_address_ (0) ,
        m_value_ (0) ,
        m_size_ (0) ,
        m_time_ms_ (0) ,
        m_speed_ (0) ,
        m_acc_ (0) ,
        m_timestamp_ (0ll)  {

    }   

    ServoCommand::ServoCommand (const std::string& command_type_,const std::string& port_name_,int32_t baud_rate_,int32_t servo_id_,const ::rti::core::bounded_sequence< int32_t, 100L >& target_ids_,int32_t address_,int32_t value_,int32_t size_,int32_t time_ms_,int32_t speed_,int32_t acc_,int64_t timestamp_):
        m_command_type_(command_type_), 
        m_port_name_(port_name_), 
        m_baud_rate_(baud_rate_), 
        m_servo_id_(servo_id_), 
        m_target_ids_(target_ids_), 
        m_address_(address_), 
        m_value_(value_), 
        m_size_(size_), 
        m_time_ms_(time_ms_), 
        m_speed_(speed_), 
        m_acc_(acc_), 
        m_timestamp_(timestamp_) {
    }

    void ServoCommand::swap(ServoCommand& other_)  noexcept 
    {
        using std::swap;
        swap(m_command_type_, other_.m_command_type_);
        swap(m_port_name_, other_.m_port_name_);
        swap(m_baud_rate_, other_.m_baud_rate_);
        swap(m_servo_id_, other_.m_servo_id_);
        swap(m_target_ids_, other_.m_target_ids_);
        swap(m_address_, other_.m_address_);
        swap(m_value_, other_.m_value_);
        swap(m_size_, other_.m_size_);
        swap(m_time_ms_, other_.m_time_ms_);
        swap(m_speed_, other_.m_speed_);
        swap(m_acc_, other_.m_acc_);
        swap(m_timestamp_, other_.m_timestamp_);
    }  

    bool ServoCommand::operator == (const ServoCommand& other_) const {
        if (m_command_type_ != other_.m_command_type_) {
            return false;
        }
        if (m_port_name_ != other_.m_port_name_) {
            return false;
        }
        if (m_baud_rate_ != other_.m_baud_rate_) {
            return false;
        }
        if (m_servo_id_ != other_.m_servo_id_) {
            return false;
        }
        if (m_target_ids_ != other_.m_target_ids_) {
            return false;
        }
        if (m_address_ != other_.m_address_) {
            return false;
        }
        if (m_value_ != other_.m_value_) {
            return false;
        }
        if (m_size_ != other_.m_size_) {
            return false;
        }
        if (m_time_ms_ != other_.m_time_ms_) {
            return false;
        }
        if (m_speed_ != other_.m_speed_) {
            return false;
        }
        if (m_acc_ != other_.m_acc_) {
            return false;
        }
        if (m_timestamp_ != other_.m_timestamp_) {
            return false;
        }
        return true;
    }

    bool ServoCommand::operator != (const ServoCommand& other_) const {
        return !this->operator ==(other_);
    }

    std::ostream& operator << (std::ostream& o,const ServoCommand& sample)
    {
        ::rti::util::StreamFlagSaver flag_saver (o);
        o <<"[";
        o << "command_type: " << sample.command_type()<<", ";
        o << "port_name: " << sample.port_name()<<", ";
        o << "baud_rate: " << sample.baud_rate()<<", ";
        o << "servo_id: " << sample.servo_id()<<", ";
        o << "target_ids: " << sample.target_ids()<<", ";
        o << "address: " << sample.address()<<", ";
        o << "value: " << sample.value()<<", ";
        o << "size: " << sample.size()<<", ";
        o << "time_ms: " << sample.time_ms()<<", ";
        o << "speed: " << sample.speed()<<", ";
        o << "acc: " << sample.acc()<<", ";
        o << "timestamp: " << sample.timestamp();
        o <<"]";
        return o;
    }

    // ---- ServoFeedback: 

    ServoFeedback::ServoFeedback() :
        m_feedback_type_ ("") ,
        m_connected_ (0) ,
        m_current_port_ ("") ,
        m_message_ ("") ,
        m_is_error_ (0) ,
        m_timestamp_ (0ll)  {

    }   

    ServoFeedback::ServoFeedback (const std::string& feedback_type_,bool connected_,const std::string& current_port_,const ::rti::core::bounded_sequence< ::scservo::String64, 100L >& available_ports_,const ::rti::core::bounded_sequence< int32_t, 100L >& found_ids_,const ::scservo::ServoState& state_,const std::string& message_,bool is_error_,int64_t timestamp_):
        m_feedback_type_(feedback_type_), 
        m_connected_(connected_), 
        m_current_port_(current_port_), 
        m_available_ports_(available_ports_), 
        m_found_ids_(found_ids_), 
        m_state_(state_), 
        m_message_(message_), 
        m_is_error_(is_error_), 
        m_timestamp_(timestamp_) {
    }

    void ServoFeedback::swap(ServoFeedback& other_)  noexcept 
    {
        using std::swap;
        swap(m_feedback_type_, other_.m_feedback_type_);
        swap(m_connected_, other_.m_connected_);
        swap(m_current_port_, other_.m_current_port_);
        swap(m_available_ports_, other_.m_available_ports_);
        swap(m_found_ids_, other_.m_found_ids_);
        swap(m_state_, other_.m_state_);
        swap(m_message_, other_.m_message_);
        swap(m_is_error_, other_.m_is_error_);
        swap(m_timestamp_, other_.m_timestamp_);
    }  

    bool ServoFeedback::operator == (const ServoFeedback& other_) const {
        if (m_feedback_type_ != other_.m_feedback_type_) {
            return false;
        }
        if (m_connected_ != other_.m_connected_) {
            return false;
        }
        if (m_current_port_ != other_.m_current_port_) {
            return false;
        }
        if (m_available_ports_ != other_.m_available_ports_) {
            return false;
        }
        if (m_found_ids_ != other_.m_found_ids_) {
            return false;
        }
        if (m_state_ != other_.m_state_) {
            return false;
        }
        if (m_message_ != other_.m_message_) {
            return false;
        }
        if (m_is_error_ != other_.m_is_error_) {
            return false;
        }
        if (m_timestamp_ != other_.m_timestamp_) {
            return false;
        }
        return true;
    }

    bool ServoFeedback::operator != (const ServoFeedback& other_) const {
        return !this->operator ==(other_);
    }

    std::ostream& operator << (std::ostream& o,const ServoFeedback& sample)
    {
        ::rti::util::StreamFlagSaver flag_saver (o);
        o <<"[";
        o << "feedback_type: " << sample.feedback_type()<<", ";
        o << "connected: " << sample.connected()<<", ";
        o << "current_port: " << sample.current_port()<<", ";
        o << "available_ports: " << sample.available_ports()<<", ";
        o << "found_ids: " << sample.found_ids()<<", ";
        o << "state: " << sample.state()<<", ";
        o << "message: " << sample.message()<<", ";
        o << "is_error: " << sample.is_error()<<", ";
        o << "timestamp: " << sample.timestamp();
        o <<"]";
        return o;
    }

} // namespace scservo  

#ifdef NDDS_STANDALONE_TYPE
namespace rti {
    namespace topic {
    }
}

#else
// --- Type traits: -------------------------------------------------

namespace rti { 
    namespace topic {

        template<>
        struct native_type_code< ::scservo::String64_AliasTag_t > {

            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static std::atomic_bool is_initialized {false};

                static DDS_TypeCode String64_g_tc_string;

                static DDS_TypeCode String64_g_tc =
                {{
                        DDS_TK_ALIAS, /* Kind*/
                        DDS_BOOLEAN_FALSE,/* Is a pointer? */
                        -1, /* Ignored */
                        (char *)"scservo::String64", /* Name */
                        NULL, /* Content type code is assigned later */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for  String64 */

                if (is_initialized.load(std::memory_order_acquire)) {
                    return &String64_g_tc;
                }

                String64_g_tc_string = initialize_string_typecode((64L));

                String64_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                String64_g_tc._data._typeCode =  (RTICdrTypeCode *)&String64_g_tc_string;

                /* Initialize the values for member annotations. */
                String64_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_STRING;
                String64_g_tc._data._annotations._defaultValue._u.string_value = (DDS_Char *) "";

                String64_g_tc._data._sampleAccessInfo = sample_access_info();
                String64_g_tc._data._typePlugin = type_plugin_info();    

                is_initialized.store(true, std::memory_order_release);

                return &String64_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static std::atomic_bool is_initialized {false};

                static RTIXCdrMemberAccessInfo String64_g_memberAccessInfos[1] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo String64_g_sampleAccessInfo = 
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized.load(std::memory_order_acquire)) {
                    return (RTIXCdrSampleAccessInfo*) &String64_g_sampleAccessInfo;
                }

                String64_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

                String64_g_sampleAccessInfo.memberAccessInfos = 
                String64_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(::scservo::String64);

                    if (candidateTypeSize > RTIXCdrLong_MAX) {
                        String64_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrLong_MAX;
                    } else {
                        String64_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                String64_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                String64_g_sampleAccessInfo.getMemberValuePointerFcn = 
                interpreter::get_aggregation_value_pointer< ::scservo::String64 >;

                String64_g_sampleAccessInfo.languageBinding = 
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                is_initialized.store(true, std::memory_order_release);
                return (RTIXCdrSampleAccessInfo*) &String64_g_sampleAccessInfo;
            }
            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin String64_g_typePlugin = 
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &String64_g_typePlugin;
            }
        }; // native_type_code

        const ::dds::core::xtypes::AliasType& dynamic_type< ::scservo::String64_AliasTag_t >::get()
        {
            return static_cast<const ::dds::core::xtypes::AliasType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ::scservo::String64_AliasTag_t >::get())));
        }

        template<>
        struct native_type_code< ::scservo::String256_AliasTag_t > {

            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static std::atomic_bool is_initialized {false};

                static DDS_TypeCode String256_g_tc_string;

                static DDS_TypeCode String256_g_tc =
                {{
                        DDS_TK_ALIAS, /* Kind*/
                        DDS_BOOLEAN_FALSE,/* Is a pointer? */
                        -1, /* Ignored */
                        (char *)"scservo::String256", /* Name */
                        NULL, /* Content type code is assigned later */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for  String256 */

                if (is_initialized.load(std::memory_order_acquire)) {
                    return &String256_g_tc;
                }

                String256_g_tc_string = initialize_string_typecode((256L));

                String256_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                String256_g_tc._data._typeCode =  (RTICdrTypeCode *)&String256_g_tc_string;

                /* Initialize the values for member annotations. */
                String256_g_tc._data._annotations._defaultValue._d = RTI_XCDR_TK_STRING;
                String256_g_tc._data._annotations._defaultValue._u.string_value = (DDS_Char *) "";

                String256_g_tc._data._sampleAccessInfo = sample_access_info();
                String256_g_tc._data._typePlugin = type_plugin_info();    

                is_initialized.store(true, std::memory_order_release);

                return &String256_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static std::atomic_bool is_initialized {false};

                static RTIXCdrMemberAccessInfo String256_g_memberAccessInfos[1] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo String256_g_sampleAccessInfo = 
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized.load(std::memory_order_acquire)) {
                    return (RTIXCdrSampleAccessInfo*) &String256_g_sampleAccessInfo;
                }

                String256_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 0;

                String256_g_sampleAccessInfo.memberAccessInfos = 
                String256_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(::scservo::String256);

                    if (candidateTypeSize > RTIXCdrLong_MAX) {
                        String256_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrLong_MAX;
                    } else {
                        String256_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                String256_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                String256_g_sampleAccessInfo.getMemberValuePointerFcn = 
                interpreter::get_aggregation_value_pointer< ::scservo::String256 >;

                String256_g_sampleAccessInfo.languageBinding = 
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                is_initialized.store(true, std::memory_order_release);
                return (RTIXCdrSampleAccessInfo*) &String256_g_sampleAccessInfo;
            }
            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin String256_g_typePlugin = 
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &String256_g_typePlugin;
            }
        }; // native_type_code

        const ::dds::core::xtypes::AliasType& dynamic_type< ::scservo::String256_AliasTag_t >::get()
        {
            return static_cast<const ::dds::core::xtypes::AliasType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ::scservo::String256_AliasTag_t >::get())));
        }

        template<>
        struct native_type_code< ::scservo::ServoState > {

            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static std::atomic_bool is_initialized {false};

                static DDS_TypeCode_Member ServoState_g_tc_members[7]=
                {

                    {
                        (char *)"id",/* Member name */
                        {
                            0,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"position",/* Member name */
                        {
                            1,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"speed",/* Member name */
                        {
                            2,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"load",/* Member name */
                        {
                            3,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"voltage",/* Member name */
                        {
                            4,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"temperature",/* Member name */
                        {
                            5,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"current",/* Member name */
                        {
                            6,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }
                };

                static DDS_TypeCode ServoState_g_tc =
                {{
                        DDS_TK_STRUCT, /* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"scservo::ServoState", /* Name */
                        NULL, /* Ignored */      
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        7, /* Number of members */
                        ServoState_g_tc_members, /* Members */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for ServoState*/

                if (is_initialized.load(std::memory_order_acquire)) {
                    return &ServoState_g_tc;
                }

                ServoState_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                ServoState_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
                ServoState_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
                ServoState_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
                ServoState_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
                ServoState_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
                ServoState_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
                ServoState_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

                /* Initialize the values for member annotations. */
                ServoState_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[0]._annotations._defaultValue._u.long_value = 0;
                ServoState_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[0]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
                ServoState_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[0]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;
                ServoState_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[1]._annotations._defaultValue._u.long_value = 0;
                ServoState_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[1]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
                ServoState_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[1]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;
                ServoState_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[2]._annotations._defaultValue._u.long_value = 0;
                ServoState_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[2]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
                ServoState_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[2]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;
                ServoState_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[3]._annotations._defaultValue._u.long_value = 0;
                ServoState_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[3]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
                ServoState_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[3]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;
                ServoState_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[4]._annotations._defaultValue._u.long_value = 0;
                ServoState_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[4]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
                ServoState_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[4]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;
                ServoState_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[5]._annotations._defaultValue._u.long_value = 0;
                ServoState_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[5]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
                ServoState_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[5]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;
                ServoState_g_tc_members[6]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[6]._annotations._defaultValue._u.long_value = 0;
                ServoState_g_tc_members[6]._annotations._minValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[6]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
                ServoState_g_tc_members[6]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
                ServoState_g_tc_members[6]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

                ServoState_g_tc._data._sampleAccessInfo = sample_access_info();
                ServoState_g_tc._data._typePlugin = type_plugin_info();    

                is_initialized.store(true, std::memory_order_release);

                return &ServoState_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static std::atomic_bool is_initialized {false};

                ::scservo::ServoState *sample;

                static RTIXCdrMemberAccessInfo ServoState_g_memberAccessInfos[7] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo ServoState_g_sampleAccessInfo = 
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized.load(std::memory_order_acquire)) {
                    return (RTIXCdrSampleAccessInfo*) &ServoState_g_sampleAccessInfo;
                }

                RTIXCdrHeap_allocateStruct(
                    &sample, 
                    ::scservo::ServoState);
                if (sample == NULL) {
                    return NULL;
                }

                ServoState_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->id() - (char *)sample);

                ServoState_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->position() - (char *)sample);

                ServoState_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->speed() - (char *)sample);

                ServoState_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->load() - (char *)sample);

                ServoState_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->voltage() - (char *)sample);

                ServoState_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->temperature() - (char *)sample);

                ServoState_g_memberAccessInfos[6].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->current() - (char *)sample);

                ServoState_g_sampleAccessInfo.memberAccessInfos = 
                ServoState_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(::scservo::ServoState);

                    if (candidateTypeSize > RTIXCdrLong_MAX) {
                        ServoState_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrLong_MAX;
                    } else {
                        ServoState_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                ServoState_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                ServoState_g_sampleAccessInfo.getMemberValuePointerFcn = 
                interpreter::get_aggregation_value_pointer< ::scservo::ServoState >;

                ServoState_g_sampleAccessInfo.languageBinding = 
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                RTIXCdrHeap_freeStruct(sample);
                is_initialized.store(true, std::memory_order_release);
                return (RTIXCdrSampleAccessInfo*) &ServoState_g_sampleAccessInfo;
            }
            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin ServoState_g_typePlugin = 
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &ServoState_g_typePlugin;
            }
        }; // native_type_code

        const ::dds::core::xtypes::StructType& dynamic_type< ::scservo::ServoState >::get()
        {
            return static_cast<const ::dds::core::xtypes::StructType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ::scservo::ServoState >::get())));
        }

        template<>
        struct native_type_code< ::scservo::MemoryVal > {

            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static std::atomic_bool is_initialized {false};

                static DDS_TypeCode_Member MemoryVal_g_tc_members[2]=
                {

                    {
                        (char *)"address",/* Member name */
                        {
                            0,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"value",/* Member name */
                        {
                            1,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }
                };

                static DDS_TypeCode MemoryVal_g_tc =
                {{
                        DDS_TK_STRUCT, /* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"scservo::MemoryVal", /* Name */
                        NULL, /* Ignored */      
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        2, /* Number of members */
                        MemoryVal_g_tc_members, /* Members */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for MemoryVal*/

                if (is_initialized.load(std::memory_order_acquire)) {
                    return &MemoryVal_g_tc;
                }

                MemoryVal_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                MemoryVal_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
                MemoryVal_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;

                /* Initialize the values for member annotations. */
                MemoryVal_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
                MemoryVal_g_tc_members[0]._annotations._defaultValue._u.long_value = 0;
                MemoryVal_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_LONG;
                MemoryVal_g_tc_members[0]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
                MemoryVal_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
                MemoryVal_g_tc_members[0]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;
                MemoryVal_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
                MemoryVal_g_tc_members[1]._annotations._defaultValue._u.long_value = 0;
                MemoryVal_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_LONG;
                MemoryVal_g_tc_members[1]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
                MemoryVal_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
                MemoryVal_g_tc_members[1]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

                MemoryVal_g_tc._data._sampleAccessInfo = sample_access_info();
                MemoryVal_g_tc._data._typePlugin = type_plugin_info();    

                is_initialized.store(true, std::memory_order_release);

                return &MemoryVal_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static std::atomic_bool is_initialized {false};

                ::scservo::MemoryVal *sample;

                static RTIXCdrMemberAccessInfo MemoryVal_g_memberAccessInfos[2] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo MemoryVal_g_sampleAccessInfo = 
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized.load(std::memory_order_acquire)) {
                    return (RTIXCdrSampleAccessInfo*) &MemoryVal_g_sampleAccessInfo;
                }

                RTIXCdrHeap_allocateStruct(
                    &sample, 
                    ::scservo::MemoryVal);
                if (sample == NULL) {
                    return NULL;
                }

                MemoryVal_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->address() - (char *)sample);

                MemoryVal_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->value() - (char *)sample);

                MemoryVal_g_sampleAccessInfo.memberAccessInfos = 
                MemoryVal_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(::scservo::MemoryVal);

                    if (candidateTypeSize > RTIXCdrLong_MAX) {
                        MemoryVal_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrLong_MAX;
                    } else {
                        MemoryVal_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                MemoryVal_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                MemoryVal_g_sampleAccessInfo.getMemberValuePointerFcn = 
                interpreter::get_aggregation_value_pointer< ::scservo::MemoryVal >;

                MemoryVal_g_sampleAccessInfo.languageBinding = 
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                RTIXCdrHeap_freeStruct(sample);
                is_initialized.store(true, std::memory_order_release);
                return (RTIXCdrSampleAccessInfo*) &MemoryVal_g_sampleAccessInfo;
            }
            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin MemoryVal_g_typePlugin = 
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &MemoryVal_g_typePlugin;
            }
        }; // native_type_code

        const ::dds::core::xtypes::StructType& dynamic_type< ::scservo::MemoryVal >::get()
        {
            return static_cast<const ::dds::core::xtypes::StructType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ::scservo::MemoryVal >::get())));
        }

        template<>
        struct native_type_code< ::scservo::ServoCommand > {

            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static std::atomic_bool is_initialized {false};

                static DDS_TypeCode ServoCommand_g_tc_target_ids_sequence;

                static DDS_TypeCode_Member ServoCommand_g_tc_members[12]=
                {

                    {
                        (char *)"command_type",/* Member name */
                        {
                            0,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"port_name",/* Member name */
                        {
                            1,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"baud_rate",/* Member name */
                        {
                            2,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"servo_id",/* Member name */
                        {
                            3,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"target_ids",/* Member name */
                        {
                            4,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"address",/* Member name */
                        {
                            5,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"value",/* Member name */
                        {
                            6,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"size",/* Member name */
                        {
                            7,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"time_ms",/* Member name */
                        {
                            8,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"speed",/* Member name */
                        {
                            9,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"acc",/* Member name */
                        {
                            10,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"timestamp",/* Member name */
                        {
                            11,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }
                };

                static DDS_TypeCode ServoCommand_g_tc =
                {{
                        DDS_TK_STRUCT, /* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"scservo::ServoCommand", /* Name */
                        NULL, /* Ignored */      
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        12, /* Number of members */
                        ServoCommand_g_tc_members, /* Members */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for ServoCommand*/

                if (is_initialized.load(std::memory_order_acquire)) {
                    return &ServoCommand_g_tc;
                }

                ServoCommand_g_tc_target_ids_sequence = initialize_sequence_typecode< ::rti::core::bounded_sequence< int32_t, 100L > >((100L));

                ServoCommand_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                ServoCommand_g_tc_target_ids_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
                ServoCommand_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&::rti::topic::dynamic_type< ::scservo::String64_AliasTag_t>::get().native();
                ServoCommand_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&::rti::topic::dynamic_type< ::scservo::String64_AliasTag_t>::get().native();
                ServoCommand_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
                ServoCommand_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
                ServoCommand_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)& ServoCommand_g_tc_target_ids_sequence;
                ServoCommand_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
                ServoCommand_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
                ServoCommand_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
                ServoCommand_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
                ServoCommand_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
                ServoCommand_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
                ServoCommand_g_tc_members[11]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_longlong;

                /* Initialize the values for member annotations. */
                ServoCommand_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_STRING;
                ServoCommand_g_tc_members[0]._annotations._defaultValue._u.string_value = (DDS_Char *) "";
                ServoCommand_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_STRING;
                ServoCommand_g_tc_members[1]._annotations._defaultValue._u.string_value = (DDS_Char *) "";
                ServoCommand_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[2]._annotations._defaultValue._u.long_value = 0;
                ServoCommand_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[2]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
                ServoCommand_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[2]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;
                ServoCommand_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[3]._annotations._defaultValue._u.long_value = 0;
                ServoCommand_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[3]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
                ServoCommand_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[3]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;
                ServoCommand_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[5]._annotations._defaultValue._u.long_value = 0;
                ServoCommand_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[5]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
                ServoCommand_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[5]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;
                ServoCommand_g_tc_members[6]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[6]._annotations._defaultValue._u.long_value = 0;
                ServoCommand_g_tc_members[6]._annotations._minValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[6]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
                ServoCommand_g_tc_members[6]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[6]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;
                ServoCommand_g_tc_members[7]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[7]._annotations._defaultValue._u.long_value = 0;
                ServoCommand_g_tc_members[7]._annotations._minValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[7]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
                ServoCommand_g_tc_members[7]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[7]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;
                ServoCommand_g_tc_members[8]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[8]._annotations._defaultValue._u.long_value = 0;
                ServoCommand_g_tc_members[8]._annotations._minValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[8]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
                ServoCommand_g_tc_members[8]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[8]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;
                ServoCommand_g_tc_members[9]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[9]._annotations._defaultValue._u.long_value = 0;
                ServoCommand_g_tc_members[9]._annotations._minValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[9]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
                ServoCommand_g_tc_members[9]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[9]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;
                ServoCommand_g_tc_members[10]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[10]._annotations._defaultValue._u.long_value = 0;
                ServoCommand_g_tc_members[10]._annotations._minValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[10]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
                ServoCommand_g_tc_members[10]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
                ServoCommand_g_tc_members[10]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;
                ServoCommand_g_tc_members[11]._annotations._defaultValue._d = RTI_XCDR_TK_LONGLONG;
                ServoCommand_g_tc_members[11]._annotations._defaultValue._u.long_long_value = 0ll;
                ServoCommand_g_tc_members[11]._annotations._minValue._d = RTI_XCDR_TK_LONGLONG;
                ServoCommand_g_tc_members[11]._annotations._minValue._u.long_long_value = RTIXCdrLongLong_MIN;
                ServoCommand_g_tc_members[11]._annotations._maxValue._d = RTI_XCDR_TK_LONGLONG;
                ServoCommand_g_tc_members[11]._annotations._maxValue._u.long_long_value = RTIXCdrLongLong_MAX;

                ServoCommand_g_tc._data._sampleAccessInfo = sample_access_info();
                ServoCommand_g_tc._data._typePlugin = type_plugin_info();    

                is_initialized.store(true, std::memory_order_release);

                return &ServoCommand_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static std::atomic_bool is_initialized {false};

                ::scservo::ServoCommand *sample;

                static RTIXCdrMemberAccessInfo ServoCommand_g_memberAccessInfos[12] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo ServoCommand_g_sampleAccessInfo = 
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized.load(std::memory_order_acquire)) {
                    return (RTIXCdrSampleAccessInfo*) &ServoCommand_g_sampleAccessInfo;
                }

                RTIXCdrHeap_allocateStruct(
                    &sample, 
                    ::scservo::ServoCommand);
                if (sample == NULL) {
                    return NULL;
                }

                ServoCommand_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->command_type() - (char *)sample);

                ServoCommand_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->port_name() - (char *)sample);

                ServoCommand_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->baud_rate() - (char *)sample);

                ServoCommand_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->servo_id() - (char *)sample);

                ServoCommand_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->target_ids() - (char *)sample);

                ServoCommand_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->address() - (char *)sample);

                ServoCommand_g_memberAccessInfos[6].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->value() - (char *)sample);

                ServoCommand_g_memberAccessInfos[7].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->size() - (char *)sample);

                ServoCommand_g_memberAccessInfos[8].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->time_ms() - (char *)sample);

                ServoCommand_g_memberAccessInfos[9].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->speed() - (char *)sample);

                ServoCommand_g_memberAccessInfos[10].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->acc() - (char *)sample);

                ServoCommand_g_memberAccessInfos[11].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->timestamp() - (char *)sample);

                ServoCommand_g_sampleAccessInfo.memberAccessInfos = 
                ServoCommand_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(::scservo::ServoCommand);

                    if (candidateTypeSize > RTIXCdrLong_MAX) {
                        ServoCommand_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrLong_MAX;
                    } else {
                        ServoCommand_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                ServoCommand_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                ServoCommand_g_sampleAccessInfo.getMemberValuePointerFcn = 
                interpreter::get_aggregation_value_pointer< ::scservo::ServoCommand >;

                ServoCommand_g_sampleAccessInfo.languageBinding = 
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                RTIXCdrHeap_freeStruct(sample);
                is_initialized.store(true, std::memory_order_release);
                return (RTIXCdrSampleAccessInfo*) &ServoCommand_g_sampleAccessInfo;
            }
            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin ServoCommand_g_typePlugin = 
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &ServoCommand_g_typePlugin;
            }
        }; // native_type_code

        const ::dds::core::xtypes::StructType& dynamic_type< ::scservo::ServoCommand >::get()
        {
            return static_cast<const ::dds::core::xtypes::StructType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ::scservo::ServoCommand >::get())));
        }

        template<>
        struct native_type_code< ::scservo::ServoFeedback > {

            static DDS_TypeCode * get()
            {
                using namespace ::rti::topic::interpreter;

                static std::atomic_bool is_initialized {false};

                static DDS_TypeCode ServoFeedback_g_tc_available_ports_sequence;
                static DDS_TypeCode ServoFeedback_g_tc_found_ids_sequence;

                static DDS_TypeCode_Member ServoFeedback_g_tc_members[9]=
                {

                    {
                        (char *)"feedback_type",/* Member name */
                        {
                            0,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"connected",/* Member name */
                        {
                            1,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"current_port",/* Member name */
                        {
                            2,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"available_ports",/* Member name */
                        {
                            3,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"found_ids",/* Member name */
                        {
                            4,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"state",/* Member name */
                        {
                            5,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"message",/* Member name */
                        {
                            6,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"is_error",/* Member name */
                        {
                            7,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }, 
                    {
                        (char *)"timestamp",/* Member name */
                        {
                            8,/* Representation ID */
                            DDS_BOOLEAN_FALSE,/* Is a pointer? */
                            -1, /* Bitfield bits */
                            NULL/* Member type code is assigned later */
                        },
                        0, /* Ignored */
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                        DDS_PUBLIC_MEMBER,/* Member visibility */
                        RTICdrTypeCodeAnnotations_INITIALIZER
                    }
                };

                static DDS_TypeCode ServoFeedback_g_tc =
                {{
                        DDS_TK_STRUCT, /* Kind */
                        DDS_BOOLEAN_FALSE, /* Ignored */
                        -1, /*Ignored*/
                        (char *)"scservo::ServoFeedback", /* Name */
                        NULL, /* Ignored */      
                        0, /* Ignored */
                        0, /* Ignored */
                        NULL, /* Ignored */
                        9, /* Number of members */
                        ServoFeedback_g_tc_members, /* Members */
                        DDS_VM_NONE, /* Ignored */
                        RTICdrTypeCodeAnnotations_INITIALIZER,
                        DDS_BOOLEAN_TRUE, /* _isCopyable */
                        NULL, /* _sampleAccessInfo: assigned later */
                        NULL /* _typePlugin: assigned later */
                    }}; /* Type code for ServoFeedback*/

                if (is_initialized.load(std::memory_order_acquire)) {
                    return &ServoFeedback_g_tc;
                }

                ServoFeedback_g_tc_available_ports_sequence = initialize_sequence_typecode< ::rti::core::bounded_sequence< ::scservo::String64, 100L > >((100L));
                ServoFeedback_g_tc_found_ids_sequence = initialize_sequence_typecode< ::rti::core::bounded_sequence< int32_t, 100L > >((100L));

                ServoFeedback_g_tc._data._annotations._allowedDataRepresentationMask = 5;

                ServoFeedback_g_tc_available_ports_sequence._data._typeCode = (RTICdrTypeCode *)&::rti::topic::dynamic_type< ::scservo::String64_AliasTag_t>::get().native();
                ServoFeedback_g_tc_found_ids_sequence._data._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
                ServoFeedback_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&::rti::topic::dynamic_type< ::scservo::String64_AliasTag_t>::get().native();
                ServoFeedback_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&::rti::topic::interpreter::initialize_bool_typecode();
                ServoFeedback_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&::rti::topic::dynamic_type< ::scservo::String64_AliasTag_t>::get().native();
                ServoFeedback_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)& ServoFeedback_g_tc_available_ports_sequence;
                ServoFeedback_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)& ServoFeedback_g_tc_found_ids_sequence;
                ServoFeedback_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)&::rti::topic::dynamic_type< ::scservo::ServoState>::get().native();
                ServoFeedback_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)&::rti::topic::dynamic_type< ::scservo::String256_AliasTag_t>::get().native();
                ServoFeedback_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)&::rti::topic::interpreter::initialize_bool_typecode();
                ServoFeedback_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_longlong;

                /* Initialize the values for member annotations. */
                ServoFeedback_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_STRING;
                ServoFeedback_g_tc_members[0]._annotations._defaultValue._u.string_value = (DDS_Char *) "";
                ServoFeedback_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_BOOLEAN;
                ServoFeedback_g_tc_members[1]._annotations._defaultValue._u.boolean_value = 0;
                ServoFeedback_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_STRING;
                ServoFeedback_g_tc_members[2]._annotations._defaultValue._u.string_value = (DDS_Char *) "";
                ServoFeedback_g_tc_members[6]._annotations._defaultValue._d = RTI_XCDR_TK_STRING;
                ServoFeedback_g_tc_members[6]._annotations._defaultValue._u.string_value = (DDS_Char *) "";
                ServoFeedback_g_tc_members[7]._annotations._defaultValue._d = RTI_XCDR_TK_BOOLEAN;
                ServoFeedback_g_tc_members[7]._annotations._defaultValue._u.boolean_value = 0;
                ServoFeedback_g_tc_members[8]._annotations._defaultValue._d = RTI_XCDR_TK_LONGLONG;
                ServoFeedback_g_tc_members[8]._annotations._defaultValue._u.long_long_value = 0ll;
                ServoFeedback_g_tc_members[8]._annotations._minValue._d = RTI_XCDR_TK_LONGLONG;
                ServoFeedback_g_tc_members[8]._annotations._minValue._u.long_long_value = RTIXCdrLongLong_MIN;
                ServoFeedback_g_tc_members[8]._annotations._maxValue._d = RTI_XCDR_TK_LONGLONG;
                ServoFeedback_g_tc_members[8]._annotations._maxValue._u.long_long_value = RTIXCdrLongLong_MAX;

                ServoFeedback_g_tc._data._sampleAccessInfo = sample_access_info();
                ServoFeedback_g_tc._data._typePlugin = type_plugin_info();    

                is_initialized.store(true, std::memory_order_release);

                return &ServoFeedback_g_tc;
            }

            static RTIXCdrSampleAccessInfo * sample_access_info()
            {
                static std::atomic_bool is_initialized {false};

                ::scservo::ServoFeedback *sample;

                static RTIXCdrMemberAccessInfo ServoFeedback_g_memberAccessInfos[9] =
                {RTIXCdrMemberAccessInfo_INITIALIZER};

                static RTIXCdrSampleAccessInfo ServoFeedback_g_sampleAccessInfo = 
                RTIXCdrSampleAccessInfo_INITIALIZER;

                if (is_initialized.load(std::memory_order_acquire)) {
                    return (RTIXCdrSampleAccessInfo*) &ServoFeedback_g_sampleAccessInfo;
                }

                RTIXCdrHeap_allocateStruct(
                    &sample, 
                    ::scservo::ServoFeedback);
                if (sample == NULL) {
                    return NULL;
                }

                ServoFeedback_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->feedback_type() - (char *)sample);

                ServoFeedback_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->connected() - (char *)sample);

                ServoFeedback_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->current_port() - (char *)sample);

                ServoFeedback_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->available_ports() - (char *)sample);

                ServoFeedback_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->found_ids() - (char *)sample);

                ServoFeedback_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->state() - (char *)sample);

                ServoFeedback_g_memberAccessInfos[6].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->message() - (char *)sample);

                ServoFeedback_g_memberAccessInfos[7].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->is_error() - (char *)sample);

                ServoFeedback_g_memberAccessInfos[8].bindingMemberValueOffset[0] = 
                (RTIXCdrUnsignedLong) ((char *)&sample->timestamp() - (char *)sample);

                ServoFeedback_g_sampleAccessInfo.memberAccessInfos = 
                ServoFeedback_g_memberAccessInfos;

                {
                    size_t candidateTypeSize = sizeof(::scservo::ServoFeedback);

                    if (candidateTypeSize > RTIXCdrLong_MAX) {
                        ServoFeedback_g_sampleAccessInfo.typeSize[0] =
                        RTIXCdrLong_MAX;
                    } else {
                        ServoFeedback_g_sampleAccessInfo.typeSize[0] =
                        (RTIXCdrUnsignedLong) candidateTypeSize;
                    }
                }

                ServoFeedback_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
                RTI_XCDR_TRUE;

                ServoFeedback_g_sampleAccessInfo.getMemberValuePointerFcn = 
                interpreter::get_aggregation_value_pointer< ::scservo::ServoFeedback >;

                ServoFeedback_g_sampleAccessInfo.languageBinding = 
                RTI_XCDR_TYPE_BINDING_CPP_11_STL ;

                RTIXCdrHeap_freeStruct(sample);
                is_initialized.store(true, std::memory_order_release);
                return (RTIXCdrSampleAccessInfo*) &ServoFeedback_g_sampleAccessInfo;
            }
            static RTIXCdrTypePlugin * type_plugin_info()
            {
                static RTIXCdrTypePlugin ServoFeedback_g_typePlugin = 
                {
                    NULL, /* serialize */
                    NULL, /* serialize_key */
                    NULL, /* deserialize_sample */
                    NULL, /* deserialize_key_sample */
                    NULL, /* skip */
                    NULL, /* get_serialized_sample_size */
                    NULL, /* get_serialized_sample_max_size_ex */
                    NULL, /* get_serialized_key_max_size_ex */
                    NULL, /* get_serialized_sample_min_size */
                    NULL, /* serialized_sample_to_key */
                    NULL,
                    NULL,
                    NULL,
                    NULL,
                    NULL
                };

                return &ServoFeedback_g_typePlugin;
            }
        }; // native_type_code

        const ::dds::core::xtypes::StructType& dynamic_type< ::scservo::ServoFeedback >::get()
        {
            return static_cast<const ::dds::core::xtypes::StructType&>(
                ::rti::core::native_conversions::cast_from_native< ::dds::core::xtypes::DynamicType >(
                    *(native_type_code< ::scservo::ServoFeedback >::get())));
        }
    }
}

namespace dds { 
    namespace topic {
        void topic_type_support< ::scservo::ServoState >:: register_type(
            ::dds::domain::DomainParticipant& participant,
            const std::string& type_name) 
        {

            ::rti::domain::register_type_plugin(
                participant,
                type_name,
                ::scservo::ServoStatePlugin_new,
                ::scservo::ServoStatePlugin_delete);
        }

        std::vector<char>& topic_type_support< ::scservo::ServoState >::to_cdr_buffer(
            std::vector<char>& buffer, 
            const ::scservo::ServoState& sample,
            ::dds::core::policy::DataRepresentationId representation)
        {
            // First get the length of the buffer
            unsigned int length = 0;
            RTIBool ok = ServoStatePlugin_serialize_to_cdr_buffer(
                NULL, 
                &length,
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to calculate cdr buffer size");

            // Create a vector with that size and copy the cdr buffer into it
            buffer.resize(length);
            ok = ServoStatePlugin_serialize_to_cdr_buffer(
                &buffer[0], 
                &length, 
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to copy cdr buffer");

            return buffer;
        }

        void topic_type_support< ::scservo::ServoState >::from_cdr_buffer(::scservo::ServoState& sample, 
        const std::vector<char>& buffer)
        {

            RTIBool ok  = ServoStatePlugin_deserialize_from_cdr_buffer(
                &sample, 
                &buffer[0], 
                static_cast<unsigned int>(buffer.size()));
            ::rti::core::check_return_code(ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
            "Failed to create ::scservo::ServoState from cdr buffer");
        }

        void topic_type_support< ::scservo::ServoState >::reset_sample(::scservo::ServoState& sample) 
        {
            sample.id(0);
            sample.position(0);
            sample.speed(0);
            sample.load(0);
            sample.voltage(0);
            sample.temperature(0);
            sample.current(0);
        }

        void topic_type_support< ::scservo::ServoState >::allocate_sample(::scservo::ServoState& sample, int, int) 
        {
            RTIOsapiUtility_unusedParameter(sample);
        }
        void topic_type_support< ::scservo::MemoryVal >:: register_type(
            ::dds::domain::DomainParticipant& participant,
            const std::string& type_name) 
        {

            ::rti::domain::register_type_plugin(
                participant,
                type_name,
                ::scservo::MemoryValPlugin_new,
                ::scservo::MemoryValPlugin_delete);
        }

        std::vector<char>& topic_type_support< ::scservo::MemoryVal >::to_cdr_buffer(
            std::vector<char>& buffer, 
            const ::scservo::MemoryVal& sample,
            ::dds::core::policy::DataRepresentationId representation)
        {
            // First get the length of the buffer
            unsigned int length = 0;
            RTIBool ok = MemoryValPlugin_serialize_to_cdr_buffer(
                NULL, 
                &length,
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to calculate cdr buffer size");

            // Create a vector with that size and copy the cdr buffer into it
            buffer.resize(length);
            ok = MemoryValPlugin_serialize_to_cdr_buffer(
                &buffer[0], 
                &length, 
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to copy cdr buffer");

            return buffer;
        }

        void topic_type_support< ::scservo::MemoryVal >::from_cdr_buffer(::scservo::MemoryVal& sample, 
        const std::vector<char>& buffer)
        {

            RTIBool ok  = MemoryValPlugin_deserialize_from_cdr_buffer(
                &sample, 
                &buffer[0], 
                static_cast<unsigned int>(buffer.size()));
            ::rti::core::check_return_code(ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
            "Failed to create ::scservo::MemoryVal from cdr buffer");
        }

        void topic_type_support< ::scservo::MemoryVal >::reset_sample(::scservo::MemoryVal& sample) 
        {
            sample.address(0);
            sample.value(0);
        }

        void topic_type_support< ::scservo::MemoryVal >::allocate_sample(::scservo::MemoryVal& sample, int, int) 
        {
            RTIOsapiUtility_unusedParameter(sample);
        }
        void topic_type_support< ::scservo::ServoCommand >:: register_type(
            ::dds::domain::DomainParticipant& participant,
            const std::string& type_name) 
        {

            ::rti::domain::register_type_plugin(
                participant,
                type_name,
                ::scservo::ServoCommandPlugin_new,
                ::scservo::ServoCommandPlugin_delete);
        }

        std::vector<char>& topic_type_support< ::scservo::ServoCommand >::to_cdr_buffer(
            std::vector<char>& buffer, 
            const ::scservo::ServoCommand& sample,
            ::dds::core::policy::DataRepresentationId representation)
        {
            // First get the length of the buffer
            unsigned int length = 0;
            RTIBool ok = ServoCommandPlugin_serialize_to_cdr_buffer(
                NULL, 
                &length,
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to calculate cdr buffer size");

            // Create a vector with that size and copy the cdr buffer into it
            buffer.resize(length);
            ok = ServoCommandPlugin_serialize_to_cdr_buffer(
                &buffer[0], 
                &length, 
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to copy cdr buffer");

            return buffer;
        }

        void topic_type_support< ::scservo::ServoCommand >::from_cdr_buffer(::scservo::ServoCommand& sample, 
        const std::vector<char>& buffer)
        {

            RTIBool ok  = ServoCommandPlugin_deserialize_from_cdr_buffer(
                &sample, 
                &buffer[0], 
                static_cast<unsigned int>(buffer.size()));
            ::rti::core::check_return_code(ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
            "Failed to create ::scservo::ServoCommand from cdr buffer");
        }

        void topic_type_support< ::scservo::ServoCommand >::reset_sample(::scservo::ServoCommand& sample) 
        {
            sample.command_type("");
            sample.port_name("");
            sample.baud_rate(0);
            sample.servo_id(0);
            ::rti::topic::reset_sample(sample.target_ids());
            sample.address(0);
            sample.value(0);
            sample.size(0);
            sample.time_ms(0);
            sample.speed(0);
            sample.acc(0);
            sample.timestamp(0ll);
        }

        void topic_type_support< ::scservo::ServoCommand >::allocate_sample(::scservo::ServoCommand& sample, int, int) 
        {
            ::rti::topic::allocate_sample(sample.command_type(),  -1, 64L);
            ::rti::topic::allocate_sample(sample.port_name(),  -1, 64L);
            ::rti::topic::allocate_sample(sample.target_ids(),  100L, -1);
        }
        void topic_type_support< ::scservo::ServoFeedback >:: register_type(
            ::dds::domain::DomainParticipant& participant,
            const std::string& type_name) 
        {

            ::rti::domain::register_type_plugin(
                participant,
                type_name,
                ::scservo::ServoFeedbackPlugin_new,
                ::scservo::ServoFeedbackPlugin_delete);
        }

        std::vector<char>& topic_type_support< ::scservo::ServoFeedback >::to_cdr_buffer(
            std::vector<char>& buffer, 
            const ::scservo::ServoFeedback& sample,
            ::dds::core::policy::DataRepresentationId representation)
        {
            // First get the length of the buffer
            unsigned int length = 0;
            RTIBool ok = ServoFeedbackPlugin_serialize_to_cdr_buffer(
                NULL, 
                &length,
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to calculate cdr buffer size");

            // Create a vector with that size and copy the cdr buffer into it
            buffer.resize(length);
            ok = ServoFeedbackPlugin_serialize_to_cdr_buffer(
                &buffer[0], 
                &length, 
                &sample,
                representation);
            ::rti::core::check_return_code(
                ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
                "Failed to copy cdr buffer");

            return buffer;
        }

        void topic_type_support< ::scservo::ServoFeedback >::from_cdr_buffer(::scservo::ServoFeedback& sample, 
        const std::vector<char>& buffer)
        {

            RTIBool ok  = ServoFeedbackPlugin_deserialize_from_cdr_buffer(
                &sample, 
                &buffer[0], 
                static_cast<unsigned int>(buffer.size()));
            ::rti::core::check_return_code(ok ? DDS_RETCODE_OK : DDS_RETCODE_ERROR,
            "Failed to create ::scservo::ServoFeedback from cdr buffer");
        }

        void topic_type_support< ::scservo::ServoFeedback >::reset_sample(::scservo::ServoFeedback& sample) 
        {
            sample.feedback_type("");
            sample.connected(0);
            sample.current_port("");
            ::rti::topic::reset_sample(sample.available_ports());
            ::rti::topic::reset_sample(sample.found_ids());
            ::rti::topic::reset_sample(sample.state());
            sample.message("");
            sample.is_error(0);
            sample.timestamp(0ll);
        }

        void topic_type_support< ::scservo::ServoFeedback >::allocate_sample(::scservo::ServoFeedback& sample, int, int) 
        {
            ::rti::topic::allocate_sample(sample.feedback_type(),  -1, 64L);
            ::rti::topic::allocate_sample(sample.current_port(),  -1, 64L);
            ::rti::topic::allocate_sample(sample.available_ports(),  100L, 64L);
            ::rti::topic::allocate_sample(sample.found_ids(),  100L, -1);
            ::rti::topic::allocate_sample(sample.state(),  -1, -1);
            ::rti::topic::allocate_sample(sample.message(),  -1, 256L);
        }
    }
}  

#endif // NDDS_STANDALONE_TYPE
