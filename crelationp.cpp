#include "crelationp.h"
#include "ui_crelationp.h"

CRelationP::CRelationP(QSortFilterProxyModel *model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CRelationP)
{
    ui->setupUi(this);
    ui->buttonBox->buttons().first()->setText("Add");
    ui->table_Comp->setModel(model);
    ui->table_Comp->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table_Comp->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_Comp->verticalHeader()->hide();
    ui->table_Comp->setColumnHidden(0,true);

    connect(
      ui->table_Comp->selectionModel(),
      SIGNAL(currentRowChanged(const QModelIndex&,const QModelIndex&)),
      SLOT(onPersonSelectionChange(const QModelIndex&,const QModelIndex&))
     );
}

CRelationP::~CRelationP()
{
    delete ui;
}

void CRelationP::on_buttonBox_accepted()
{
    emit this->addPRelAccepted();
}

void CRelationP::on_buttonBox_rejected()
{
    emit this->relationRejected();
}

void CRelationP::on_CRelationP_finished()
{
    emit this->relationRejected();
}

void CRelationP::on_table_Comp_clicked(const QModelIndex &index)
{

    if(lastSelection == index.row() && !overrideTableClick)
    {
        overrideOnSelectionChange = true;
        ui->table_Comp->selectionModel()->clearSelection();
        lastSelection = -1;
        overrideOnSelectionChange = false;

    }else if(!overrideTableClick){
        int index = ui->table_Comp->currentIndex().row();
        lastSelection = index;
    }
    overrideTableClick = false;

}

void CRelationP::onPersonSelectionChange(const QModelIndex &c,const QModelIndex &p)
{
    if(!overrideOnSelectionChange)
    {
        int index = c.row();
        lastSelection = index;
        overrideTableClick = true;
    }
}
