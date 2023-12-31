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


#include "testapi99.h"

#include <QtQml>

namespace api {

TestApi99::TestApi99(QObject *parent)
    : AbstractTestApi99(parent)
    , m_propInt(0)
    , m_propFloat(0.0f)
    , m_propString(QString())
{
}

TestApi99::~TestApi99()
{
}

void TestApi99::setPropInt(int propInt)
{
    if (m_propInt != propInt) {
        m_propInt = propInt;
        emit propIntChanged(propInt);
    }
}

int TestApi99::propInt() const
{
    return m_propInt;
}

void TestApi99::setPropFloat(qreal propFloat)
{
    if (m_propFloat != propFloat) {
        m_propFloat = propFloat;
        emit propFloatChanged(propFloat);
    }
}

qreal TestApi99::propFloat() const
{
    return m_propFloat;
}

void TestApi99::setPropString(const QString& propString)
{
    if (m_propString != propString) {
        m_propString = propString;
        emit propStringChanged(propString);
    }
}

QString TestApi99::propString() const
{
    return m_propString;
}

int TestApi99::funcInt(int paramInt)
{
    return 0;
}

qreal TestApi99::funcFloat(qreal paramFloat)
{
    return 0.0f;
}

QString TestApi99::funcString(const QString& paramString)
{
    return QString();
}
} //namespace api
