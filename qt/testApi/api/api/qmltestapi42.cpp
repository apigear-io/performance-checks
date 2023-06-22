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


#include "qmltestapi42.h"
#include "apifactory.h"

#include <QtQml>

namespace api {

QmlTestApi42::QmlTestApi42(QObject *parent)
    : AbstractTestApi42(parent)
{
    m_obj = ApiFactory::get()->createTestApi42();
    // Connection to forward backend implementation singal to wrapper:
    // - Forward the Property Changed singal emitted by backend implementation, as QmlTestApi42::Property Changed signal for qml property changed notification.
    // - Forward the  Property Changed singal emitted by backend implementation, as AbstractTestApi42::Property Changed signal
    // for usage, where QmlTestApi42 is used by the AbstractTuner interface and for connections with AbstractTestApi42::Property Changed signal
    connect(m_obj.get(), &AbstractTestApi42::propIntChanged, this, &QmlTestApi42::propIntChanged);
    connect(m_obj.get(), &AbstractTestApi42::propIntChanged, this, &AbstractTestApi42::propIntChanged);
    connect(m_obj.get(), &AbstractTestApi42::propFloatChanged, this, &QmlTestApi42::propFloatChanged);
    connect(m_obj.get(), &AbstractTestApi42::propFloatChanged, this, &AbstractTestApi42::propFloatChanged);
    connect(m_obj.get(), &AbstractTestApi42::propStringChanged, this, &QmlTestApi42::propStringChanged);
    connect(m_obj.get(), &AbstractTestApi42::propStringChanged, this, &AbstractTestApi42::propStringChanged);

    // Forward the singals emitted by backend implementation to QmlTestApi42 wrapper.
    //  Have in mind that there is no forwarding from the QmlTestApi42 wrapper to backend implementation.
    //  This signal is designed to be emitted from backend only.
    connect(m_obj.get(), &AbstractTestApi42::sigInt, this, &AbstractTestApi42::sigInt);
    connect(m_obj.get(), &AbstractTestApi42::sigFloat, this, &AbstractTestApi42::sigFloat);
    connect(m_obj.get(), &AbstractTestApi42::sigString, this, &AbstractTestApi42::sigString);
}

QmlTestApi42::~QmlTestApi42()
{
}

int QmlTestApi42::propInt() const
{
    return m_obj->propInt();
}

void QmlTestApi42::setPropInt(int propInt)
{
    return m_obj->setPropInt(propInt);
}

qreal QmlTestApi42::propFloat() const
{
    return m_obj->propFloat();
}

void QmlTestApi42::setPropFloat(qreal propFloat)
{
    return m_obj->setPropFloat(propFloat);
}

QString QmlTestApi42::propString() const
{
    return m_obj->propString();
}

void QmlTestApi42::setPropString(const QString& propString)
{
    return m_obj->setPropString(propString);
}

int QmlTestApi42::funcInt(int paramInt)
{
    return m_obj->funcInt(paramInt);
}

qreal QmlTestApi42::funcFloat(qreal paramFloat)
{
    return m_obj->funcFloat(paramFloat);
}

QString QmlTestApi42::funcString(const QString& paramString)
{
    return m_obj->funcString(paramString);
}

} //namespace api
