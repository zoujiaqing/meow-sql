#ifndef DB_TABLE_ENTITY_H
#define DB_TABLE_ENTITY_H

#include "entity.h"
#include "db/table_structure.h"

namespace meow {
namespace db {

class DataBaseEntity;

class TableEntity : public Entity
{
public:
    TableEntity(const QString & tableName, DataBaseEntity * parent = nullptr);
    virtual ~TableEntity();

    virtual QString name() const override;
    virtual QVariant icon() const override;
    virtual Type type() const override { return Type::Table; }

    virtual bool hasDataSize() const override { return true; }
    virtual db::ulonglong dataSize() const override { return _dataSize; }
    void setDataSize(db::ulonglong dataSize) { _dataSize = dataSize; }

    // TODO: enum?
    QString engineStr() const { return _engineStr; }
    void setEngine(const QString & engine) { _engineStr = engine; }

    QString collation() const { return _collation; }
    void setCollation(const QString & collation) { _collation = collation; }

    db::ulonglong rowsCount(bool refresh = false);
    void setRowsCount(db::ulonglong rowsCount) { _rowsCount = rowsCount; }

    db::ulonglong version() const { return _version; }
    void setVersion(db::ulonglong version) { _version = version; }

    db::TableStructure * structure() const;

private:
    QString _collation;
    QString _tableName;
    QString _engineStr;

    db::ulonglong _rowsCount;
    db::ulonglong _dataSize;
    db::ulonglong _version;

    mutable db::TableStructure * _structure;
};

} // namespace db
} // namespace meow

#endif // DB_TABLE_ENTITY_H
