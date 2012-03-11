#ifndef DEVICEDIALOG_H
#define DEVICEDIALOG_H

#include <QDialog>
#include "ui_devicedialog.h"

namespace Ui
{
    class DeviceDialog;
}

/*!
 * \class DeviceDialog
 *
 * \brief Device dialog for adding a new pointing device to the application.
 * \author KNCH
 * \version 1.0
 */
class DeviceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceDialog(QWidget *parent = 0);
    ~DeviceDialog();

public:
    Ui::DeviceDialog *ui;

private slots:
    void on_buttonCancel_clicked();
    void on_buttonAccept_clicked();
};

#endif // DEVICEDIALOG_H
