/**
 * OpenDLV - Simulation environment
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <cmath>
#include <iostream>
#include <iomanip>
#include <limits>
#include <memory>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"
#include "automotivedata/generated/cartesian/Constants.h"
#include "opendlv/data/environment/Point3.h"
#include "opendlv/data/environment/WGS84Coordinate.h"

namespace opendlv {
    namespace data {
        namespace environment {

            using namespace std;
            using namespace odcore::base;
            using namespace odcore::data;
            using namespace opendlv::data::environment;

            const double WGS84Coordinate::EQUATOR_RADIUS = 6378137.0;
            const double WGS84Coordinate::FLATTENING = 1.0 / 298.257223563;
            const double WGS84Coordinate::SQUARED_ECCENTRICITY = 2.0 * FLATTENING - FLATTENING * FLATTENING;
            const double WGS84Coordinate::POLE_RADIUS = EQUATOR_RADIUS * sqrt(1.0 - SQUARED_ECCENTRICITY);

            const double WGS84Coordinate::C00 = 1.0;
            const double WGS84Coordinate::C02 = 0.25;
            const double WGS84Coordinate::C04 = 0.046875;
            const double WGS84Coordinate::C06 = 0.01953125;
            const double WGS84Coordinate::C08 = 0.01068115234375;
            const double WGS84Coordinate::C22 = 0.75;
            const double WGS84Coordinate::C44 = 0.46875;
            const double WGS84Coordinate::C46 = 0.01302083333333333333;
            const double WGS84Coordinate::C48 = 0.00712076822916666666;
            const double WGS84Coordinate::C66 = 0.36458333333333333333;
            const double WGS84Coordinate::C68 = 0.00569661458333333333;
            const double WGS84Coordinate::C88 = 0.3076171875;

            const double WGS84Coordinate::R0 = WGS84Coordinate::C00 - WGS84Coordinate::SQUARED_ECCENTRICITY * (WGS84Coordinate::C02 + WGS84Coordinate::SQUARED_ECCENTRICITY * (WGS84Coordinate::C04 + WGS84Coordinate::SQUARED_ECCENTRICITY * (WGS84Coordinate::C06 + WGS84Coordinate::SQUARED_ECCENTRICITY * WGS84Coordinate::C08)));
            const double WGS84Coordinate::R1 = WGS84Coordinate::SQUARED_ECCENTRICITY * (WGS84Coordinate::C22 - WGS84Coordinate::SQUARED_ECCENTRICITY * (WGS84Coordinate::C04 + WGS84Coordinate::SQUARED_ECCENTRICITY * (WGS84Coordinate::C06 + WGS84Coordinate::SQUARED_ECCENTRICITY * WGS84Coordinate::C08)));
            const double WGS84Coordinate::R2T = WGS84Coordinate::SQUARED_ECCENTRICITY * WGS84Coordinate::SQUARED_ECCENTRICITY;
            const double WGS84Coordinate::R2 = WGS84Coordinate::R2T * (WGS84Coordinate::C44 - WGS84Coordinate::SQUARED_ECCENTRICITY * (WGS84Coordinate::C46 + WGS84Coordinate::SQUARED_ECCENTRICITY * WGS84Coordinate::C48));
            const double WGS84Coordinate::R3T = WGS84Coordinate::R2T* WGS84Coordinate::SQUARED_ECCENTRICITY;
            const double WGS84Coordinate::R3 = WGS84Coordinate::R3T * (WGS84Coordinate::C66 - WGS84Coordinate::SQUARED_ECCENTRICITY * WGS84Coordinate::C68);;
            const double WGS84Coordinate::R4 = WGS84Coordinate::R3T * WGS84Coordinate::SQUARED_ECCENTRICITY * WGS84Coordinate::C88;

            WGS84Coordinate::WGS84Coordinate() :
                geodetic::WGS84(),
                m_latitude(0),
                m_longitude(0),
                m_ml0(0) {
                initialize();
            }

            WGS84Coordinate::WGS84Coordinate(const double &lat, const double &lon) :
                geodetic::WGS84(lat, lon),
                m_latitude(0),
                m_longitude(0),
                m_ml0(0) {
                initialize();
            }

            WGS84Coordinate::~WGS84Coordinate() {}

            WGS84Coordinate& WGS84Coordinate::operator=(const WGS84Coordinate &obj) {
                geodetic::WGS84::operator=(obj);
                m_latitude = obj.m_latitude;
                m_longitude = obj.m_longitude;
                m_ml0 = obj.m_ml0;

                initialize();

                return (*this);
            }

            void WGS84Coordinate::initialize() {
                m_latitude = getLatitude() * cartesian::Constants::DEG2RAD;
                m_longitude = getLongitude() * cartesian::Constants::DEG2RAD;

                m_ml0 = mlfn(m_latitude);
            }

            double WGS84Coordinate::mlfn(const double &lat) const {
                double sin_phi = sin(lat);
                double cos_phi = cos(lat);
                cos_phi *= sin_phi;
                sin_phi *= sin_phi;

                return (R0 * lat - cos_phi * (R1 + sin_phi * (R2 + sin_phi * (R3 + sin_phi * R4))));
            }

            double WGS84Coordinate::msfn(const double &sinPhi, const double &cosPhi, const double &es) const {
                return (cosPhi / sqrt(1.0 - es * sinPhi * sinPhi));
            }

            pair<double, double> WGS84Coordinate::fwd(double lat, double lon) const {
                pair<double, double> result;

                double t = abs(lat) - cartesian::Constants::PI / 2.0;

                if ( (t > 1.0e-12) ||
                     (abs(lon) > 10.0) ) {
                    return result;
                }

                if (abs(t) < 1.0e-12) {
                    if (lat < 0.0) {
                        lat = -cartesian::Constants::PI / 2.0;
                    } else {
                        lat = cartesian::Constants::PI / 2.0;
                    }
                }

                lon -= m_longitude;

                pair<double, double> projectiveResult = project(lat, lon);
                result.first = EQUATOR_RADIUS * projectiveResult.first;
                result.second = EQUATOR_RADIUS * projectiveResult.second;

                return result;
            }

            pair<double, double> WGS84Coordinate::project(double lat, double lon) const {
                pair<double, double> result;

                if (abs(lat) < 1e-10 ) {
                    result.first = lon;
                    result.second = -m_ml0;
                } else {
                    double ms;
                    if (abs(sin(lat)) > 1e-10) {
                        ms = msfn(sin(lat), cos(lat), SQUARED_ECCENTRICITY) / sin(lat);
                    } else {
                        ms = 0.0;
                    }
                    result.first = ms * sin(lon *= sin(lat));
                    result.second = (mlfn(lat) - m_ml0) + ms * (1.0 - cos(lon));
                }

                return result;
            }

            const Point3 WGS84Coordinate::transform(const WGS84Coordinate &coordinate) const {
                pair<double, double> result = fwd(coordinate.getLatitude() * cartesian::Constants::DEG2RAD, coordinate.getLongitude() * cartesian::Constants::DEG2RAD);

                return Point3(result.first, result.second, 0);
            }

            const WGS84Coordinate WGS84Coordinate::transform(const Point3 &coordinate) const {
                return transform(coordinate, 1e-2);
            }

            const WGS84Coordinate WGS84Coordinate::transform(const Point3 &coordinate, const double &accuracy) const {
                WGS84Coordinate result(*this);
                Point3 point3Result;

                double addLon = 1e-5;
                int32_t signLon = (coordinate.getX() < 0) ? -1 : 1;
                double addLat = 1e-5;
                int32_t signLat = (coordinate.getY() < 0) ? -1 : 1;

                double epsilon = accuracy;
                if (epsilon < 0) {
                    epsilon = 1e-2;
                }

                point3Result = transform(result);
                double dOld = numeric_limits<double>::max();
                double d = abs(coordinate.getY() - point3Result.getY());
                uint32_t iterations = 0;
//                while ( (d < dOld) && (d > epsilon) && (iterations < 50000)) {
                while ( (d < dOld) && (d > epsilon) ) {
                    result = WGS84Coordinate(result.getLatitude() + signLat * addLat, result.getLongitude());
                    point3Result = transform(result);
                    dOld = d;
                    d = abs(coordinate.getY() - point3Result.getY());
                    iterations++;
                }

                // Use the last transformed point3Result here.
                dOld = numeric_limits<double>::max();
                d = abs(coordinate.getX() - point3Result.getX());
                iterations = 0;
//                while ( (d < dOld) && (d > epsilon) && (iterations < 50000)) {
                while ( (d < dOld) && (d > epsilon) ) {
                    result = WGS84Coordinate(result.getLatitude(), result.getLongitude() + signLon * addLon);
                    point3Result = transform(result);
                    dOld = d;
                    d = abs(coordinate.getX() - point3Result.getX());
                    iterations++;
                }

                return result;
            }

            const string WGS84Coordinate::toString() const {
                stringstream s;
                s << "(" << setprecision(10) << getLatitude() << (!(getLatitude() < 0) ? "N" : "S") << "; " << setprecision(10) << getLongitude() << (!(getLongitude() < 0) ? "E" : "W") << ")";
                return s.str();
            }

        }
    }
} // opendlv::data::environment
