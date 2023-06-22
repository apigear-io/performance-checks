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


#include "qmltestapi86.h"
#include "apifactory.h"

#include <QtQml>

namespace api {

QmlTestApi86::QmlTestApi86(QObject *parent)
    : AbstractTestApi86(parent)
{
    m_obj = ApiFactory::get()->createTestApi86();
    // Connection to forward backend implementation singal to wrapper:
    // - Forward the Property Changed singal emitted by backend implementation, as QmlTestApi86::Property Changed signal for qml property changed notification.
    // - Forward the  Property Changed singal emitted by backend implementation, as AbstractTestApi86::Property Changed signal
    // for usage, where QmlTestApi86 is used by the AbstractTuner interface and for connections with AbstractTestApi86::Property Changed signal
    connect(m_obj.get(), &AbstractTestApi86::propIntChanged, this, &QmlTestApi86::propIntChanged);
    connect(m_obj.get(), &AbstractTestApi86::propIntChanged, this, &AbstractTestApi86::propIntChanged);
    connect(m_obj.get(), &AbstractTestApi86::propFloatChanged, this, &QmlTestApi86::propFloatChanged);
    connect(m_obj.get(), &AbstractTestApi86::propFloatChanged, this, &AbstractTestApi86::propFloatChanged);
    connect(m_obj.get(), &AbstractTestApi86::propStringChanged, this, &QmlTestApi86::propStringChanged);
    connect(m_obj.get(), &AbstractTestApi86::propStringChanged, this, &AbstractTestApi86::propStringChanged);

    // Forward the singals emitted by backend implementation to QmlTestApi86 wrapper.
    //  Have in mind that there is no forwarding from the QmlTestApi86 wrapper to backend implementation.
    //  This signal is designed to be emitted from backend only.
    connect(m_obj.get(), &AbstractTestApi86::sigInt, this, &AbstractTestApi86::sigInt);
    connect(m_obj.get(), &AbstractTestApi86::sigFloat, this, &AbstractTestApi86::sigFloat);
    connect(m_obj.get(), &AbstractTestApi86::sigString, this, &AbstractTestApi86::sigString);
}

QmlTestApi86::~QmlTestApi86()
{
}

int QmlTestApi86::propInt() const
{
    return m_obj->propInt();
}

void QmlTestApi86::setPropInt(int propInt)
{
    return m_obj->setPropInt(propInt);
}

qreal QmlTestApi86::propFloat() const
{
    return m_obj->propFloat();
}

void QmlTestApi86::setPropFloat(qreal propFloat)
{
    return m_obj->setPropFloat(propFloat);
}

QString QmlTestApi86::propString() const
{
    return m_obj->propString();
}

void QmlTestApi86::setPropString(const QString& propString)
{
    return m_obj->setPropString(propString);
}

int QmlTestApi86::funcInt(int paramInt)
{
    return m_obj->funcInt(paramInt);
}

qreal QmlTestApi86::funcFloat(qreal paramFloat)
{
    return m_obj->funcFloat(paramFloat);
}

QString QmlTestApi86::funcString(const QString& paramString)
{
    return m_obj->funcString(paramString);
}

} //namespace api
