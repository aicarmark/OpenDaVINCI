/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2015 Christian Berger
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef OPENDAVINCI_CORE_BASE_VISITOR_H_
#define OPENDAVINCI_CORE_BASE_VISITOR_H_

#include <iostream>
#include <string>

#include "opendavinci/odcore/opendavinci.h"

namespace odcore { namespace serialization { class Serializable; } }

namespace odcore {
    namespace base {

        using namespace std;

        /**
         * This interface defines methods used by visitors.
         */
        class OPENDAVINCI_API Visitor {
            public:
                virtual ~Visitor();

                /**
                 * This method is called from a Visitable before the first
                 * visit(...) call.
                 *
                 * @param id Identifier of the visitable; typically the ID() of the visited message.
                 * @param shortName of the visited message.
                 * @param longName of the visited message.
                 */
                virtual void beginVisit(const int32_t &id, const string &shortName, const string &longName) = 0;

                /**
                 * This method is called from a Visitable after the last
                 * visit(...) call.
                 */
                virtual void endVisit() = 0;

                /**
                 * This method visits a Serializable.
                 *
                 * @param id identifier for the v to be serialized.
                 * @param longName Long identifier (ie. with package name) for the v to be serialized.
                 * @param shortName Short identifier for the v to be serialized.
                 * @param v Serializable to be serialized.
                 */
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, odcore::serialization::Serializable &v) = 0;

                /**
                 * This method visits a bool.
                 *
                 * @param id identifier for the v to be serialized.
                 * @param longName Long identifier (ie. with package name) for the v to be serialized.
                 * @param shortName Short identifier for the v to be serialized.
                 * @param v Bool to be serialized.
                 */
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, bool &v) = 0;

                /**
                 * This method visits a char.
                 *
                 * @param id identifier for the v to be serialized.
                 * @param longName Long identifier (ie. with package name) for the v to be serialized.
                 * @param shortName Short identifier for the v to be serialized.
                 * @param v Char to be serialized.
                 */
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, char &v) = 0;

                /**
                 * This method visits an unsigned char.
                 *
                 * @param id identifier for the v to be serialized.
                 * @param longName Long identifier (ie. with package name) for the v to be serialized.
                 * @param shortName Short identifier for the v to be serialized.
                 * @param v Unsigned char to be serialized.
                 */
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, unsigned char &v) = 0;

                /**
                 * This method visits an int8_t.
                 *
                 * @param id identifier for the v to be serialized.
                 * @param longName Long identifier (ie. with package name) for the v to be serialized.
                 * @param shortName Short identifier for the v to be serialized.
                 * @param i int8_t to be serialized.
                 */
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, int8_t &v) = 0;

                /**
                 * This method visits an int16_t.
                 *
                 * @param id identifier for the v to be serialized.
                 * @param longName Long identifier (ie. with package name) for the v to be serialized.
                 * @param shortName Short identifier for the v to be serialized.
                 * @param i int16_t to be serialized.
                 */
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, int16_t &v) = 0;

                /**
                 * This method visits an uint16_t.
                 *
                 * @param id identifier for the v to be serialized.
                 * @param longName Long identifier (ie. with package name) for the v to be serialized.
                 * @param shortName Short identifier for the v to be serialized.
                 * @param v uint16_t to be serialized.
                 */
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, uint16_t &v) = 0;

                /**
                 * This method visits an int32_t.
                 *
                 * @param id identifier for the v to be serialized.
                 * @param longName Long identifier (ie. with package name) for the v to be serialized.
                 * @param shortName Short identifier for the v to be serialized.
                 * @param i int32_t to be serialized.
                 */
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, int32_t &v) = 0;

                /**
                 * This method visits an uint32_t.
                 *
                 * @param id identifier for the v to be serialized.
                 * @param longName Long identifier (ie. with package name) for the v to be serialized.
                 * @param shortName Short identifier for the v to be serialized.
                 * @param v uint32_t to be serialized.
                 */
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, uint32_t &v) = 0;

                /**
                 * This method visits an int64_t.
                 *
                 * @param id identifier for the v to be serialized.
                 * @param longName Long identifier (ie. with package name) for the v to be serialized.
                 * @param shortName Short identifier for the v to be serialized.
                 * @param i int64_t to be serialized.
                 */
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, int64_t &v) = 0;

                /**
                 * This method visits an uint64_t.
                 *
                 * @param id identifier for the v to be serialized.
                 * @param longName Long identifier (ie. with package name) for the v to be serialized.
                 * @param shortName Short identifier for the v to be serialized.
                 * @param v uint64_t to be serialized.
                 */
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, uint64_t &v) = 0;

                /**
                 * This method visits a float.
                 *
                 * @param id identifier for the v to be serialized.
                 * @param longName Long identifier (ie. with package name) for the v to be serialized.
                 * @param shortName Short identifier for the v to be serialized.
                 * @param v Float to be serialized.
                 */
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, float &v) = 0;

                /**
                 * This method visits a double.
                 *
                 * @param id identifier for the v to be serialized.
                 * @param longName Long identifier (ie. with package name) for the v to be serialized.
                 * @param shortName Short identifier for the v to be serialized.
                 * @param v Double to be serialized.
                 */
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, double &v) = 0;

                /**
                 * This method visits a string.
                 *
                 * @param id identifier for the v to be serialized.
                 * @param longName Long identifier (ie. with package name) for the v to be serialized.
                 * @param shortName Short identifier for the v to be serialized.
                 * @param v String to be serialized.
                 */
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, string &v) = 0;

                /**
                 * This method visits undefined data of length size.
                 *
                 * @param id identifier for the v to be serialized.
                 * @param longName Long identifier (ie. with package name) for the v to be serialized.
                 * @param shortName Short identifier for the v to be serialized.
                 * @param data Data to be serialized.
                 * @param size Length of the data to be serialized.
                 */
                virtual void visit(const uint32_t &id, const string &longName, const string &shortName, void *data, const uint32_t &size) = 0;

                /**
                 * This method visits undefined data of length size.
                 *
                 * @param id identifier for the v to be serialized.
                 * @param longName Long identifier (ie. with package name) for the v to be serialized.
                 * @param shortName Short identifier for the v to be serialized.
                 * @param data Data to be serialized.
                 * @param count Number of elements in the fixed-sized array.
                 * @param t Data type for an element.
                 */
                // TODO: Rename to visit.
                virtual void visitArray(const uint32_t &id, const string &longName, const string &shortName, void *data, const uint32_t &count, const odcore::TYPE_ &t) = 0;
        };

    }
} // odcore::base

#endif /*OPENDAVINCI_CORE_BASE_VISITOR_H_*/
