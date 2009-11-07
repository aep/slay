#ifndef SLAY_INVENTORYMODEL
#define SLAY_INVENTORYMODEL

#include "Inventory.hpp"
#include <QFileIconProvider>


class InventoryModel : public qtsl::Inventory{
public:
    InventoryModel(qtsl::Session & session);
    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
private:
    QFileIconProvider provider;

};



#endif
