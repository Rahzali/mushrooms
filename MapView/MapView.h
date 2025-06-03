#pragma once

#include <QQuickWindow>
#include <QQuickItem>

class MapView : public QObject
{
    Q_OBJECT

public:
    explicit MapView(QQuickWindow* window, QQmlEngine* engine, QObject* parent = nullptr);
    ~MapView() override = default;

    QQuickItem* item() const;
protected:
    bool eventFilter(QObject* obj, QEvent* event) override;


private:
    QQmlComponent m_component;
    QQuickItem* m_item = nullptr;
    QPointF m_lastMousePos;
    bool m_dragging = false;
};
