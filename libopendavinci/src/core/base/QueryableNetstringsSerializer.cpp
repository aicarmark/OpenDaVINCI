/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
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

#include "core/base/QueryableNetstringsSerializer.h"
#include "core/base/Serializable.h"

namespace core {
    namespace base {

        using namespace std;

        QueryableNetstringsSerializer::QueryableNetstringsSerializer() :
            m_out(NULL),
            m_serializer() {
            m_serializer = SharedPointer<Serializer>(new QueryableNetstringsSerializerAACF());
        }

        QueryableNetstringsSerializer::QueryableNetstringsSerializer(ostream &out) :
            m_out(&out),
            m_serializer() {
            m_serializer = SharedPointer<Serializer>(new QueryableNetstringsSerializerAACF());
        }

        QueryableNetstringsSerializer::~QueryableNetstringsSerializer() {
            if (m_out != NULL) {
                m_serializer->getSerializedData(*m_out);
            }
        }

        void QueryableNetstringsSerializer::getSerializedData(ostream &o) {
            m_serializer->getSerializedData(o);
        }

        void QueryableNetstringsSerializer::write(const uint32_t &id, const Serializable &s) {
            m_serializer->write(id, s);
        }

        void QueryableNetstringsSerializer::write(const uint32_t &id, const bool &b) {
            m_serializer->write(id, b);
        }

        void QueryableNetstringsSerializer::write(const uint32_t &id, const char &c) {
            m_serializer->write(id, c);
        }

        void QueryableNetstringsSerializer::write(const uint32_t &id, const unsigned char &uc) {
            m_serializer->write(id, uc);
        }

        void QueryableNetstringsSerializer::write(const uint32_t &id, const int8_t &i) {
            m_serializer->write(id, i);
        }

        void QueryableNetstringsSerializer::write(const uint32_t &id, const int16_t &i) {
            m_serializer->write(id, i);
        }

        void QueryableNetstringsSerializer::write(const uint32_t &id, const uint16_t &ui) {
            m_serializer->write(id, ui);
        }

        void QueryableNetstringsSerializer::write(const uint32_t &id, const int32_t &i) {
            m_serializer->write(id, i);
        }

        void QueryableNetstringsSerializer::write(const uint32_t &id, const uint32_t &ui) {
            m_serializer->write(id, ui);
        }

        void QueryableNetstringsSerializer::write(const uint32_t &id, const int64_t &i) {
            m_serializer->write(id, i);
        }

        void QueryableNetstringsSerializer::write(const uint32_t &id, const uint64_t &ui) {
            m_serializer->write(id, ui);
        }

        void QueryableNetstringsSerializer::write(const uint32_t &id, const float &f) {
            m_serializer->write(id, f);
        }

        void QueryableNetstringsSerializer::write(const uint32_t &id, const double &d) {
            m_serializer->write(id, d);
        }

        void QueryableNetstringsSerializer::write(const uint32_t &id, const string &s) {
            m_serializer->write(id, s);
        }

        void QueryableNetstringsSerializer::write(const uint32_t &id, const void *data, const uint32_t &size) {
            m_serializer->write(id, data, size);
        }

    }
} // core::base
