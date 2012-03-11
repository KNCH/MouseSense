#include "mainwindow.h"

#include <QProcess>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QDesktopWidget>
#include <QMessageBox>

#include "devicedialog.h"

#include <QDebug>
#include <QxtGlobalShortcut>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this); // setup ui

    ignoreMinimize = false;

    settings = new QSettings("KNCH Software", "MouseSense"); // create settings object

    loadSettings(); // load settings

    this->setWindowIcon(QIcon(":images/mouseTray.png")); // set window icon
    trayIcon = new QSystemTrayIcon(QIcon(":images/mouseTray6.png")); // create system tray
    trayIcon->show();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason))); // connect system tray acions

    /* create context menu for system tray */
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(ui->actionAddDevice);
    trayIconMenu->addAction(ui->actionRemoveDevice);
    trayIconMenu->addAction(ui->actionAcceptAll);
    trayIconMenu->addAction(ui->actionClearSettings);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(ui->actionHelp);
    trayIconMenu->addAction(ui->actionAbout);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(ui->actionExit);
    trayIcon->setContextMenu(trayIconMenu);

    on_buttonAccept_clicked(); // accept on start

    /* create global shortcut for accepting mouse settings (libqxt should be installed) */
    QxtGlobalShortcut* shortcut = new QxtGlobalShortcut(this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(on_buttonAccept_clicked()));
    shortcut->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_Y));
}

MainWindow::~MainWindow()
{
}

void MainWindow::changeEvent(QEvent *e)
{
    /* minimize to tray */
    //QMainWindow::changeEvent(e);
    if(e->type() == QEvent::WindowStateChange)
    {
        if(isMinimized())
        {
            saveSettings(); // save settings
            if(!ignoreMinimize)
            {
                this->hide();
            }

        }
    }
}

void MainWindow::closeEvent(QCloseEvent *)
{
}

void MainWindow::on_buttonAccept_clicked()
{
    QProcess *process = new QProcess();
    if (!ui->actionAcceptAll->isChecked())
    {
        process->execute("xinput set-prop \"" + ui->comboBoxDevice->currentText() + "\" \"Device Accel Constant Deceleration\" " + ui->spinBoxSensitivity->text());
        process->execute("xinput set-prop \"" + ui->comboBoxDevice->currentText() + "\" \"Device Accel Velocity Scaling\" " + ui->spinBoxAcceleration->text());

    }
    else
    {
        for(int i=0; i<(ui->comboBoxDevice->count()); i++)
        {
            process->execute("xinput set-prop \"" + ui->comboBoxDevice->itemText(i) + "\" \"Device Accel Constant Deceleration\" " + ui->spinBoxSensitivity->text());
            process->execute("xinput set-prop \"" + ui->comboBoxDevice->itemText(i) + "\" \"Device Accel Velocity Scaling\" " + ui->spinBoxAcceleration->text());
        }
    }
    saveSettings(); // save settings
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger: // on click: hide/show main window
        if(this->isHidden())
        {
            this->show();
        }
        else
        {
            this->hide();
        }
        break;
    case QSystemTrayIcon::MiddleClick: // on middle click: press accept button
        on_buttonAccept_clicked();
        break;
    default:
        break;
    }
}

void MainWindow::on_actionHelp_triggered()
{
    this->show(); // show main window, if hidden
    ignoreMinimize = true; // ignore minimize to tray
    QMessageBox::information(this, ":: MouseSense | Help ::",
                             QString("1. Choose your mouse device.<br>") +
                             QString("2. Adjust sensitivity (\"Device Accel Constant Deceleration\").<br>") +
                             QString("(Note: The larger the value is, the lower is the sensitivity.)<br>") +
                             QString("3. Adjust acceleration (\"Device Accel Velocity Scaling\").<br>") +
                             QString("4. Press the button \"Accept\"."),
                             QMessageBox::Ok);
    ignoreMinimize = false; // restore minimize to tray
}

void MainWindow::on_actionAbout_triggered()
{
    this->show(); // show main window, if hidden
    ignoreMinimize = true; // ignore minimize to tray
    QMessageBox::about(this, trUtf8(":: About MouseSense ::"), trUtf8("<b>MouseSense 1.0</b><br>Utility to adjust mouse sensitivity and acceleration.<br><br>© 2010-2012 KNCH"));
    ignoreMinimize = false; // restore minimize to tray
}

void MainWindow::on_actionExit_triggered()
{
    delete(ui);
    exit(0);
}

void MainWindow::on_actionAddDevice_triggered()
{
    this->show(); // show main window, if hidden
    ignoreMinimize = true; // ignore minimize to tray
    DeviceDialog *deviceDialog = new DeviceDialog(this); // create device dialog
    if(deviceDialog->exec())
    {
        if(ui->comboBoxDevice->findText(deviceDialog->ui->lineEditDeviceName->text(), Qt::MatchExactly) == -1) // check, if the device is already in the list
        {
            ui->comboBoxDevice->addItem(deviceDialog->ui->lineEditDeviceName->text()); // add new device
            saveSettings(); // save settings
        }
    }
    ignoreMinimize = false; // restore minimize to tray
}

void MainWindow::on_actionRemoveDevice_triggered()
{
    this->show(); // show main window, if hidden
    ignoreMinimize = true; // ignore minimize to tray
    /* call comfirmation dialog before removing */
    QMessageBox *msgBox = new QMessageBox( QMessageBox::Warning, ":: MouseSense | Remove device? ::",
                                           "Are you sure you want to remove the following device?<br><br><b>" +  ui->comboBoxDevice->currentText() + "</b>",
                                           QMessageBox::Yes | QMessageBox::No, this);

    int selection = msgBox->exec();
    if(selection == QMessageBox::Yes)
    {
        ui->comboBoxDevice->removeItem(ui->comboBoxDevice->currentIndex());
        saveSettings(); // save settings
    }
    ignoreMinimize = false; // restore minimize to tray
}

void MainWindow::saveSettings()
{
    /* save all devices in a string list */
    QStringList *devices = new QStringList();
    for(int i=0; i<(ui->comboBoxDevice->count()); i++)
    {
        devices->append(ui->comboBoxDevice->itemText(i));
    }

    /* save settings to OS */
    settings->beginGroup("settings");
    settings->setValue("geometry", this->geometry());
    settings->setValue("devices", *devices);
    settings->setValue("sensitivity", ui->spinBoxSensitivity->value());
    settings->setValue("acceleretion", ui->spinBoxAcceleration->value());
    settings->setValue("acceptAll", ui->actionAcceptAll->isChecked());
    settings->setValue("currentDevice", ui->comboBoxDevice->currentIndex());
    settings->endGroup();
}

void MainWindow::loadSettings()
{
    ui->comboBoxDevice->clear();

    if(!settings->contains("settings/firstRun")) // check for first run
    {
        /* move the mainwindow to the center of the desktop */
        this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center());

        /* fill device list with default devices */
        ui->comboBoxDevice->addItem("Razer Razer Diamondback Optical Mouse");
        ui->comboBoxDevice->addItem("Razer Razer Diamondback 3G");
        ui->comboBoxDevice->addItem("PS/2+USB Mouse");

        /* set default mouse properties */
        ui->spinBoxSensitivity->setValue(4);
        ui->spinBoxAcceleration->setValue(1);

        ui->actionAcceptAll->setChecked(true); // set "accept for all devices" true

        settings->setValue("settings/firstRun", 0); // set firstRun to 0
        saveSettings(); // save settings
    }
    else
    {
        /* load settings from OS */
        settings->beginGroup("settings");
        this->setGeometry(settings->value("geometry").toRect());
        ui->comboBoxDevice->addItems(settings->value("devices").toStringList());
        ui->spinBoxSensitivity->setValue(settings->value("sensitivity").toInt());
        ui->spinBoxAcceleration->setValue(settings->value("acceleretion").toInt());
        ui->actionAcceptAll->setChecked(settings->value("acceptAll").toBool());
        ui->comboBoxDevice->setCurrentIndex(settings->value("currentDevice").toInt());
        settings->endGroup();
    }
}

void MainWindow::on_actionClearSettings_triggered()
{
    settings->clear();
    loadSettings();
}

void MainWindow::on_actionAcceptAll_triggered()
{
    saveSettings();
}
