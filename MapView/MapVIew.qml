import QtQuick
import QtQuick.Window
import QtLocation
import QtPositioning

Map {
    Plugin {
        id: mapPlugin
        name: "osm"
    }

    anchors.fill: parent
    plugin: mapPlugin
    center: QtPositioning.coordinate(50.290786, 18.6789467)
    zoomLevel: 12
    id: map
}
