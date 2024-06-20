//
// Generated file, do not edit! Created by opp_msgtool 6.0 from services/messages/ServiceMessages.msg.
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
#include "ServiceMessages_m.h"

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

class PlatoonResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
    };
  public:
    PlatoonResponseDescriptor();
    virtual ~PlatoonResponseDescriptor();

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

Register_ClassDescriptor(PlatoonResponseDescriptor)

PlatoonResponseDescriptor::PlatoonResponseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(PlatoonResponse)), "")
{
    propertyNames = nullptr;
}

PlatoonResponseDescriptor::~PlatoonResponseDescriptor()
{
    delete[] propertyNames;
}

bool PlatoonResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PlatoonResponse *>(obj)!=nullptr;
}

const char **PlatoonResponseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = { "existingClass",  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PlatoonResponseDescriptor::getProperty(const char *propertyName) const
{
    if (!strcmp(propertyName, "existingClass")) return "";
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PlatoonResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 0+base->getFieldCount() : 0;
}

unsigned int PlatoonResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    return 0;
}

const char *PlatoonResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

int PlatoonResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->findField(fieldName) : -1;
}

const char *PlatoonResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

const char **PlatoonResponseDescriptor::getFieldPropertyNames(int field) const
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

const char *PlatoonResponseDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int PlatoonResponseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PlatoonResponse *pp = omnetpp::fromAnyPtr<PlatoonResponse>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PlatoonResponseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PlatoonResponse *pp = omnetpp::fromAnyPtr<PlatoonResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PlatoonResponse'", field);
    }
}

const char *PlatoonResponseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PlatoonResponse *pp = omnetpp::fromAnyPtr<PlatoonResponse>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PlatoonResponseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PlatoonResponse *pp = omnetpp::fromAnyPtr<PlatoonResponse>(object); (void)pp;
    switch (field) {
        default: return "";
    }
}

void PlatoonResponseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PlatoonResponse *pp = omnetpp::fromAnyPtr<PlatoonResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PlatoonResponse'", field);
    }
}

omnetpp::cValue PlatoonResponseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PlatoonResponse *pp = omnetpp::fromAnyPtr<PlatoonResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PlatoonResponse' as cValue -- field index out of range?", field);
    }
}

void PlatoonResponseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PlatoonResponse *pp = omnetpp::fromAnyPtr<PlatoonResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PlatoonResponse'", field);
    }
}

const char *PlatoonResponseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    return nullptr;
}

omnetpp::any_ptr PlatoonResponseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PlatoonResponse *pp = omnetpp::fromAnyPtr<PlatoonResponse>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PlatoonResponseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PlatoonResponse *pp = omnetpp::fromAnyPtr<PlatoonResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PlatoonResponse'", field);
    }
}

Register_Class(ProcessResponseSelfMessage)

ProcessResponseSelfMessage::ProcessResponseSelfMessage(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

ProcessResponseSelfMessage::ProcessResponseSelfMessage(const ProcessResponseSelfMessage& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

ProcessResponseSelfMessage::~ProcessResponseSelfMessage()
{
}

ProcessResponseSelfMessage& ProcessResponseSelfMessage::operator=(const ProcessResponseSelfMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void ProcessResponseSelfMessage::copy(const ProcessResponseSelfMessage& other)
{
    this->platoonId = other.platoonId;
    this->triggeringCarId = other.triggeringCarId;
    this->calcTime = other.calcTime;
    this->resp = other.resp;
}

void ProcessResponseSelfMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->platoonId);
    doParsimPacking(b,this->triggeringCarId);
    doParsimPacking(b,this->calcTime);
    doParsimPacking(b,this->resp);
}

void ProcessResponseSelfMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->platoonId);
    doParsimUnpacking(b,this->triggeringCarId);
    doParsimUnpacking(b,this->calcTime);
    doParsimUnpacking(b,this->resp);
}

const char * ProcessResponseSelfMessage::getPlatoonId() const
{
    return this->platoonId.c_str();
}

void ProcessResponseSelfMessage::setPlatoonId(const char * platoonId)
{
    this->platoonId = platoonId;
}

const char * ProcessResponseSelfMessage::getTriggeringCarId() const
{
    return this->triggeringCarId.c_str();
}

void ProcessResponseSelfMessage::setTriggeringCarId(const char * triggeringCarId)
{
    this->triggeringCarId = triggeringCarId;
}

double ProcessResponseSelfMessage::getCalcTime() const
{
    return this->calcTime;
}

void ProcessResponseSelfMessage::setCalcTime(double calcTime)
{
    this->calcTime = calcTime;
}

const PlatoonResponse& ProcessResponseSelfMessage::getResp() const
{
    return this->resp;
}

void ProcessResponseSelfMessage::setResp(const PlatoonResponse& resp)
{
    this->resp = resp;
}

class ProcessResponseSelfMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_platoonId,
        FIELD_triggeringCarId,
        FIELD_calcTime,
        FIELD_resp,
    };
  public:
    ProcessResponseSelfMessageDescriptor();
    virtual ~ProcessResponseSelfMessageDescriptor();

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

Register_ClassDescriptor(ProcessResponseSelfMessageDescriptor)

ProcessResponseSelfMessageDescriptor::ProcessResponseSelfMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(ProcessResponseSelfMessage)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

ProcessResponseSelfMessageDescriptor::~ProcessResponseSelfMessageDescriptor()
{
    delete[] propertyNames;
}

bool ProcessResponseSelfMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ProcessResponseSelfMessage *>(obj)!=nullptr;
}

const char **ProcessResponseSelfMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ProcessResponseSelfMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ProcessResponseSelfMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int ProcessResponseSelfMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_platoonId
        FD_ISEDITABLE,    // FIELD_triggeringCarId
        FD_ISEDITABLE,    // FIELD_calcTime
        FD_ISCOMPOUND,    // FIELD_resp
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *ProcessResponseSelfMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "platoonId",
        "triggeringCarId",
        "calcTime",
        "resp",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int ProcessResponseSelfMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "platoonId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "triggeringCarId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "calcTime") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "resp") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *ProcessResponseSelfMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_platoonId
        "string",    // FIELD_triggeringCarId
        "double",    // FIELD_calcTime
        "PlatoonResponse",    // FIELD_resp
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **ProcessResponseSelfMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *ProcessResponseSelfMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int ProcessResponseSelfMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ProcessResponseSelfMessage *pp = omnetpp::fromAnyPtr<ProcessResponseSelfMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ProcessResponseSelfMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ProcessResponseSelfMessage *pp = omnetpp::fromAnyPtr<ProcessResponseSelfMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ProcessResponseSelfMessage'", field);
    }
}

const char *ProcessResponseSelfMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ProcessResponseSelfMessage *pp = omnetpp::fromAnyPtr<ProcessResponseSelfMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ProcessResponseSelfMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ProcessResponseSelfMessage *pp = omnetpp::fromAnyPtr<ProcessResponseSelfMessage>(object); (void)pp;
    switch (field) {
        case FIELD_platoonId: return oppstring2string(pp->getPlatoonId());
        case FIELD_triggeringCarId: return oppstring2string(pp->getTriggeringCarId());
        case FIELD_calcTime: return double2string(pp->getCalcTime());
        case FIELD_resp: return "";
        default: return "";
    }
}

void ProcessResponseSelfMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ProcessResponseSelfMessage *pp = omnetpp::fromAnyPtr<ProcessResponseSelfMessage>(object); (void)pp;
    switch (field) {
        case FIELD_platoonId: pp->setPlatoonId((value)); break;
        case FIELD_triggeringCarId: pp->setTriggeringCarId((value)); break;
        case FIELD_calcTime: pp->setCalcTime(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ProcessResponseSelfMessage'", field);
    }
}

omnetpp::cValue ProcessResponseSelfMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ProcessResponseSelfMessage *pp = omnetpp::fromAnyPtr<ProcessResponseSelfMessage>(object); (void)pp;
    switch (field) {
        case FIELD_platoonId: return pp->getPlatoonId();
        case FIELD_triggeringCarId: return pp->getTriggeringCarId();
        case FIELD_calcTime: return pp->getCalcTime();
        case FIELD_resp: return omnetpp::toAnyPtr(&pp->getResp()); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ProcessResponseSelfMessage' as cValue -- field index out of range?", field);
    }
}

void ProcessResponseSelfMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ProcessResponseSelfMessage *pp = omnetpp::fromAnyPtr<ProcessResponseSelfMessage>(object); (void)pp;
    switch (field) {
        case FIELD_platoonId: pp->setPlatoonId(value.stringValue()); break;
        case FIELD_triggeringCarId: pp->setTriggeringCarId(value.stringValue()); break;
        case FIELD_calcTime: pp->setCalcTime(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ProcessResponseSelfMessage'", field);
    }
}

const char *ProcessResponseSelfMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_resp: return omnetpp::opp_typename(typeid(PlatoonResponse));
        default: return nullptr;
    };
}

omnetpp::any_ptr ProcessResponseSelfMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ProcessResponseSelfMessage *pp = omnetpp::fromAnyPtr<ProcessResponseSelfMessage>(object); (void)pp;
    switch (field) {
        case FIELD_resp: return omnetpp::toAnyPtr(&pp->getResp()); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ProcessResponseSelfMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ProcessResponseSelfMessage *pp = omnetpp::fromAnyPtr<ProcessResponseSelfMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ProcessResponseSelfMessage'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

