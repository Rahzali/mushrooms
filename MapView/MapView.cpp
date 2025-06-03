#include "MapView.h"
#include <QQuickItem>
#include <QQmlContext>
#include <QDebug>
#include <QQmlEngine>
#include <QDir>
#include <QtLocation/QLocation>

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
    m_item->setAcceptedMouseButtons(Qt::LeftButton);
    m_item->setAcceptHoverEvents(true);
    m_item->installEventFilter(this);
}
QQuickItem * MapView::item() const
{
    return m_item;
}

bool MapView::eventFilter(QObject *obj, QEvent *event)
{
    auto t = event->type();
    switch (t) {
        case QEvent::Wheel: {
            QWheelEvent *wheel = static_cast<QWheelEvent *>(event);
            QPoint numDegrees = wheel->angleDelta() / 8;
            if (!numDegrees.isNull()) {
                float const deltaZoom = numDegrees.y() / 120.0f;  // rotationScale = 1/120
                m_item->setProperty("zoomLevel", m_item->property("zoomLevel").toFloat() + deltaZoom);
            }
            return true;
        }
        case QEvent::MouseButtonPress: {
            QMouseEvent *mouse = static_cast<QMouseEvent *>(event);
            if (mouse->button() == Qt::LeftButton) {
                m_lastMousePos = mouse->pos();
                m_dragging = true;
                return true;
            }
            break;
        }
        case QEvent::MouseMove: {
            if (m_dragging) {
                QMouseEvent *mouse = static_cast<QMouseEvent *>(event);
                QPointF delta = mouse->pos() - m_lastMousePos;
                m_lastMousePos = mouse->pos();
                QMetaObject::invokeMethod(m_item, "pan", Q_ARG(int, -delta.x()), Q_ARG(int, -delta.y()));
                return true;
            }
            break;
        }
        case QEvent::MouseButtonRelease: {
            QMouseEvent *mouse = static_cast<QMouseEvent *>(event);
            if (mouse->button() == Qt::LeftButton) {
                m_dragging = false;
                return true;
            }
            break;
        }
        default:
            return QObject::eventFilter(obj, event);
    }
    return false;
}
