#include "devicedialog.h"


DeviceDialog::DeviceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceDialog)
{
    ui->setupUi(this);
}

DeviceDialog::~DeviceDialog()
{
    delete ui;
}

void DeviceDialog::on_buttonAccept_clicked()
{
    accept();
}

void DeviceDialog::on_buttonCancel_clicked()
{
    reject();
}
