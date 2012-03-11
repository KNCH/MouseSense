#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "devicedialog.h"

#include <QSystemTrayIcon>
#include <QSettings>

namespace Ui
{
    class MainWindow;
}

/*!
 * \class MainWindow
 *
 * \brief main window of the application
 * \author KNCH
 * \version 1.0
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    /*!
     * \fn MainWindow(QWidget *parent = 0);
     *
     * \brief Default constructor.
     * Sets up main window and loads settings from OS. At first run loads default settings.
     */
    MainWindow(QWidget *parent = 0);

    /*!
     * \fn ~MainWindow();
     *
     * \brief Destructor.
     */
    ~MainWindow();

protected:

    /*!
     * \fn changeEvent(QEvent *e);
     *
     * \brief Change event.
     */
    void changeEvent(QEvent *e);

    /*!
     * \fn closeEvent(QCloseEvent *event);
     *
     * \brief Close event.
     */
    void closeEvent(QCloseEvent *event);

private:
    /*!
     * \var ui
     *
     * \brief UI of the main window.
     */
    Ui::MainWindow *ui;

    /*!
     * \var trayIconMenu
     *
     * \brief Context menu for the tray icon.
     */
    QMenu *trayIconMenu;

    /*!
     * \var trayIcon
     *
     * \brief Tray icon.
     */
    QSystemTrayIcon *trayIcon;

    /*!
     * \var settings
     *
     * \brief Settings object for handling saving and loading.
     */
    QSettings *settings;

    /*!
     * \var ignoreMinimize
     *
     * \brief Boolean for ignoring minimize to tray.
     */
    bool ignoreMinimize;

private slots:
    /*!
     * \fn on_buttonAccept_clicked();
     *
     * \brief Applies the settings and saves them to OS.
     */
    void on_buttonAccept_clicked();

    /*!
     * \fn iconActivated(QSystemTrayIcon::ActivationReason reason);
     *
     * \brief Sets up tray icon actions.
     */
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

    /*!
     * \fn on_actionHelp_triggered();
     *
     * \brief Calls help dialog.
     */
    void on_actionHelp_triggered();

    /*!
     * \fn on_actionAbout_triggered();
     *
     * \brief Calls about dialog.
     */
    void on_actionAbout_triggered();

    /*!
     * \fn on_actionExit_triggered();
     *
     * \brief Closes the application.
     */
    void on_actionExit_triggered();

    /*!
     * \fn on_actionAddDevice_triggered();
     *
     * \brief Calls dialog for adding a new device.
     */
    void on_actionAddDevice_triggered();

    /*!
     * \fn on_actionRemoveDevice_triggered();
     *
     * \brief Removes current device from list.
     */
    void on_actionRemoveDevice_triggered();

    /*!
     * \fn on_actionClearSettings_triggered();
     *
     * \brief Clears settings in OS and sets them to default.
     */
    void on_actionClearSettings_triggered();

    /*!
     * \fn on_actionAcceptAll_triggered();
     *
     * \brief Toggles "accept for all devices" setting and saves settings to OS.
     */
    void on_actionAcceptAll_triggered();

    /*!
     * \fn saveSettings();
     *
     * \brief Saves settings to OS.
     */
    void saveSettings();

    /*!
     * \fn loadSettings();
     *
     * \brief Loads settings from OS.
     */
    void loadSettings();
};

#endif // MAINWINDOW_H
