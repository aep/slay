#include "InventoryModel.hpp"

using namespace qtsl;

InventoryModel::InventoryModel(qtsl::Session & session)
    :Inventory(session){
}



QVariant InventoryModel::data ( const QModelIndex & index, int role  ) const{
    if(!index.isValid())
        return QVariant();
    if(role==Qt::DecorationRole){
        if(qtsl::Inventory::data(index,Qt::UserRole+1).toBool()){
            if(qtsl::Inventory::data(index,Qt::UserRole+2).toInt()<2){
                return provider.icon(QFileIconProvider::Network);
            }else{
                return provider.icon(QFileIconProvider::Folder);
            }
        }else{
            return provider.icon(QFileIconProvider::File);
        }
    }else{
        return qtsl::Inventory::data(index,role);
    }
}

