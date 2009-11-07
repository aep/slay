#include "Inventory.hpp"
#include "InventoryDialog.hpp"
#include <QFileIconProvider>


class InventoryModel : public qtsl::Inventory{
public:
    InventoryModel(qtsl::Session & session)
        :Inventory(session){
    }

    QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const{
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

private:
    QFileIconProvider provider;

};


InventoryDialog::InventoryDialog(qtsl::Session & session)
 :QDialog()
 ,layout(this){
    model=new InventoryModel(session);
    layout.addWidget(&view,1,1,1,1);
    layout.setContentsMargins ( 0,0,0,0);
    view.setModel(model);
    setWindowOpacity(0.8);
    setWindowTitle("Inventory");
    view.setFrameStyle(QFrame::NoFrame);
    view.setHeaderHidden(true);
}

InventoryDialog::~InventoryDialog(){
    delete model;
}




