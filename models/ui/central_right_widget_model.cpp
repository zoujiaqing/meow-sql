#include "central_right_widget_model.h"
#include <QObject> // tr()
#include <QDebug>

namespace meow {
namespace models {
namespace ui {

CentralRightWidgetModel::CentralRightWidgetModel()
    : _entityHolder()
{

}

bool CentralRightWidgetModel::setCurrentEntity(db::Entity * currentEntity)
{
    return _entityHolder.setCurrentEntity(currentEntity);
}

bool CentralRightWidgetModel::connectionChanged() const
{
    return _entityHolder.connectionChanged();
}

bool CentralRightWidgetModel::databaseChanged() const
{
    return _entityHolder.databaseChanged();
}

bool CentralRightWidgetModel::hasDatabase() const
{
    return _entityHolder.hasDatabase();
}

bool CentralRightWidgetModel::hasDataTab() const
{
    if (_entityHolder.currentEntity() == nullptr) {
        return false;
    }

    return _entityHolder.currentEntity()->type() == db::Entity::Type::Table ||
           _entityHolder.currentEntity()->type() == db::Entity::Type::View;
}

bool CentralRightWidgetModel::hasEntityTab() const
{
    if (_entityHolder.currentEntity() == nullptr) {
        return false;
    }
    // TODO: other types
    return _entityHolder.currentEntity()->type() == db::Entity::Type::Table;
}

bool CentralRightWidgetModel::hasQueryTab() const
{
    return _entityHolder.currentEntity() != nullptr;
}

QString CentralRightWidgetModel::titleForHostTab() const
{
    if (_entityHolder.currentEntity()) {

        QString host = _entityHolder.currentEntity()
                ->connection()->connectionParams()->hostName();

        return QObject::tr("Host") + ": " + host;
    } else {
        return QObject::tr("Host");
    }
}

QString CentralRightWidgetModel::titleForDatabaseTab() const
{
    if (_entityHolder.currentEntity()) {

        QString database = _entityHolder.currentEntity()
                ->connection()->database();

        return QObject::tr("Database") + ": " + database;
    }

    return QObject::tr("Database");
}


QString CentralRightWidgetModel::titleForTableTab() const
{
    if (_entityHolder.currentEntity()
        && _entityHolder.currentEntity()->type() == meow::db::Entity::Type::Table) {
        return QObject::tr("Table") + ": " + _entityHolder.currentEntity()->name();
    }

    return QObject::tr("Table");
}

QString CentralRightWidgetModel::titleForDataTab() const
{
    return QObject::tr("Data");
}

QString CentralRightWidgetModel::titleForQueryTab() const
{
    return QObject::tr("Query");
}

int CentralRightWidgetModel::indexForQueryTab() const
{
    if (hasDataTab()) {
        return static_cast<int>(CentralRightWidgetTabs::Data) + 1;
    } else if (hasEntityTab()) {
        return static_cast<int>(CentralRightWidgetTabs::Entity) + 1;
    } else if (hasDatabase()) {
        return static_cast<int>(CentralRightWidgetTabs::Database) + 1;
    }

    return static_cast<int>(CentralRightWidgetTabs::Host) + 1;
}

int CentralRightWidgetModel::indexForDataTab() const
{
    if (hasDataTab()) {
        if (_entityHolder.currentEntity()->type() == db::Entity::Type::Table) {
            return static_cast<int>(CentralRightWidgetTabs::Entity) + 1;
        } else if (_entityHolder.currentEntity()->type() == db::Entity::Type::View) {
            return static_cast<int>(CentralRightWidgetTabs::Database) + 1;
        }
    }
    return -1;
}

} // namespace ui
} // namespace models
} // namespace meow
