import QtQuick
import QtQuick.Window
import QtLocation
import QtPositioning

Item {
    anchors.fill: parent

    property var centerCoordinatre: QtPositioning.coordinate(50.290786, 18.6789467)  // RMS
    property real zoomLevel: 14

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
        anchors.fill: parent
        plugin: mapPlugin
        center: centerCoordinatre
        zoomLevel: zoomLevel
        id: map

        MapQuickItem {
            id: marker
            coordinate: centerCoordinatre
            anchorPoint.x: 5
            anchorPoint.y: 5
            sourceItem: Rectangle {
                width: 10
                height: 10
                radius: 5
                color: "black"
                border.color: "white"
                border.width: 1
            }
        }
    }
}
