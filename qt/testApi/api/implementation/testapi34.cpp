/**
NO TITLE
Copyright (C) 2020 ApiGear UG

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


#include "testapi34.h"

#include <QtQml>

namespace api {

TestApi34::TestApi34(QObject *parent)
    : AbstractTestApi34(parent)
    , m_propInt(0)
    , m_propFloat(0.0f)
    , m_propString(QString())
{
}

TestApi34::~TestApi34()
{
}

void TestApi34::setPropInt(int propInt)
{
    if (m_propInt != propInt) {
        m_propInt = propInt;
        emit propIntChanged(propInt);
    }
}

int TestApi34::propInt() const
{
    return m_propInt;
}

void TestApi34::setPropFloat(qreal propFloat)
{
    if (m_propFloat != propFloat) {
        m_propFloat = propFloat;
        emit propFloatChanged(propFloat);
    }
}

qreal TestApi34::propFloat() const
{
    return m_propFloat;
}

void TestApi34::setPropString(const QString& propString)
{
    if (m_propString != propString) {
        m_propString = propString;
        emit propStringChanged(propString);
    }
}

QString TestApi34::propString() const
{
    return m_propString;
}

int TestApi34::funcInt(int paramInt)
{
    return 0;
}

qreal TestApi34::funcFloat(qreal paramFloat)
{
    return 0.0f;
}

QString TestApi34::funcString(const QString& paramString)
{
    return QString();
}
} //namespace api
