

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from scservo.idl
using RTI Code Generator (rtiddsgen) version 4.5.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#ifndef scservo_1338806988_hpp
#define scservo_1338806988_hpp

#include <iosfwd>

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef RTIUSERDllExport
#define RTIUSERDllExport __declspec(dllexport)
#endif

#include "dds/core/SafeEnumeration.hpp"
#include "dds/core/String.hpp"
#include "dds/core/array.hpp"
#include "dds/core/vector.hpp"
#include "dds/core/External.hpp"
#include "rti/core/LongDouble.hpp"
#include "rti/core/Pointer.hpp"
#include "rti/core/array.hpp"
#include "rti/topic/TopicTraits.hpp"

#include "omg/types/string_view.hpp"

#include "rti/core/BoundedSequence.hpp"
#include "dds/core/Optional.hpp"

#ifndef NDDS_STANDALONE_TYPE
#include "cdr/cdr_typeCode.h"
#include "dds/domain/DomainParticipant.hpp"
#include "dds/topic/TopicTraits.hpp"
#include "dds/core/xtypes/DynamicType.hpp"
#include "dds/core/xtypes/StructType.hpp"
#include "dds/core/xtypes/UnionType.hpp"
#include "dds/core/xtypes/EnumType.hpp"
#include "dds/core/xtypes/AliasType.hpp"
#include "rti/util/StreamFlagSaver.hpp"
#include "rti/domain/PluginSupport.hpp"
#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef RTIUSERDllExport
#define RTIUSERDllExport
#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

namespace scservo {

    typedef std::string String64;
    struct String64_AliasTag_t {};

    typedef std::string String256;
    struct String256_AliasTag_t {};

    class NDDSUSERDllExport ServoState {
      public:

        ServoState();

        ServoState(int32_t id_,int32_t position_,int32_t speed_,int32_t load_,int32_t voltage_,int32_t temperature_,int32_t current_);

        int32_t& id() noexcept {
            return m_id_;
        }

        const int32_t& id() const noexcept {
            return m_id_;
        }

        void id(int32_t value) {

            m_id_ = value;
        }

        int32_t& position() noexcept {
            return m_position_;
        }

        const int32_t& position() const noexcept {
            return m_position_;
        }

        void position(int32_t value) {

            m_position_ = value;
        }

        int32_t& speed() noexcept {
            return m_speed_;
        }

        const int32_t& speed() const noexcept {
            return m_speed_;
        }

        void speed(int32_t value) {

            m_speed_ = value;
        }

        int32_t& load() noexcept {
            return m_load_;
        }

        const int32_t& load() const noexcept {
            return m_load_;
        }

        void load(int32_t value) {

            m_load_ = value;
        }

        int32_t& voltage() noexcept {
            return m_voltage_;
        }

        const int32_t& voltage() const noexcept {
            return m_voltage_;
        }

        void voltage(int32_t value) {

            m_voltage_ = value;
        }

        int32_t& temperature() noexcept {
            return m_temperature_;
        }

        const int32_t& temperature() const noexcept {
            return m_temperature_;
        }

        void temperature(int32_t value) {

            m_temperature_ = value;
        }

        int32_t& current() noexcept {
            return m_current_;
        }

        const int32_t& current() const noexcept {
            return m_current_;
        }

        void current(int32_t value) {

            m_current_ = value;
        }

        bool operator == (const ServoState& other_) const;
        bool operator != (const ServoState& other_) const;

        void swap(ServoState& other_) noexcept ;

      private:

        int32_t m_id_;
        int32_t m_position_;
        int32_t m_speed_;
        int32_t m_load_;
        int32_t m_voltage_;
        int32_t m_temperature_;
        int32_t m_current_;

    };

    inline void swap(ServoState& a, ServoState& b)  noexcept 
    {
        a.swap(b);
    }

    NDDSUSERDllExport std::ostream& operator<<(std::ostream& o, const ServoState& sample);

    class NDDSUSERDllExport MemoryVal {
      public:

        MemoryVal();

        MemoryVal(int32_t address_,int32_t value_);

        int32_t& address() noexcept {
            return m_address_;
        }

        const int32_t& address() const noexcept {
            return m_address_;
        }

        void address(int32_t value) {

            m_address_ = value;
        }

        int32_t& value() noexcept {
            return m_value_;
        }

        const int32_t& value() const noexcept {
            return m_value_;
        }

        void value(int32_t value) {

            m_value_ = value;
        }

        bool operator == (const MemoryVal& other_) const;
        bool operator != (const MemoryVal& other_) const;

        void swap(MemoryVal& other_) noexcept ;

      private:

        int32_t m_address_;
        int32_t m_value_;

    };

    inline void swap(MemoryVal& a, MemoryVal& b)  noexcept 
    {
        a.swap(b);
    }

    NDDSUSERDllExport std::ostream& operator<<(std::ostream& o, const MemoryVal& sample);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    // On Windows, dll-export template instantiations of standard types used by
    // other dll-exported types
    template class NDDSUSERDllExport std::allocator< int32_t >;
    template class NDDSUSERDllExport std::vector< int32_t >;
    #endif
    class NDDSUSERDllExport ServoCommand {
      public:

        ServoCommand();

        ServoCommand(const std::string& command_type_,const std::string& port_name_,int32_t baud_rate_,int32_t servo_id_,const ::rti::core::bounded_sequence< int32_t, 100L >& target_ids_,int32_t address_,int32_t value_,int32_t size_,int32_t time_ms_,int32_t speed_,int32_t acc_,int64_t timestamp_);

        std::string& command_type() noexcept {
            return m_command_type_;
        }

        const std::string& command_type() const noexcept {
            return m_command_type_;
        }

        void command_type(const std::string& value) {

            m_command_type_ = value;
        }

        void command_type(std::string&& value) {
            m_command_type_ = std::move(value);
        }
        std::string& port_name() noexcept {
            return m_port_name_;
        }

        const std::string& port_name() const noexcept {
            return m_port_name_;
        }

        void port_name(const std::string& value) {

            m_port_name_ = value;
        }

        void port_name(std::string&& value) {
            m_port_name_ = std::move(value);
        }
        int32_t& baud_rate() noexcept {
            return m_baud_rate_;
        }

        const int32_t& baud_rate() const noexcept {
            return m_baud_rate_;
        }

        void baud_rate(int32_t value) {

            m_baud_rate_ = value;
        }

        int32_t& servo_id() noexcept {
            return m_servo_id_;
        }

        const int32_t& servo_id() const noexcept {
            return m_servo_id_;
        }

        void servo_id(int32_t value) {

            m_servo_id_ = value;
        }

        ::rti::core::bounded_sequence< int32_t, 100L >& target_ids() noexcept {
            return m_target_ids_;
        }

        const ::rti::core::bounded_sequence< int32_t, 100L >& target_ids() const noexcept {
            return m_target_ids_;
        }

        void target_ids(const ::rti::core::bounded_sequence< int32_t, 100L >& value) {

            m_target_ids_ = value;
        }

        void target_ids(::rti::core::bounded_sequence< int32_t, 100L >&& value) {
            m_target_ids_ = std::move(value);
        }
        int32_t& address() noexcept {
            return m_address_;
        }

        const int32_t& address() const noexcept {
            return m_address_;
        }

        void address(int32_t value) {

            m_address_ = value;
        }

        int32_t& value() noexcept {
            return m_value_;
        }

        const int32_t& value() const noexcept {
            return m_value_;
        }

        void value(int32_t value) {

            m_value_ = value;
        }

        int32_t& size() noexcept {
            return m_size_;
        }

        const int32_t& size() const noexcept {
            return m_size_;
        }

        void size(int32_t value) {

            m_size_ = value;
        }

        int32_t& time_ms() noexcept {
            return m_time_ms_;
        }

        const int32_t& time_ms() const noexcept {
            return m_time_ms_;
        }

        void time_ms(int32_t value) {

            m_time_ms_ = value;
        }

        int32_t& speed() noexcept {
            return m_speed_;
        }

        const int32_t& speed() const noexcept {
            return m_speed_;
        }

        void speed(int32_t value) {

            m_speed_ = value;
        }

        int32_t& acc() noexcept {
            return m_acc_;
        }

        const int32_t& acc() const noexcept {
            return m_acc_;
        }

        void acc(int32_t value) {

            m_acc_ = value;
        }

        int64_t& timestamp() noexcept {
            return m_timestamp_;
        }

        const int64_t& timestamp() const noexcept {
            return m_timestamp_;
        }

        void timestamp(int64_t value) {

            m_timestamp_ = value;
        }

        bool operator == (const ServoCommand& other_) const;
        bool operator != (const ServoCommand& other_) const;

        void swap(ServoCommand& other_) noexcept ;

      private:

        std::string m_command_type_;
        std::string m_port_name_;
        int32_t m_baud_rate_;
        int32_t m_servo_id_;
        ::rti::core::bounded_sequence< int32_t, 100L > m_target_ids_;
        int32_t m_address_;
        int32_t m_value_;
        int32_t m_size_;
        int32_t m_time_ms_;
        int32_t m_speed_;
        int32_t m_acc_;
        int64_t m_timestamp_;

    };

    inline void swap(ServoCommand& a, ServoCommand& b)  noexcept 
    {
        a.swap(b);
    }

    NDDSUSERDllExport std::ostream& operator<<(std::ostream& o, const ServoCommand& sample);

    #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    // On Windows, dll-export template instantiations of standard types used by
    // other dll-exported types
    template class NDDSUSERDllExport std::allocator< ::scservo::String64 >;
    template class NDDSUSERDllExport std::vector< ::scservo::String64 >;
    #endif
    class NDDSUSERDllExport ServoFeedback {
      public:

        ServoFeedback();

        ServoFeedback(const std::string& feedback_type_,bool connected_,const std::string& current_port_,const ::rti::core::bounded_sequence< ::scservo::String64, 100L >& available_ports_,const ::rti::core::bounded_sequence< int32_t, 100L >& found_ids_,const ::scservo::ServoState& state_,const std::string& message_,bool is_error_,int64_t timestamp_);

        std::string& feedback_type() noexcept {
            return m_feedback_type_;
        }

        const std::string& feedback_type() const noexcept {
            return m_feedback_type_;
        }

        void feedback_type(const std::string& value) {

            m_feedback_type_ = value;
        }

        void feedback_type(std::string&& value) {
            m_feedback_type_ = std::move(value);
        }
        bool& connected() noexcept {
            return m_connected_;
        }

        const bool& connected() const noexcept {
            return m_connected_;
        }

        void connected(bool value) {

            m_connected_ = value;
        }

        std::string& current_port() noexcept {
            return m_current_port_;
        }

        const std::string& current_port() const noexcept {
            return m_current_port_;
        }

        void current_port(const std::string& value) {

            m_current_port_ = value;
        }

        void current_port(std::string&& value) {
            m_current_port_ = std::move(value);
        }
        ::rti::core::bounded_sequence< ::scservo::String64, 100L >& available_ports() noexcept {
            return m_available_ports_;
        }

        const ::rti::core::bounded_sequence< ::scservo::String64, 100L >& available_ports() const noexcept {
            return m_available_ports_;
        }

        void available_ports(const ::rti::core::bounded_sequence< ::scservo::String64, 100L >& value) {

            m_available_ports_ = value;
        }

        void available_ports(::rti::core::bounded_sequence< ::scservo::String64, 100L >&& value) {
            m_available_ports_ = std::move(value);
        }
        ::rti::core::bounded_sequence< int32_t, 100L >& found_ids() noexcept {
            return m_found_ids_;
        }

        const ::rti::core::bounded_sequence< int32_t, 100L >& found_ids() const noexcept {
            return m_found_ids_;
        }

        void found_ids(const ::rti::core::bounded_sequence< int32_t, 100L >& value) {

            m_found_ids_ = value;
        }

        void found_ids(::rti::core::bounded_sequence< int32_t, 100L >&& value) {
            m_found_ids_ = std::move(value);
        }
        ::scservo::ServoState& state() noexcept {
            return m_state_;
        }

        const ::scservo::ServoState& state() const noexcept {
            return m_state_;
        }

        void state(const ::scservo::ServoState& value) {

            m_state_ = value;
        }

        void state(::scservo::ServoState&& value) {
            m_state_ = std::move(value);
        }
        std::string& message() noexcept {
            return m_message_;
        }

        const std::string& message() const noexcept {
            return m_message_;
        }

        void message(const std::string& value) {

            m_message_ = value;
        }

        void message(std::string&& value) {
            m_message_ = std::move(value);
        }
        bool& is_error() noexcept {
            return m_is_error_;
        }

        const bool& is_error() const noexcept {
            return m_is_error_;
        }

        void is_error(bool value) {

            m_is_error_ = value;
        }

        int64_t& timestamp() noexcept {
            return m_timestamp_;
        }

        const int64_t& timestamp() const noexcept {
            return m_timestamp_;
        }

        void timestamp(int64_t value) {

            m_timestamp_ = value;
        }

        bool operator == (const ServoFeedback& other_) const;
        bool operator != (const ServoFeedback& other_) const;

        void swap(ServoFeedback& other_) noexcept ;

      private:

        std::string m_feedback_type_;
        bool m_connected_;
        std::string m_current_port_;
        ::rti::core::bounded_sequence< ::scservo::String64, 100L > m_available_ports_;
        ::rti::core::bounded_sequence< int32_t, 100L > m_found_ids_;
        ::scservo::ServoState m_state_;
        std::string m_message_;
        bool m_is_error_;
        int64_t m_timestamp_;

    };

    inline void swap(ServoFeedback& a, ServoFeedback& b)  noexcept 
    {
        a.swap(b);
    }

    NDDSUSERDllExport std::ostream& operator<<(std::ostream& o, const ServoFeedback& sample);

} // namespace scservo  

#ifdef NDDS_STANDALONE_TYPE
namespace rti { 
    namespace topic {
    }
}
#else

namespace rti {
    namespace flat {
        namespace topic {
        }
    }
}
namespace dds {
    namespace topic {

        template<>
        struct topic_type_name< ::scservo::ServoState > {
            NDDSUSERDllExport static std::string value() {
                return "scservo::ServoState";
            }
        };

        template<>
        struct is_topic_type< ::scservo::ServoState > : public ::dds::core::true_type {};

        template<>
        struct topic_type_support< ::scservo::ServoState > {
            NDDSUSERDllExport 
            static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);

            NDDSUSERDllExport 
            static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer, 
                const ::scservo::ServoState& sample,
                ::dds::core::policy::DataRepresentationId representation 
                = ::dds::core::policy::DataRepresentation::auto_id());

            NDDSUSERDllExport 
            static void from_cdr_buffer(::scservo::ServoState& sample, const std::vector<char>& buffer);
            NDDSUSERDllExport 
            static void reset_sample(::scservo::ServoState& sample);

            NDDSUSERDllExport 
            static void allocate_sample(::scservo::ServoState& sample, int, int);

            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::STL;
        };
        template<>
        struct topic_type_name< ::scservo::MemoryVal > {
            NDDSUSERDllExport static std::string value() {
                return "scservo::MemoryVal";
            }
        };

        template<>
        struct is_topic_type< ::scservo::MemoryVal > : public ::dds::core::true_type {};

        template<>
        struct topic_type_support< ::scservo::MemoryVal > {
            NDDSUSERDllExport 
            static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);

            NDDSUSERDllExport 
            static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer, 
                const ::scservo::MemoryVal& sample,
                ::dds::core::policy::DataRepresentationId representation 
                = ::dds::core::policy::DataRepresentation::auto_id());

            NDDSUSERDllExport 
            static void from_cdr_buffer(::scservo::MemoryVal& sample, const std::vector<char>& buffer);
            NDDSUSERDllExport 
            static void reset_sample(::scservo::MemoryVal& sample);

            NDDSUSERDllExport 
            static void allocate_sample(::scservo::MemoryVal& sample, int, int);

            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::STL;
        };
        template<>
        struct topic_type_name< ::scservo::ServoCommand > {
            NDDSUSERDllExport static std::string value() {
                return "scservo::ServoCommand";
            }
        };

        template<>
        struct is_topic_type< ::scservo::ServoCommand > : public ::dds::core::true_type {};

        template<>
        struct topic_type_support< ::scservo::ServoCommand > {
            NDDSUSERDllExport 
            static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);

            NDDSUSERDllExport 
            static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer, 
                const ::scservo::ServoCommand& sample,
                ::dds::core::policy::DataRepresentationId representation 
                = ::dds::core::policy::DataRepresentation::auto_id());

            NDDSUSERDllExport 
            static void from_cdr_buffer(::scservo::ServoCommand& sample, const std::vector<char>& buffer);
            NDDSUSERDllExport 
            static void reset_sample(::scservo::ServoCommand& sample);

            NDDSUSERDllExport 
            static void allocate_sample(::scservo::ServoCommand& sample, int, int);

            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::STL;
        };
        template<>
        struct topic_type_name< ::scservo::ServoFeedback > {
            NDDSUSERDllExport static std::string value() {
                return "scservo::ServoFeedback";
            }
        };

        template<>
        struct is_topic_type< ::scservo::ServoFeedback > : public ::dds::core::true_type {};

        template<>
        struct topic_type_support< ::scservo::ServoFeedback > {
            NDDSUSERDllExport 
            static void register_type(
                ::dds::domain::DomainParticipant& participant,
                const std::string & type_name);

            NDDSUSERDllExport 
            static std::vector<char>& to_cdr_buffer(
                std::vector<char>& buffer, 
                const ::scservo::ServoFeedback& sample,
                ::dds::core::policy::DataRepresentationId representation 
                = ::dds::core::policy::DataRepresentation::auto_id());

            NDDSUSERDllExport 
            static void from_cdr_buffer(::scservo::ServoFeedback& sample, const std::vector<char>& buffer);
            NDDSUSERDllExport 
            static void reset_sample(::scservo::ServoFeedback& sample);

            NDDSUSERDllExport 
            static void allocate_sample(::scservo::ServoFeedback& sample, int, int);

            static const ::rti::topic::TypePluginKind::type type_plugin_kind = 
            ::rti::topic::TypePluginKind::STL;
        };
    }
}

namespace rti { 
    namespace topic {

        template<>
        struct dynamic_type< ::scservo::String64_AliasTag_t > {
            typedef ::dds::core::xtypes::AliasType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::AliasType& get();
        };

        template<>
        struct dynamic_type< ::scservo::String256_AliasTag_t > {
            typedef ::dds::core::xtypes::AliasType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::AliasType& get();
        };

        template<>
        struct dynamic_type< ::scservo::ServoState > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };

        template <>
        struct extensibility< ::scservo::ServoState > {
            static const ::dds::core::xtypes::ExtensibilityKind::type kind =
            ::dds::core::xtypes::ExtensibilityKind::EXTENSIBLE;    };

        template<>
        struct dynamic_type< ::scservo::MemoryVal > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };

        template <>
        struct extensibility< ::scservo::MemoryVal > {
            static const ::dds::core::xtypes::ExtensibilityKind::type kind =
            ::dds::core::xtypes::ExtensibilityKind::EXTENSIBLE;    };

        template<>
        struct dynamic_type< ::scservo::ServoCommand > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };

        template <>
        struct extensibility< ::scservo::ServoCommand > {
            static const ::dds::core::xtypes::ExtensibilityKind::type kind =
            ::dds::core::xtypes::ExtensibilityKind::EXTENSIBLE;    };

        template<>
        struct dynamic_type< ::scservo::ServoFeedback > {
            typedef ::dds::core::xtypes::StructType type;
            NDDSUSERDllExport static const ::dds::core::xtypes::StructType& get();
        };

        template <>
        struct extensibility< ::scservo::ServoFeedback > {
            static const ::dds::core::xtypes::ExtensibilityKind::type kind =
            ::dds::core::xtypes::ExtensibilityKind::EXTENSIBLE;    };

    }
}

#endif // NDDS_STANDALONE_TYPE
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif // scservo_1338806988_hpp
