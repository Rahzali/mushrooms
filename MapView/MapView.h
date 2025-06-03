#pragma once

#include <QObject>
#include <QQmlComponent>
#include <QQuickWindow>
#include <QQuickItem>

#include "MapItem.h"

class MapView : public QObject
{
    Q_OBJECT

public:

    enum class Error { InvalidId, InvalidCoordinates };
    class Exception : public std::runtime_error
    {
    public:
        explicit Exception(Error const err) : std::runtime_error("MapView exception"), m_error(err) {}
        explicit Exception(Error const err, std::string msg) : std::runtime_error(std::move(msg)), m_error(err) {}
        Error error() const { return m_error; }
    private:
        Error m_error;
    };


    explicit MapView(QQuickWindow* window, QQmlEngine* engine, QObject* parent = nullptr);
    ~MapView() override = default;

    QQuickItem* item() const;

    MapItem_t getMapItem(const std::string& name) const;
    void addMapItem(const std::string& name, const MapItem_t& item);
    void updateMapItem(const std::string& name, const MapItem_t& item);
    void removeMapItem(const std::string& name);

private:
    QQmlComponent m_component;
    QQuickItem* m_item = nullptr;
    std::unordered_map<std::string, MapItem_t> m_mapItems;
};
