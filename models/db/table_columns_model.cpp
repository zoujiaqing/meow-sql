#include "table_columns_model.h"
#include "db/entity/table_entity.h"
#include "db/table_structure.h"

namespace meow {
namespace models {
namespace db {

TableColumnsModel::TableColumnsModel(QObject * parent)
    : QAbstractTableModel(parent),
      _table(nullptr)
{

}

void TableColumnsModel::setTable(meow::db::TableEntity * table)
{
    removeData();
    _table = table;
    insertData();
}

int TableColumnsModel::columnCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return (int)Columns::Count;
}

int TableColumnsModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    if (_table && _table->structure()) {
        return _table->structure()->columns().size();
    }
    return 0;
}

Qt::ItemFlags TableColumnsModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::ItemIsEnabled;
    }

    return QAbstractItemModel::flags(index);
}

QVariant TableColumnsModel::headerData(int section,
                                    Qt::Orientation orientation,
                                    int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        switch (static_cast<Columns>(section)) {

        case Columns::Name:
            return QString(tr("Name"));

        case Columns::DataType:
            return QString(tr("Datatype"));

        case Columns::Length:
            return QString(tr("Length/Set"));

        case Columns::Unsigned:
            return QString(tr("Unsigned"));

        case Columns::AllowNull:
            return QString(tr("Allow NULL"));

        case Columns::Zerofill:
            return QString(tr("Zerofill"));

        case Columns::Default:
            return QString(tr("Default"));

        case Columns::Comment:
            return QString(tr("Comment"));

        case Columns::Collation:
            return QString(tr("Collation"));

        case Columns::Expression:
            return QString(tr("Expression"));

        case Columns::Virtuality:
            return QString(tr("Virtuality"));

        default:
            break;
        }
    } else {
        return QString::number(section + 1);
    }

    return QVariant();
}

QVariant TableColumnsModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid() || index.row() >= rowCount()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        return textDataAt(index.row(), index.column());
    }

    return QVariant();
}

void TableColumnsModel::removeData()
{
    if (rowCount()) {
        beginRemoveRows(QModelIndex(), 0, rowCount()-1);
        endRemoveRows();
    }
}
void TableColumnsModel::insertData()
{
    if (rowCount() > 0) {
        beginInsertRows(QModelIndex(), 0, rowCount()-1);
        endInsertRows();
    }
}

void TableColumnsModel::refresh()
{
    removeData();
    insertData();
}

QString TableColumnsModel::textDataAt(int row, int col) const
{
    meow::db::TableColumn * tableColumn = _table->structure()->columns().at(row);

    switch (static_cast<Columns>(col)) {

    case Columns::Name:
        return tableColumn->name();

    case Columns::DataType:
        return tableColumn->dataTypeName();

    case Columns::Length:
        return tableColumn->lengthSet();

    case Columns::Unsigned:
    case Columns::AllowNull:
    case Columns::Zerofill:
        return QString("");

    case Columns::Default: {
        using colDef = meow::db::ColumnDefaultType;
        const QString onUpdCurTS = QString(" ON UPDATE CURRENT_TIMESTAMP");

        switch (tableColumn->defaultType()) {

        case colDef::None:
            return tr("No default");

        case colDef::Text:
            return tableColumn->defaultText();
        case colDef::TextUpdateTS:
            return tableColumn->defaultText() + onUpdCurTS;

        case colDef::Null:
            return QString("NULL");
        case colDef::NullUpdateTS:
            return QString("NULL") + onUpdCurTS;

        case colDef::CurTS:
            return QString("CURRENT_TIMESTAMP");
        case colDef::CurTSUpdateTS:
            return QString("CURRENT_TIMESTAMP") + onUpdCurTS;

        case colDef::AutoInc:
            return QString("AUTO_INCREMENT");

        default:
            break;
        }
        return QString();
    }

    case Columns::Comment:
        return tableColumn->comment();

    case Columns::Collation:
        return tableColumn->collation();

    case Columns::Expression:
        return QString("");

    case Columns::Virtuality:
        return QString("");

    default:
       return QString();
    }
}

} // namespace db
} // namespace models
} // namespace meow