#include "MapView.h"
#include <QQuickItem>
#include <QQmlContext>
#include <QDebug>
#include <QQmlEngine>
#include <QDir>


// New constructor with window and engine passed
MapView::MapView(QQuickWindow* window, QQmlEngine* engine, QObject* parent)
    : QObject(parent)
    , m_component(engine, this)  // Initialize QQmlComponent with QQmlEngine* and this as parent
{
    if (!window || !engine) {
        qWarning() << "MapView: null window or engine";
        return;
    }

    const QUrl qmlUrl(QStringLiteral("qrc:/qml/MapView.qml"));
    m_component.loadUrl(qmlUrl);

    if (m_component.isError()) {
        for (const auto& err : m_component.errors())
            qWarning() << err.toString();
        return;
    }

    QObject* created = m_component.create(engine->rootContext());
    if (!created) {
        qWarning() << "MapView: failed to instantiate component:" << qmlUrl;
        return;
    }

    m_item = qobject_cast<QQuickItem*>(created);
    if (!m_item) {
        qWarning() << "MapView: root object is not a QQuickItem:" << qmlUrl;
        delete created;
        return;
    }


    m_item->setParentItem(window->contentItem());
    m_item->setParent(this);
}

QQuickItem * MapView::item() const
{
    return m_item;
}

MapItem_t MapView::getMapItem(const std::string &name) const
{
}
void MapView::addMapItem(const std::string &name, const MapItem_t &item) {}
void MapView::updateMapItem(const std::string &name, const MapItem_t &item) {}
void MapView::removeMapItem(const std::string &name) {}
