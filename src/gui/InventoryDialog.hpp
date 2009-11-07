#ifndef INVWNTORY_DIALOG
#define INVWNTORY_DIALOG

#include <QDialog>
#include <QGridLayout>
#include <QTreeView>

class InventoryModel;
class InventoryDialog : public QDialog{
public:
    InventoryDialog(qtsl::Session&);
    ~InventoryDialog();
private:
    QGridLayout layout;
    QTreeView view;
    InventoryModel * model;
};

#endif
