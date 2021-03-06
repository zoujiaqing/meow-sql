#ifndef DB_TABLE_STRUCTURE_H
#define DB_TABLE_STRUCTURE_H

#include "db/common.h"
#include "table_column.h"
#include "table_index.h"
#include "foreign_key.h"

namespace meow {
namespace db {

// Holds table structure items and additional options
class TableStructure
{
public:
    TableStructure();
    ~TableStructure();

    QList<TableColumn *> & columns() { return _columns; }
    QList<TableIndex  *> & indicies() { return _indicies; }
    QList<ForeignKey  *> & foreighKeys() { return _foreignKeys; }

    QString rowFormatStr() const { return _rowFormatStr; }
    void setRowFormat(const QString & format) { _rowFormatStr = format; }

    db::ulonglong avgRowLen() const { return _avgRowLen; }
    void setAvgRowLen(db::ulonglong len) { _avgRowLen = len; }

    db::ulonglong autoInc() const { return _autoInc; }
    void setAutoInc(db::ulonglong inc) { _autoInc = inc; }

    db::ulonglong maxRows() const { return _maxRows; }
    void setMaxRows(db::ulonglong maxRows) { _maxRows = maxRows; }

    bool isCheckSum() const { return _isCheckSum; }
    void setCheckSum(bool checksum) { _isCheckSum = checksum; }

    QString comment() const { return _comment; }
    void setComment(const QString & comment) { _comment = comment; }

    bool hasIndexForColumn(const QString & columnName, TableIndexClass indexClass);

private:

    QString _comment;
    QString _rowFormatStr;
    db::ulonglong _avgRowLen;
    db::ulonglong _autoInc;
    db::ulonglong _maxRows;
    bool _isCheckSum;

    QList<TableColumn *>  _columns;
    QList<TableIndex  *>  _indicies;
    QList<ForeignKey  *>  _foreignKeys;

};

} // namespace db
} // namespace meow

#endif // DB_TABLE_STRUCTURE_H
