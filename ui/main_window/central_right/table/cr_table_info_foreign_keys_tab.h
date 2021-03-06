#ifndef UI_CENTRAL_RIGHT_TABLE_INFO_FOREIGN_KEYS_TAB_H
#define UI_CENTRAL_RIGHT_TABLE_INFO_FOREIGN_KEYS_TAB_H

#include <QtWidgets>

namespace meow {

namespace models {
namespace forms {
    class TableInfoForm;
}
}

namespace ui {
namespace main_window {
namespace central_right {
namespace table_info {

class ForeignKeysTab : public QWidget
{
    Q_OBJECT
public:
    explicit ForeignKeysTab(models::forms::TableInfoForm * form,
                            QWidget *parent = nullptr);


private:
    void createWidgets();

    models::forms::TableInfoForm * _tableForm;
    QTableView * _fKeysTable;
    QHBoxLayout * _mainLayout;

};

} // namespace table_info
} // namespace central_right
} // namespace main_window
} // namespace ui
} // namespace meow

#endif // UI_CENTRAL_RIGHT_TABLE_INFO_FOREIGN_KEYS_TAB_H
