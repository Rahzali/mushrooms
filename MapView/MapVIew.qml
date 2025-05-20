import QtQuick
import QtQuick.Window
import QtLocation
import QtPositioning

Item {
    visible: true
    width: 800
    height: 600

    Plugin {
        id: mapPlugin
        name: "osm"
    }

    Map {
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(51.107883, 17.038538)  // Wroclaw, Poland
        zoomLevel: 14
    }
}
