/*
 * THIS IS A GENERATED FILE - CHANGES WILL BE OVERWRITTEN.
 */

#include <iostream>
#include <test8/GeneratedHeaders_Test8.h>
#include <test8/GeneratedHeaders_Test8_Helper.h>
#include <opendavinci/odcore/base/Visitable.h>
#include <opendavinci/odcore/reflection/MessageFromVisitableVisitor.h>
extern "C" {
    odcore::reflection::Helper *newHelper() {
        return new GeneratedHeaders_Test8_Helper;
    }
    void deleteHelper(odcore::reflection::Helper *h) {
        delete h;
    }
}
GeneratedHeaders_Test8_Helper::~GeneratedHeaders_Test8_Helper() {}
void GeneratedHeaders_Test8_Helper::delegateVistor(odcore::data::Container &c, odcore::base::Visitor &v, bool &successfullyDelegated) {
    GeneratedHeaders_Test8_Helper::__delegateVistor(c, v, successfullyDelegated);
}
odcore::reflection::Message GeneratedHeaders_Test8_Helper::map(odcore::data::Container &c, bool &successfullyMapped) {
    return GeneratedHeaders_Test8_Helper::__map(c, successfullyMapped);
}
void GeneratedHeaders_Test8_Helper::__delegateVistor(odcore::data::Container &c, odcore::base::Visitor &v, bool &successfullyDelegated) {
    successfullyDelegated = false;
    if (c.getDataType() == testpackage::Test8A::ID()) {
        testpackage::Test8A payload = c.getData<testpackage::Test8A>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == testpackage::Test8B::ID()) {
        testpackage::Test8B payload = c.getData<testpackage::Test8B>();
        payload.accept(v);
        successfullyDelegated = true;
    }
    if (c.getDataType() == testpackage::subpackage::Test8C::ID()) {
        testpackage::subpackage::Test8C payload = c.getData<testpackage::subpackage::Test8C>();
        payload.accept(v);
        successfullyDelegated = true;
    }
}
odcore::reflection::Message GeneratedHeaders_Test8_Helper::__map(odcore::data::Container &c, bool &successfullyMapped) {
    successfullyMapped = false;
    odcore::reflection::Message msg;
    odcore::reflection::MessageFromVisitableVisitor mfvv;
    __delegateVistor(c, mfvv, successfullyMapped);
    if (successfullyMapped) {
        msg = mfvv.getMessage();
    }
    return msg;
}
