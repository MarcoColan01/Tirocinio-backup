//
// Generated file, do not edit! Created by opp_msgtool 6.0 from apps/packets/VehicleControlPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "VehicleControlPacket_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(VehicleControlPacket)

VehicleControlPacket::VehicleControlPacket() : ::MECPacket()
{
}

VehicleControlPacket::VehicleControlPacket(const VehicleControlPacket& other) : ::MECPacket(other)
{
    copy(other);
}

VehicleControlPacket::~VehicleControlPacket()
{
}

VehicleControlPacket& VehicleControlPacket::operator=(const VehicleControlPacket& other)
{
    if (this == &other) return *this;
    ::MECPacket::operator=(other);
    copy(other);
    return *this;
}

void VehicleControlPacket::copy(const VehicleControlPacket& other)
{
    this->creationTime = other.creationTime;
    this->sequenceNumber = other.sequenceNumber;
}

void VehicleControlPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::MECPacket::parsimPack(b);
    doParsimPacking(b,this->creationTime);
    doParsimPacking(b,this->sequenceNumber);
}

void VehicleControlPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::MECPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->creationTime);
    doParsimUnpacking(b,this->sequenceNumber);
}

omnetpp::simtime_t VehicleControlPacket::getCreationTime() const
{
    return this->creationTime;
}

void VehicleControlPacket::setCreationTime(omnetpp::simtime_t creationTime)
{
    handleChange();
    this->creationTime = creationTime;
}

int VehicleControlPacket::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void VehicleControlPacket::setSequenceNumber(int sequenceNumber)
{
    handleChange();
    this->sequenceNumber = sequenceNumber;
}

class VehicleControlPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_creationTime,
        FIELD_sequenceNumber,
    };
  public:
    VehicleControlPacketDescriptor();
    virtual ~VehicleControlPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(VehicleControlPacketDescriptor)

VehicleControlPacketDescriptor::VehicleControlPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(VehicleControlPacket)), "MECPacket")
{
    propertyNames = nullptr;
}

VehicleControlPacketDescriptor::~VehicleControlPacketDescriptor()
{
    delete[] propertyNames;
}

bool VehicleControlPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<VehicleControlPacket *>(obj)!=nullptr;
}

const char **VehicleControlPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *VehicleControlPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int VehicleControlPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int VehicleControlPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_creationTime
        FD_ISEDITABLE,    // FIELD_sequenceNumber
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *VehicleControlPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "creationTime",
        "sequenceNumber",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int VehicleControlPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "creationTime") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *VehicleControlPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "omnetpp::simtime_t",    // FIELD_creationTime
        "int",    // FIELD_sequenceNumber
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **VehicleControlPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *VehicleControlPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int VehicleControlPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    VehicleControlPacket *pp = omnetpp::fromAnyPtr<VehicleControlPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void VehicleControlPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleControlPacket *pp = omnetpp::fromAnyPtr<VehicleControlPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'VehicleControlPacket'", field);
    }
}

const char *VehicleControlPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleControlPacket *pp = omnetpp::fromAnyPtr<VehicleControlPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string VehicleControlPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleControlPacket *pp = omnetpp::fromAnyPtr<VehicleControlPacket>(object); (void)pp;
    switch (field) {
        case FIELD_creationTime: return simtime2string(pp->getCreationTime());
        case FIELD_sequenceNumber: return long2string(pp->getSequenceNumber());
        default: return "";
    }
}

void VehicleControlPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleControlPacket *pp = omnetpp::fromAnyPtr<VehicleControlPacket>(object); (void)pp;
    switch (field) {
        case FIELD_creationTime: pp->setCreationTime(string2simtime(value)); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleControlPacket'", field);
    }
}

omnetpp::cValue VehicleControlPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleControlPacket *pp = omnetpp::fromAnyPtr<VehicleControlPacket>(object); (void)pp;
    switch (field) {
        case FIELD_creationTime: return pp->getCreationTime().dbl();
        case FIELD_sequenceNumber: return pp->getSequenceNumber();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'VehicleControlPacket' as cValue -- field index out of range?", field);
    }
}

void VehicleControlPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleControlPacket *pp = omnetpp::fromAnyPtr<VehicleControlPacket>(object); (void)pp;
    switch (field) {
        case FIELD_creationTime: pp->setCreationTime(value.doubleValue()); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleControlPacket'", field);
    }
}

const char *VehicleControlPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr VehicleControlPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    VehicleControlPacket *pp = omnetpp::fromAnyPtr<VehicleControlPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void VehicleControlPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleControlPacket *pp = omnetpp::fromAnyPtr<VehicleControlPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleControlPacket'", field);
    }
}

Register_Class(VehicleStartPacket)

VehicleStartPacket::VehicleStartPacket() : ::VehicleControlPacket()
{
}

VehicleStartPacket::VehicleStartPacket(const VehicleStartPacket& other) : ::VehicleControlPacket(other)
{
    copy(other);
}

VehicleStartPacket::~VehicleStartPacket()
{
}

VehicleStartPacket& VehicleStartPacket::operator=(const VehicleStartPacket& other)
{
    if (this == &other) return *this;
    ::VehicleControlPacket::operator=(other);
    copy(other);
    return *this;
}

void VehicleStartPacket::copy(const VehicleStartPacket& other)
{
    this->vehicleLength = other.vehicleLength;
    this->carId = other.carId;
    this->sumoCarId = other.sumoCarId;
    this->position_x = other.position_x;
    this->position_y = other.position_y;
    this->position_z = other.position_z;
    this->acceleration = other.acceleration;
    this->speed = other.speed;
    this->distance = other.distance;
    this->frontVehicle = other.frontVehicle;
}

void VehicleStartPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::VehicleControlPacket::parsimPack(b);
    doParsimPacking(b,this->vehicleLength);
    doParsimPacking(b,this->carId);
    doParsimPacking(b,this->sumoCarId);
    doParsimPacking(b,this->position_x);
    doParsimPacking(b,this->position_y);
    doParsimPacking(b,this->position_z);
    doParsimPacking(b,this->acceleration);
    doParsimPacking(b,this->speed);
    doParsimPacking(b,this->distance);
    doParsimPacking(b,this->frontVehicle);
}

void VehicleStartPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::VehicleControlPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->vehicleLength);
    doParsimUnpacking(b,this->carId);
    doParsimUnpacking(b,this->sumoCarId);
    doParsimUnpacking(b,this->position_x);
    doParsimUnpacking(b,this->position_y);
    doParsimUnpacking(b,this->position_z);
    doParsimUnpacking(b,this->acceleration);
    doParsimUnpacking(b,this->speed);
    doParsimUnpacking(b,this->distance);
    doParsimUnpacking(b,this->frontVehicle);
}

double VehicleStartPacket::getVehicleLength() const
{
    return this->vehicleLength;
}

void VehicleStartPacket::setVehicleLength(double vehicleLength)
{
    handleChange();
    this->vehicleLength = vehicleLength;
}

const char * VehicleStartPacket::getCarId() const
{
    return this->carId.c_str();
}

void VehicleStartPacket::setCarId(const char * carId)
{
    handleChange();
    this->carId = carId;
}

const char * VehicleStartPacket::getSumoCarId() const
{
    return this->sumoCarId.c_str();
}

void VehicleStartPacket::setSumoCarId(const char * sumoCarId)
{
    handleChange();
    this->sumoCarId = sumoCarId;
}

double VehicleStartPacket::getPosition_x() const
{
    return this->position_x;
}

void VehicleStartPacket::setPosition_x(double position_x)
{
    handleChange();
    this->position_x = position_x;
}

double VehicleStartPacket::getPosition_y() const
{
    return this->position_y;
}

void VehicleStartPacket::setPosition_y(double position_y)
{
    handleChange();
    this->position_y = position_y;
}

double VehicleStartPacket::getPosition_z() const
{
    return this->position_z;
}

void VehicleStartPacket::setPosition_z(double position_z)
{
    handleChange();
    this->position_z = position_z;
}

double VehicleStartPacket::getAcceleration() const
{
    return this->acceleration;
}

void VehicleStartPacket::setAcceleration(double acceleration)
{
    handleChange();
    this->acceleration = acceleration;
}

double VehicleStartPacket::getDesiredAcceleration() const
{
    return this->desiredAcceleration;
}

void VehicleStartPacket::setDesiredAcceleration(double desired)
{
    handleChange();
    this->desiredAcceleration = desired;
}

double VehicleStartPacket::getSpeed() const
{
    return this->speed;
}

void VehicleStartPacket::setSpeed(double speed)
{
    handleChange();
    this->speed = speed;
}

double VehicleStartPacket::getDistance() const
{
    return this->distance;
}

void VehicleStartPacket::setDistance(double distance)
{
    handleChange();
    this->distance = distance;
}

const char * VehicleStartPacket::getFrontVehicle() const
{
    return this->frontVehicle.c_str();
}

void VehicleStartPacket::setFrontVehicle(const char * frontVehicle)
{
    handleChange();
    this->frontVehicle = frontVehicle;
}

class VehicleStartPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_desiredAcceleration,
        FIELD_vehicleLength,
        FIELD_carId,
        FIELD_sumoCarId,
        FIELD_position_x,
        FIELD_position_y,
        FIELD_position_z,
        FIELD_acceleration,
        FIELD_speed,
        FIELD_distance,
        FIELD_frontVehicle,
    };
  public:
    VehicleStartPacketDescriptor();
    virtual ~VehicleStartPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(VehicleStartPacketDescriptor)

VehicleStartPacketDescriptor::VehicleStartPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(VehicleStartPacket)), "VehicleControlPacket")
{
    propertyNames = nullptr;
}

VehicleStartPacketDescriptor::~VehicleStartPacketDescriptor()
{
    delete[] propertyNames;
}

bool VehicleStartPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<VehicleStartPacket *>(obj)!=nullptr;
}

const char **VehicleStartPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *VehicleStartPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int VehicleStartPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 10+base->getFieldCount() : 10;
}

unsigned int VehicleStartPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_vehicleLength
        FD_ISEDITABLE,    // FIELD_carId
        FD_ISEDITABLE,    // FIELD_sumoCarId
        FD_ISEDITABLE,    // FIELD_position_x
        FD_ISEDITABLE,    // FIELD_position_y
        FD_ISEDITABLE,    // FIELD_position_z
        FD_ISEDITABLE,    // FIELD_acceleration
        FD_ISEDITABLE,    // FIELD_speed
        FD_ISEDITABLE,    // FIELD_distance
        FD_ISEDITABLE,    // FIELD_frontVehicle
    };
    return (field >= 0 && field < 10) ? fieldTypeFlags[field] : 0;
}

const char *VehicleStartPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "vehicleLength",
        "carId",
        "sumoCarId",
        "position_x",
        "position_y",
        "position_z",
        "acceleration",
        "speed",
        "distance",
        "frontVehicle",
    };
    return (field >= 0 && field < 10) ? fieldNames[field] : nullptr;
}

int VehicleStartPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "vehicleLength") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "carId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "sumoCarId") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "position_x") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "position_y") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "position_z") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "acceleration") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "speed") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "distance") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "frontVehicle") == 0) return baseIndex + 9;
    return base ? base->findField(fieldName) : -1;
}

const char *VehicleStartPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",    // FIELD_vehicleLength
        "string",    // FIELD_carId
        "string",    // FIELD_sumoCarId
        "double",    // FIELD_position_x
        "double",    // FIELD_position_y
        "double",    // FIELD_position_z
        "double",    // FIELD_acceleration
        "double",    // FIELD_speed
        "double",    // FIELD_distance
        "string",    // FIELD_frontVehicle
    };
    return (field >= 0 && field < 10) ? fieldTypeStrings[field] : nullptr;
}

const char **VehicleStartPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *VehicleStartPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int VehicleStartPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    VehicleStartPacket *pp = omnetpp::fromAnyPtr<VehicleStartPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void VehicleStartPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleStartPacket *pp = omnetpp::fromAnyPtr<VehicleStartPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'VehicleStartPacket'", field);
    }
}

const char *VehicleStartPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleStartPacket *pp = omnetpp::fromAnyPtr<VehicleStartPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string VehicleStartPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleStartPacket *pp = omnetpp::fromAnyPtr<VehicleStartPacket>(object); (void)pp;
    switch (field) {
        case FIELD_vehicleLength: return double2string(pp->getVehicleLength());
        case FIELD_carId: return oppstring2string(pp->getCarId());
        case FIELD_sumoCarId: return oppstring2string(pp->getSumoCarId());
        case FIELD_position_x: return double2string(pp->getPosition_x());
        case FIELD_position_y: return double2string(pp->getPosition_y());
        case FIELD_position_z: return double2string(pp->getPosition_z());
        case FIELD_acceleration: return double2string(pp->getAcceleration());
        case FIELD_speed: return double2string(pp->getSpeed());
        case FIELD_distance: return double2string(pp->getDistance());
        case FIELD_frontVehicle: return oppstring2string(pp->getFrontVehicle());
        default: return "";
    }
}

void VehicleStartPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleStartPacket *pp = omnetpp::fromAnyPtr<VehicleStartPacket>(object); (void)pp;
    switch (field) {
        case FIELD_desiredAcceleration: pp->setDesiredAcceleration(string2double(value)); break;
        case FIELD_vehicleLength: pp->setVehicleLength(string2double(value)); break;
        case FIELD_carId: pp->setCarId((value)); break;
        case FIELD_sumoCarId: pp->setSumoCarId((value)); break;
        case FIELD_position_x: pp->setPosition_x(string2double(value)); break;
        case FIELD_position_y: pp->setPosition_y(string2double(value)); break;
        case FIELD_position_z: pp->setPosition_z(string2double(value)); break;
        case FIELD_acceleration: pp->setAcceleration(string2double(value)); break;
        case FIELD_speed: pp->setSpeed(string2double(value)); break;
        case FIELD_distance: pp->setDistance(string2double(value)); break;
        case FIELD_frontVehicle: pp->setFrontVehicle((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleStartPacket'", field);
    }
}

omnetpp::cValue VehicleStartPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleStartPacket *pp = omnetpp::fromAnyPtr<VehicleStartPacket>(object); (void)pp;
    switch (field) {
        case FIELD_vehicleLength: return pp->getVehicleLength();
        case FIELD_carId: return pp->getCarId();
        case FIELD_sumoCarId: return pp->getSumoCarId();
        case FIELD_position_x: return pp->getPosition_x();
        case FIELD_position_y: return pp->getPosition_y();
        case FIELD_position_z: return pp->getPosition_z();
        case FIELD_acceleration: return pp->getAcceleration();
        case FIELD_speed: return pp->getSpeed();
        case FIELD_distance: return pp->getDistance();
        case FIELD_frontVehicle: return pp->getFrontVehicle();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'VehicleStartPacket' as cValue -- field index out of range?", field);
    }
}

void VehicleStartPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleStartPacket *pp = omnetpp::fromAnyPtr<VehicleStartPacket>(object); (void)pp;
    switch (field) {
        case FIELD_vehicleLength: pp->setVehicleLength(value.doubleValue()); break;
        case FIELD_carId: pp->setCarId(value.stringValue()); break;
        case FIELD_sumoCarId: pp->setSumoCarId(value.stringValue()); break;
        case FIELD_position_x: pp->setPosition_x(value.doubleValue()); break;
        case FIELD_position_y: pp->setPosition_y(value.doubleValue()); break;
        case FIELD_position_z: pp->setPosition_z(value.doubleValue()); break;
        case FIELD_acceleration: pp->setAcceleration(value.doubleValue()); break;
        case FIELD_speed: pp->setSpeed(value.doubleValue()); break;
        case FIELD_distance: pp->setDistance(value.doubleValue()); break;
        case FIELD_frontVehicle: pp->setFrontVehicle(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleStartPacket'", field);
    }
}

const char *VehicleStartPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr VehicleStartPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    VehicleStartPacket *pp = omnetpp::fromAnyPtr<VehicleStartPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void VehicleStartPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleStartPacket *pp = omnetpp::fromAnyPtr<VehicleStartPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleStartPacket'", field);
    }
}

Register_Class(VehicleStatusPacket)

VehicleStatusPacket::VehicleStatusPacket() : ::VehicleControlPacket()
{
}

VehicleStatusPacket::VehicleStatusPacket(const VehicleStatusPacket& other) : ::VehicleControlPacket(other)
{
    copy(other);
}

VehicleStatusPacket::~VehicleStatusPacket()
{
}

VehicleStatusPacket& VehicleStatusPacket::operator=(const VehicleStatusPacket& other)
{
    if (this == &other) return *this;
    ::VehicleControlPacket::operator=(other);
    copy(other);
    return *this;
}

void VehicleStatusPacket::copy(const VehicleStatusPacket& other)
{
    this->position_x = other.position_x;
    this->position_y = other.position_y;
    this->position_z = other.position_z;
    this->acceleration = other.acceleration;
    this->speed = other.speed;
    this->distance = other.distance;
    this->frontVehicle = other.frontVehicle;
    this->desiredAcceleration = other.desiredAcceleration;
}

void VehicleStatusPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::VehicleControlPacket::parsimPack(b);
    doParsimPacking(b,this->position_x);
    doParsimPacking(b,this->position_y);
    doParsimPacking(b,this->position_z);
    doParsimPacking(b,this->acceleration);
    doParsimPacking(b,this->speed);
    doParsimPacking(b,this->distance);
    doParsimPacking(b,this->frontVehicle);
    doParsimPacking(b,this->desiredAcceleration);
}

void VehicleStatusPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::VehicleControlPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->position_x);
    doParsimUnpacking(b,this->position_y);
    doParsimUnpacking(b,this->position_z);
    doParsimUnpacking(b,this->acceleration);
    doParsimUnpacking(b,this->speed);
    doParsimUnpacking(b,this->distance);
    doParsimUnpacking(b,this->frontVehicle);
    doParsimUnpacking(b,this->desiredAcceleration);
}

double VehicleStatusPacket::getPosition_x() const
{
    return this->position_x;
}

void VehicleStatusPacket::setPosition_x(double position_x)
{
    handleChange();
    this->position_x = position_x;
}

double VehicleStatusPacket::getPosition_y() const
{
    return this->position_y;
}

void VehicleStatusPacket::setPosition_y(double position_y)
{
    handleChange();
    this->position_y = position_y;
}

double VehicleStatusPacket::getPosition_z() const
{
    return this->position_z;
}

void VehicleStatusPacket::setPosition_z(double position_z)
{
    handleChange();
    this->position_z = position_z;
}

double VehicleStatusPacket::getAcceleration() const
{
    return this->acceleration;
}

void VehicleStatusPacket::setAcceleration(double acceleration)
{
    handleChange();
    this->acceleration = acceleration;
}

double VehicleStatusPacket::getSpeed() const
{
    return this->speed;
}

void VehicleStatusPacket::setSpeed(double speed)
{
    handleChange();
    this->speed = speed;
}

double VehicleStatusPacket::getDistance() const
{
    return this->distance;
}

void VehicleStatusPacket::setDistance(double distance)
{
    handleChange();
    this->distance = distance;
}

const char * VehicleStatusPacket::getFrontVehicle() const
{
    return this->frontVehicle.c_str();
}

void VehicleStatusPacket::setFrontVehicle(const char * frontVehicle)
{
    handleChange();
    this->frontVehicle = frontVehicle;
}

double VehicleStatusPacket::getDesiredAcceleration() const
{
    return this->desiredAcceleration;
}

void VehicleStatusPacket::setDesiredAcceleration(double desiredAcceleration)
{
    handleChange();
    this->desiredAcceleration = desiredAcceleration;
}

class VehicleStatusPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_position_x,
        FIELD_position_y,
        FIELD_position_z,
        FIELD_acceleration,
        FIELD_speed,
        FIELD_distance,
        FIELD_frontVehicle,
        FIELD_desiredAcceleration,
    };
  public:
    VehicleStatusPacketDescriptor();
    virtual ~VehicleStatusPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(VehicleStatusPacketDescriptor)

VehicleStatusPacketDescriptor::VehicleStatusPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(VehicleStatusPacket)), "VehicleControlPacket")
{
    propertyNames = nullptr;
}

VehicleStatusPacketDescriptor::~VehicleStatusPacketDescriptor()
{
    delete[] propertyNames;
}

bool VehicleStatusPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<VehicleStatusPacket *>(obj)!=nullptr;
}

const char **VehicleStatusPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *VehicleStatusPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int VehicleStatusPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int VehicleStatusPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_position_x
        FD_ISEDITABLE,    // FIELD_position_y
        FD_ISEDITABLE,    // FIELD_position_z
        FD_ISEDITABLE,    // FIELD_acceleration
        FD_ISEDITABLE,    // FIELD_speed
        FD_ISEDITABLE,    // FIELD_distance
        FD_ISEDITABLE,    // FIELD_frontVehicle
        FD_ISEDITABLE,    // FIELD_desiredAcceleration
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *VehicleStatusPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "position_x",
        "position_y",
        "position_z",
        "acceleration",
        "speed",
        "distance",
        "frontVehicle",
        "desiredAcceleration",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int VehicleStatusPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "position_x") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "position_y") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "position_z") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "acceleration") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "speed") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "distance") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "frontVehicle") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "desiredAcceleration") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *VehicleStatusPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",    // FIELD_position_x
        "double",    // FIELD_position_y
        "double",    // FIELD_position_z
        "double",    // FIELD_acceleration
        "double",    // FIELD_speed
        "double",    // FIELD_distance
        "string",    // FIELD_frontVehicle
        "double",    // FIELD_desiredAcceleration
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **VehicleStatusPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *VehicleStatusPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int VehicleStatusPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    VehicleStatusPacket *pp = omnetpp::fromAnyPtr<VehicleStatusPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void VehicleStatusPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleStatusPacket *pp = omnetpp::fromAnyPtr<VehicleStatusPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'VehicleStatusPacket'", field);
    }
}

const char *VehicleStatusPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleStatusPacket *pp = omnetpp::fromAnyPtr<VehicleStatusPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string VehicleStatusPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleStatusPacket *pp = omnetpp::fromAnyPtr<VehicleStatusPacket>(object); (void)pp;
    switch (field) {
        case FIELD_position_x: return double2string(pp->getPosition_x());
        case FIELD_position_y: return double2string(pp->getPosition_y());
        case FIELD_position_z: return double2string(pp->getPosition_z());
        case FIELD_acceleration: return double2string(pp->getAcceleration());
        case FIELD_speed: return double2string(pp->getSpeed());
        case FIELD_distance: return double2string(pp->getDistance());
        case FIELD_frontVehicle: return oppstring2string(pp->getFrontVehicle());
        case FIELD_desiredAcceleration: return double2string(pp->getDesiredAcceleration());
        default: return "";
    }
}

void VehicleStatusPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleStatusPacket *pp = omnetpp::fromAnyPtr<VehicleStatusPacket>(object); (void)pp;
    switch (field) {
        case FIELD_position_x: pp->setPosition_x(string2double(value)); break;
        case FIELD_position_y: pp->setPosition_y(string2double(value)); break;
        case FIELD_position_z: pp->setPosition_z(string2double(value)); break;
        case FIELD_acceleration: pp->setAcceleration(string2double(value)); break;
        case FIELD_speed: pp->setSpeed(string2double(value)); break;
        case FIELD_distance: pp->setDistance(string2double(value)); break;
        case FIELD_frontVehicle: pp->setFrontVehicle((value)); break;
        case FIELD_desiredAcceleration: pp->setDesiredAcceleration(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleStatusPacket'", field);
    }
}

omnetpp::cValue VehicleStatusPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleStatusPacket *pp = omnetpp::fromAnyPtr<VehicleStatusPacket>(object); (void)pp;
    switch (field) {
        case FIELD_position_x: return pp->getPosition_x();
        case FIELD_position_y: return pp->getPosition_y();
        case FIELD_position_z: return pp->getPosition_z();
        case FIELD_acceleration: return pp->getAcceleration();
        case FIELD_speed: return pp->getSpeed();
        case FIELD_distance: return pp->getDistance();
        case FIELD_frontVehicle: return pp->getFrontVehicle();
        case FIELD_desiredAcceleration: return pp->getDesiredAcceleration();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'VehicleStatusPacket' as cValue -- field index out of range?", field);
    }
}

void VehicleStatusPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleStatusPacket *pp = omnetpp::fromAnyPtr<VehicleStatusPacket>(object); (void)pp;
    switch (field) {
        case FIELD_position_x: pp->setPosition_x(value.doubleValue()); break;
        case FIELD_position_y: pp->setPosition_y(value.doubleValue()); break;
        case FIELD_position_z: pp->setPosition_z(value.doubleValue()); break;
        case FIELD_acceleration: pp->setAcceleration(value.doubleValue()); break;
        case FIELD_speed: pp->setSpeed(value.doubleValue()); break;
        case FIELD_distance: pp->setDistance(value.doubleValue()); break;
        case FIELD_frontVehicle: pp->setFrontVehicle(value.stringValue()); break;
        case FIELD_desiredAcceleration: pp->setDesiredAcceleration(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleStatusPacket'", field);
    }
}

const char *VehicleStatusPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr VehicleStatusPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    VehicleStatusPacket *pp = omnetpp::fromAnyPtr<VehicleStatusPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void VehicleStatusPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleStatusPacket *pp = omnetpp::fromAnyPtr<VehicleStatusPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleStatusPacket'", field);
    }
}

Register_Class(VehicleInstructionPacket)

VehicleInstructionPacket::VehicleInstructionPacket() : ::VehicleControlPacket()
{
}

VehicleInstructionPacket::VehicleInstructionPacket(const VehicleInstructionPacket& other) : ::VehicleControlPacket(other)
{
    copy(other);
}

VehicleInstructionPacket::~VehicleInstructionPacket()
{
}

VehicleInstructionPacket& VehicleInstructionPacket::operator=(const VehicleInstructionPacket& other)
{
    if (this == &other) return *this;
    ::VehicleControlPacket::operator=(other);
    copy(other);
    return *this;
}

void VehicleInstructionPacket::copy(const VehicleInstructionPacket& other)
{
    this->isLeader_ = other.isLeader_;
    this->acceleration = other.acceleration;
    this->thisAoi = other.thisAoi;
    this->precedingAoi = other.precedingAoi;
    this->leaderAoi = other.leaderAoi;
    this->triggeringCarId = other.triggeringCarId;
}

void VehicleInstructionPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::VehicleControlPacket::parsimPack(b);
    doParsimPacking(b,this->isLeader_);
    doParsimPacking(b,this->acceleration);
    doParsimPacking(b,this->thisAoi);
    doParsimPacking(b,this->precedingAoi);
    doParsimPacking(b,this->leaderAoi);
    doParsimPacking(b,this->triggeringCarId);
}

void VehicleInstructionPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::VehicleControlPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->isLeader_);
    doParsimUnpacking(b,this->acceleration);
    doParsimUnpacking(b,this->thisAoi);
    doParsimUnpacking(b,this->precedingAoi);
    doParsimUnpacking(b,this->leaderAoi);
    doParsimUnpacking(b,this->triggeringCarId);
}

bool VehicleInstructionPacket::isLeader() const
{
    return this->isLeader_;
}

void VehicleInstructionPacket::setIsLeader(bool isLeader)
{
    handleChange();
    this->isLeader_ = isLeader;
}

double VehicleInstructionPacket::getAcceleration() const
{
    return this->acceleration;
}

void VehicleInstructionPacket::setAcceleration(double acceleration)
{
    handleChange();
    this->acceleration = acceleration;
}

double VehicleInstructionPacket::getThisAoi() const
{
    return this->thisAoi;
}

void VehicleInstructionPacket::setThisAoi(double thisAoi)
{
    handleChange();
    this->thisAoi = thisAoi;
}

double VehicleInstructionPacket::getPrecedingAoi() const
{
    return this->precedingAoi;
}

void VehicleInstructionPacket::setPrecedingAoi(double precedingAoi)
{
    handleChange();
    this->precedingAoi = precedingAoi;
}

double VehicleInstructionPacket::getLeaderAoi() const
{
    return this->leaderAoi;
}

void VehicleInstructionPacket::setLeaderAoi(double leaderAoi)
{
    handleChange();
    this->leaderAoi = leaderAoi;
}

const char * VehicleInstructionPacket::getTriggeringCarId() const
{
    return this->triggeringCarId.c_str();
}

void VehicleInstructionPacket::setTriggeringCarId(const char * triggeringCarId)
{
    handleChange();
    this->triggeringCarId = triggeringCarId;
}

class VehicleInstructionPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_isLeader,
        FIELD_acceleration,
        FIELD_thisAoi,
        FIELD_precedingAoi,
        FIELD_leaderAoi,
        FIELD_triggeringCarId,
    };
  public:
    VehicleInstructionPacketDescriptor();
    virtual ~VehicleInstructionPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(VehicleInstructionPacketDescriptor)

VehicleInstructionPacketDescriptor::VehicleInstructionPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(VehicleInstructionPacket)), "VehicleControlPacket")
{
    propertyNames = nullptr;
}

VehicleInstructionPacketDescriptor::~VehicleInstructionPacketDescriptor()
{
    delete[] propertyNames;
}

bool VehicleInstructionPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<VehicleInstructionPacket *>(obj)!=nullptr;
}

const char **VehicleInstructionPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *VehicleInstructionPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int VehicleInstructionPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int VehicleInstructionPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_isLeader
        FD_ISEDITABLE,    // FIELD_acceleration
        FD_ISEDITABLE,    // FIELD_thisAoi
        FD_ISEDITABLE,    // FIELD_precedingAoi
        FD_ISEDITABLE,    // FIELD_leaderAoi
        FD_ISEDITABLE,    // FIELD_triggeringCarId
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *VehicleInstructionPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "isLeader",
        "acceleration",
        "thisAoi",
        "precedingAoi",
        "leaderAoi",
        "triggeringCarId",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int VehicleInstructionPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "isLeader") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "acceleration") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "thisAoi") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "precedingAoi") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "leaderAoi") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "triggeringCarId") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *VehicleInstructionPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "bool",    // FIELD_isLeader
        "double",    // FIELD_acceleration
        "double",    // FIELD_thisAoi
        "double",    // FIELD_precedingAoi
        "double",    // FIELD_leaderAoi
        "string",    // FIELD_triggeringCarId
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **VehicleInstructionPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *VehicleInstructionPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int VehicleInstructionPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    VehicleInstructionPacket *pp = omnetpp::fromAnyPtr<VehicleInstructionPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void VehicleInstructionPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleInstructionPacket *pp = omnetpp::fromAnyPtr<VehicleInstructionPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'VehicleInstructionPacket'", field);
    }
}

const char *VehicleInstructionPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleInstructionPacket *pp = omnetpp::fromAnyPtr<VehicleInstructionPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string VehicleInstructionPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleInstructionPacket *pp = omnetpp::fromAnyPtr<VehicleInstructionPacket>(object); (void)pp;
    switch (field) {
        case FIELD_isLeader: return bool2string(pp->isLeader());
        case FIELD_acceleration: return double2string(pp->getAcceleration());
        case FIELD_thisAoi: return double2string(pp->getThisAoi());
        case FIELD_precedingAoi: return double2string(pp->getPrecedingAoi());
        case FIELD_leaderAoi: return double2string(pp->getLeaderAoi());
        case FIELD_triggeringCarId: return oppstring2string(pp->getTriggeringCarId());
        default: return "";
    }
}

void VehicleInstructionPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleInstructionPacket *pp = omnetpp::fromAnyPtr<VehicleInstructionPacket>(object); (void)pp;
    switch (field) {
        case FIELD_isLeader: pp->setIsLeader(string2bool(value)); break;
        case FIELD_acceleration: pp->setAcceleration(string2double(value)); break;
        case FIELD_thisAoi: pp->setThisAoi(string2double(value)); break;
        case FIELD_precedingAoi: pp->setPrecedingAoi(string2double(value)); break;
        case FIELD_leaderAoi: pp->setLeaderAoi(string2double(value)); break;
        case FIELD_triggeringCarId: pp->setTriggeringCarId((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleInstructionPacket'", field);
    }
}

omnetpp::cValue VehicleInstructionPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    VehicleInstructionPacket *pp = omnetpp::fromAnyPtr<VehicleInstructionPacket>(object); (void)pp;
    switch (field) {
        case FIELD_isLeader: return pp->isLeader();
        case FIELD_acceleration: return pp->getAcceleration();
        case FIELD_thisAoi: return pp->getThisAoi();
        case FIELD_precedingAoi: return pp->getPrecedingAoi();
        case FIELD_leaderAoi: return pp->getLeaderAoi();
        case FIELD_triggeringCarId: return pp->getTriggeringCarId();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'VehicleInstructionPacket' as cValue -- field index out of range?", field);
    }
}

void VehicleInstructionPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleInstructionPacket *pp = omnetpp::fromAnyPtr<VehicleInstructionPacket>(object); (void)pp;
    switch (field) {
        case FIELD_isLeader: pp->setIsLeader(value.boolValue()); break;
        case FIELD_acceleration: pp->setAcceleration(value.doubleValue()); break;
        case FIELD_thisAoi: pp->setThisAoi(value.doubleValue()); break;
        case FIELD_precedingAoi: pp->setPrecedingAoi(value.doubleValue()); break;
        case FIELD_leaderAoi: pp->setLeaderAoi(value.doubleValue()); break;
        case FIELD_triggeringCarId: pp->setTriggeringCarId(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleInstructionPacket'", field);
    }
}

const char *VehicleInstructionPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr VehicleInstructionPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    VehicleInstructionPacket *pp = omnetpp::fromAnyPtr<VehicleInstructionPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void VehicleInstructionPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    VehicleInstructionPacket *pp = omnetpp::fromAnyPtr<VehicleInstructionPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehicleInstructionPacket'", field);
    }
}

Register_Class(VehiclePlatoonInfoPacket)

VehiclePlatoonInfoPacket::VehiclePlatoonInfoPacket() : ::VehicleControlPacket()
{
}

VehiclePlatoonInfoPacket::VehiclePlatoonInfoPacket(const VehiclePlatoonInfoPacket& other) : ::VehicleControlPacket(other)
{
    copy(other);
}

VehiclePlatoonInfoPacket::~VehiclePlatoonInfoPacket()
{
}

VehiclePlatoonInfoPacket& VehiclePlatoonInfoPacket::operator=(const VehiclePlatoonInfoPacket& other)
{
    if (this == &other) return *this;
    ::VehicleControlPacket::operator=(other);
    copy(other);
    return *this;
}

void VehiclePlatoonInfoPacket::copy(const VehiclePlatoonInfoPacket& other)
{
    this->platoonId = other.platoonId;
    this->platoonCarId = other.platoonCarId;
}

void VehiclePlatoonInfoPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::VehicleControlPacket::parsimPack(b);
    doParsimPacking(b,this->platoonId);
    doParsimPacking(b,this->platoonCarId);
}

void VehiclePlatoonInfoPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::VehicleControlPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->platoonId);
    doParsimUnpacking(b,this->platoonCarId);
}

const char * VehiclePlatoonInfoPacket::getPlatoonId() const
{
    return this->platoonId.c_str();
}

void VehiclePlatoonInfoPacket::setPlatoonId(const char * platoonId)
{
    handleChange();
    this->platoonId = platoonId;
}

const char * VehiclePlatoonInfoPacket::getPlatoonCarId() const
{
    return this->platoonCarId.c_str();
}

void VehiclePlatoonInfoPacket::setPlatoonCarId(const char * platoonCarId)
{
    handleChange();
    this->platoonCarId = platoonCarId;
}

class VehiclePlatoonInfoPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_platoonId,
        FIELD_platoonCarId,
    };
  public:
    VehiclePlatoonInfoPacketDescriptor();
    virtual ~VehiclePlatoonInfoPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(VehiclePlatoonInfoPacketDescriptor)

VehiclePlatoonInfoPacketDescriptor::VehiclePlatoonInfoPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(VehiclePlatoonInfoPacket)), "VehicleControlPacket")
{
    propertyNames = nullptr;
}

VehiclePlatoonInfoPacketDescriptor::~VehiclePlatoonInfoPacketDescriptor()
{
    delete[] propertyNames;
}

bool VehiclePlatoonInfoPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<VehiclePlatoonInfoPacket *>(obj)!=nullptr;
}

const char **VehiclePlatoonInfoPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *VehiclePlatoonInfoPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int VehiclePlatoonInfoPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int VehiclePlatoonInfoPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_platoonId
        FD_ISEDITABLE,    // FIELD_platoonCarId
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *VehiclePlatoonInfoPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "platoonId",
        "platoonCarId",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int VehiclePlatoonInfoPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "platoonId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "platoonCarId") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *VehiclePlatoonInfoPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_platoonId
        "string",    // FIELD_platoonCarId
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **VehiclePlatoonInfoPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *VehiclePlatoonInfoPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int VehiclePlatoonInfoPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    VehiclePlatoonInfoPacket *pp = omnetpp::fromAnyPtr<VehiclePlatoonInfoPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void VehiclePlatoonInfoPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    VehiclePlatoonInfoPacket *pp = omnetpp::fromAnyPtr<VehiclePlatoonInfoPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'VehiclePlatoonInfoPacket'", field);
    }
}

const char *VehiclePlatoonInfoPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    VehiclePlatoonInfoPacket *pp = omnetpp::fromAnyPtr<VehiclePlatoonInfoPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string VehiclePlatoonInfoPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    VehiclePlatoonInfoPacket *pp = omnetpp::fromAnyPtr<VehiclePlatoonInfoPacket>(object); (void)pp;
    switch (field) {
        case FIELD_platoonId: return oppstring2string(pp->getPlatoonId());
        case FIELD_platoonCarId: return oppstring2string(pp->getPlatoonCarId());
        default: return "";
    }
}

void VehiclePlatoonInfoPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VehiclePlatoonInfoPacket *pp = omnetpp::fromAnyPtr<VehiclePlatoonInfoPacket>(object); (void)pp;
    switch (field) {
        case FIELD_platoonId: pp->setPlatoonId((value)); break;
        case FIELD_platoonCarId: pp->setPlatoonCarId((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehiclePlatoonInfoPacket'", field);
    }
}

omnetpp::cValue VehiclePlatoonInfoPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    VehiclePlatoonInfoPacket *pp = omnetpp::fromAnyPtr<VehiclePlatoonInfoPacket>(object); (void)pp;
    switch (field) {
        case FIELD_platoonId: return pp->getPlatoonId();
        case FIELD_platoonCarId: return pp->getPlatoonCarId();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'VehiclePlatoonInfoPacket' as cValue -- field index out of range?", field);
    }
}

void VehiclePlatoonInfoPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    VehiclePlatoonInfoPacket *pp = omnetpp::fromAnyPtr<VehiclePlatoonInfoPacket>(object); (void)pp;
    switch (field) {
        case FIELD_platoonId: pp->setPlatoonId(value.stringValue()); break;
        case FIELD_platoonCarId: pp->setPlatoonCarId(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehiclePlatoonInfoPacket'", field);
    }
}

const char *VehiclePlatoonInfoPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr VehiclePlatoonInfoPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    VehiclePlatoonInfoPacket *pp = omnetpp::fromAnyPtr<VehiclePlatoonInfoPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void VehiclePlatoonInfoPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    VehiclePlatoonInfoPacket *pp = omnetpp::fromAnyPtr<VehiclePlatoonInfoPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'VehiclePlatoonInfoPacket'", field);
    }
}

Register_Class(LowLevelPacket)

LowLevelPacket::LowLevelPacket() : ::inet::ApplicationPacket()
{
}

LowLevelPacket::LowLevelPacket(const LowLevelPacket& other) : ::inet::ApplicationPacket(other)
{
    copy(other);
}

LowLevelPacket::~LowLevelPacket()
{
}

LowLevelPacket& LowLevelPacket::operator=(const LowLevelPacket& other)
{
    if (this == &other) return *this;
    ::inet::ApplicationPacket::operator=(other);
    copy(other);
    return *this;
}

void LowLevelPacket::copy(const LowLevelPacket& other)
{
    this->carId = other.carId;
    this->position_x = other.position_x;
    this->position_y = other.position_y;
    this->position_z = other.position_z;
    this->acceleration = other.acceleration;
    this->speed = other.speed;
    this->distance = other.distance;
    this->frontVehicle = other.frontVehicle;
}

void LowLevelPacket::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::inet::ApplicationPacket::parsimPack(b);
    doParsimPacking(b,this->carId);
    doParsimPacking(b,this->position_x);
    doParsimPacking(b,this->position_y);
    doParsimPacking(b,this->position_z);
    doParsimPacking(b,this->acceleration);
    doParsimPacking(b,this->speed);
    doParsimPacking(b,this->distance);
    doParsimPacking(b,this->frontVehicle);
}

void LowLevelPacket::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::inet::ApplicationPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->carId);
    doParsimUnpacking(b,this->position_x);
    doParsimUnpacking(b,this->position_y);
    doParsimUnpacking(b,this->position_z);
    doParsimUnpacking(b,this->acceleration);
    doParsimUnpacking(b,this->speed);
    doParsimUnpacking(b,this->distance);
    doParsimUnpacking(b,this->frontVehicle);
}

unsigned int LowLevelPacket::getCarId() const
{
    return this->carId;
}

void LowLevelPacket::setCarId(unsigned int carId)
{
    handleChange();
    this->carId = carId;
}

double LowLevelPacket::getPosition_x() const
{
    return this->position_x;
}

void LowLevelPacket::setPosition_x(double position_x)
{
    handleChange();
    this->position_x = position_x;
}

double LowLevelPacket::getPosition_y() const
{
    return this->position_y;
}

void LowLevelPacket::setPosition_y(double position_y)
{
    handleChange();
    this->position_y = position_y;
}

double LowLevelPacket::getPosition_z() const
{
    return this->position_z;
}

void LowLevelPacket::setPosition_z(double position_z)
{
    handleChange();
    this->position_z = position_z;
}

double LowLevelPacket::getAcceleration() const
{
    return this->acceleration;
}

void LowLevelPacket::setAcceleration(double acceleration)
{
    handleChange();
    this->acceleration = acceleration;
}

double LowLevelPacket::getSpeed() const
{
    return this->speed;
}

void LowLevelPacket::setSpeed(double speed)
{
    handleChange();
    this->speed = speed;
}

double LowLevelPacket::getDistance() const
{
    return this->distance;
}

void LowLevelPacket::setDistance(double distance)
{
    handleChange();
    this->distance = distance;
}

const char * LowLevelPacket::getFrontVehicle() const
{
    return this->frontVehicle.c_str();
}

void LowLevelPacket::setFrontVehicle(const char * frontVehicle)
{
    handleChange();
    this->frontVehicle = frontVehicle;
}

class LowLevelPacketDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_carId,
        FIELD_position_x,
        FIELD_position_y,
        FIELD_position_z,
        FIELD_acceleration,
        FIELD_speed,
        FIELD_distance,
        FIELD_frontVehicle,
    };
  public:
    LowLevelPacketDescriptor();
    virtual ~LowLevelPacketDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(LowLevelPacketDescriptor)

LowLevelPacketDescriptor::LowLevelPacketDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(LowLevelPacket)), "inet::ApplicationPacket")
{
    propertyNames = nullptr;
}

LowLevelPacketDescriptor::~LowLevelPacketDescriptor()
{
    delete[] propertyNames;
}

bool LowLevelPacketDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LowLevelPacket *>(obj)!=nullptr;
}

const char **LowLevelPacketDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LowLevelPacketDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LowLevelPacketDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int LowLevelPacketDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_carId
        FD_ISEDITABLE,    // FIELD_position_x
        FD_ISEDITABLE,    // FIELD_position_y
        FD_ISEDITABLE,    // FIELD_position_z
        FD_ISEDITABLE,    // FIELD_acceleration
        FD_ISEDITABLE,    // FIELD_speed
        FD_ISEDITABLE,    // FIELD_distance
        FD_ISEDITABLE,    // FIELD_frontVehicle
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *LowLevelPacketDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "carId",
        "position_x",
        "position_y",
        "position_z",
        "acceleration",
        "speed",
        "distance",
        "frontVehicle",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int LowLevelPacketDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "carId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "position_x") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "position_y") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "position_z") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "acceleration") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "speed") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "distance") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "frontVehicle") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *LowLevelPacketDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "unsigned int",    // FIELD_carId
        "double",    // FIELD_position_x
        "double",    // FIELD_position_y
        "double",    // FIELD_position_z
        "double",    // FIELD_acceleration
        "double",    // FIELD_speed
        "double",    // FIELD_distance
        "string",    // FIELD_frontVehicle
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **LowLevelPacketDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *LowLevelPacketDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int LowLevelPacketDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LowLevelPacket *pp = omnetpp::fromAnyPtr<LowLevelPacket>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void LowLevelPacketDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LowLevelPacket *pp = omnetpp::fromAnyPtr<LowLevelPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LowLevelPacket'", field);
    }
}

const char *LowLevelPacketDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LowLevelPacket *pp = omnetpp::fromAnyPtr<LowLevelPacket>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LowLevelPacketDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LowLevelPacket *pp = omnetpp::fromAnyPtr<LowLevelPacket>(object); (void)pp;
    switch (field) {
        case FIELD_carId: return ulong2string(pp->getCarId());
        case FIELD_position_x: return double2string(pp->getPosition_x());
        case FIELD_position_y: return double2string(pp->getPosition_y());
        case FIELD_position_z: return double2string(pp->getPosition_z());
        case FIELD_acceleration: return double2string(pp->getAcceleration());
        case FIELD_speed: return double2string(pp->getSpeed());
        case FIELD_distance: return double2string(pp->getDistance());
        case FIELD_frontVehicle: return oppstring2string(pp->getFrontVehicle());
        default: return "";
    }
}

void LowLevelPacketDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LowLevelPacket *pp = omnetpp::fromAnyPtr<LowLevelPacket>(object); (void)pp;
    switch (field) {
        case FIELD_carId: pp->setCarId(string2ulong(value)); break;
        case FIELD_position_x: pp->setPosition_x(string2double(value)); break;
        case FIELD_position_y: pp->setPosition_y(string2double(value)); break;
        case FIELD_position_z: pp->setPosition_z(string2double(value)); break;
        case FIELD_acceleration: pp->setAcceleration(string2double(value)); break;
        case FIELD_speed: pp->setSpeed(string2double(value)); break;
        case FIELD_distance: pp->setDistance(string2double(value)); break;
        case FIELD_frontVehicle: pp->setFrontVehicle((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LowLevelPacket'", field);
    }
}

omnetpp::cValue LowLevelPacketDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LowLevelPacket *pp = omnetpp::fromAnyPtr<LowLevelPacket>(object); (void)pp;
    switch (field) {
        case FIELD_carId: return (omnetpp::intval_t)(pp->getCarId());
        case FIELD_position_x: return pp->getPosition_x();
        case FIELD_position_y: return pp->getPosition_y();
        case FIELD_position_z: return pp->getPosition_z();
        case FIELD_acceleration: return pp->getAcceleration();
        case FIELD_speed: return pp->getSpeed();
        case FIELD_distance: return pp->getDistance();
        case FIELD_frontVehicle: return pp->getFrontVehicle();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LowLevelPacket' as cValue -- field index out of range?", field);
    }
}

void LowLevelPacketDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LowLevelPacket *pp = omnetpp::fromAnyPtr<LowLevelPacket>(object); (void)pp;
    switch (field) {
        case FIELD_carId: pp->setCarId(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_position_x: pp->setPosition_x(value.doubleValue()); break;
        case FIELD_position_y: pp->setPosition_y(value.doubleValue()); break;
        case FIELD_position_z: pp->setPosition_z(value.doubleValue()); break;
        case FIELD_acceleration: pp->setAcceleration(value.doubleValue()); break;
        case FIELD_speed: pp->setSpeed(value.doubleValue()); break;
        case FIELD_distance: pp->setDistance(value.doubleValue()); break;
        case FIELD_frontVehicle: pp->setFrontVehicle(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LowLevelPacket'", field);
    }
}

const char *LowLevelPacketDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr LowLevelPacketDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LowLevelPacket *pp = omnetpp::fromAnyPtr<LowLevelPacket>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LowLevelPacketDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LowLevelPacket *pp = omnetpp::fromAnyPtr<LowLevelPacket>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LowLevelPacket'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

