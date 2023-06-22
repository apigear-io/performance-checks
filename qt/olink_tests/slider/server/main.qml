import QtQuick 2.15
import QtQuick.Layouts 1.2
import QtQuick.Controls 2.15
import plugin_api 1.0

ApplicationWindow {
    id: appWindow
    visible: true
    width: 300
    height: 300
    ColumnLayout {
        spacing: 10
        id: mainLayout
        anchors.fill: parent

        Slider {
            from: 0
            to: 100
            onValueChanged: {
                myApi.propFloat = value
            }
        }
    }
    ApiTestApi0 { id: myApi }

}
