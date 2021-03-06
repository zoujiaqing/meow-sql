#include "cr_table_columns.h"
#include "central_right_table_tab.h"
#include "cr_table_columns_tools.h"
#include "app.h"

namespace meow {
namespace ui {
namespace main_window {
namespace central_right {

TableColumns::TableColumns(TableTab * parent) : QWidget(parent)
{
    createWidgets();
}

void TableColumns::setTable(db::TableEntity * table)
{
    _model.setTable(table);
}

void TableColumns::createWidgets()
{
    QVBoxLayout * mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);

    _tools = new TableColumnsTools(this);
    mainLayout->addWidget(_tools);

    _columnsTable = new QTableView(this);
    _columnsTable->horizontalHeader()->setHighlightSections(false);
    _columnsTable->verticalHeader()->setHighlightSections(false);
    auto geometrySettings = meow::app()->settings()->geometrySettings();
    _columnsTable->verticalHeader()->setDefaultSectionSize(
       geometrySettings->tableViewDefaultRowHeight());
    _columnsTable->setModel(&_model);
    for (int i=0; i<_model.columnCount(); ++i) {
        _columnsTable->setColumnWidth(i, _model.columnWidth(i));
    }
    mainLayout->addWidget(_columnsTable);
}

} // namespace central_right
} // namespace main_window
} // namespace ui
} // namespace meow
