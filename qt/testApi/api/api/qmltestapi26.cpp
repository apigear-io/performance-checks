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


#include "qmltestapi26.h"
#include "apifactory.h"

#include <QtQml>

namespace api {

QmlTestApi26::QmlTestApi26(QObject *parent)
    : AbstractTestApi26(parent)
{
    m_obj = ApiFactory::get()->createTestApi26();
    // Connection to forward backend implementation singal to wrapper:
    // - Forward the Property Changed singal emitted by backend implementation, as QmlTestApi26::Property Changed signal for qml property changed notification.
    // - Forward the  Property Changed singal emitted by backend implementation, as AbstractTestApi26::Property Changed signal
    // for usage, where QmlTestApi26 is used by the AbstractTuner interface and for connections with AbstractTestApi26::Property Changed signal
    connect(m_obj.get(), &AbstractTestApi26::propIntChanged, this, &QmlTestApi26::propIntChanged);
    connect(m_obj.get(), &AbstractTestApi26::propIntChanged, this, &AbstractTestApi26::propIntChanged);
    connect(m_obj.get(), &AbstractTestApi26::propFloatChanged, this, &QmlTestApi26::propFloatChanged);
    connect(m_obj.get(), &AbstractTestApi26::propFloatChanged, this, &AbstractTestApi26::propFloatChanged);
    connect(m_obj.get(), &AbstractTestApi26::propStringChanged, this, &QmlTestApi26::propStringChanged);
    connect(m_obj.get(), &AbstractTestApi26::propStringChanged, this, &AbstractTestApi26::propStringChanged);

    // Forward the singals emitted by backend implementation to QmlTestApi26 wrapper.
    //  Have in mind that there is no forwarding from the QmlTestApi26 wrapper to backend implementation.
    //  This signal is designed to be emitted from backend only.
    connect(m_obj.get(), &AbstractTestApi26::sigInt, this, &AbstractTestApi26::sigInt);
    connect(m_obj.get(), &AbstractTestApi26::sigFloat, this, &AbstractTestApi26::sigFloat);
    connect(m_obj.get(), &AbstractTestApi26::sigString, this, &AbstractTestApi26::sigString);
}

QmlTestApi26::~QmlTestApi26()
{
}

int QmlTestApi26::propInt() const
{
    return m_obj->propInt();
}

void QmlTestApi26::setPropInt(int propInt)
{
    return m_obj->setPropInt(propInt);
}

qreal QmlTestApi26::propFloat() const
{
    return m_obj->propFloat();
}

void QmlTestApi26::setPropFloat(qreal propFloat)
{
    return m_obj->setPropFloat(propFloat);
}

QString QmlTestApi26::propString() const
{
    return m_obj->propString();
}

void QmlTestApi26::setPropString(const QString& propString)
{
    return m_obj->setPropString(propString);
}

int QmlTestApi26::funcInt(int paramInt)
{
    return m_obj->funcInt(paramInt);
}

qreal QmlTestApi26::funcFloat(qreal paramFloat)
{
    return m_obj->funcFloat(paramFloat);
}

QString QmlTestApi26::funcString(const QString& paramString)
{
    return m_obj->funcString(paramString);
}

} //namespace api
