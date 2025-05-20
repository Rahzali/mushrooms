#pragma once

#include <QObject>
#include <QQmlComponent>
#include <QQuickWindow>
#include <QQuickItem>

class MapView : public QObject
{
    Q_OBJECT

public:
    explicit MapView(QQuickWindow* window, QQmlEngine* engine, QObject* parent = nullptr);
    ~MapView() override = default;

    QQuickItem* item() const;

private:
    QQmlComponent m_component;
    QQuickItem* m_item = nullptr;
};
