#include <QApplication>
#include <QMenu>
#include <QSystemTrayIcon>

#include "NordVPN.hpp"

class SystemTrayIcon : public QSystemTrayIcon {
   private:
    NordVPN nord;

   public:
    SystemTrayIcon() {
        QIcon    connectedIcon_("../icons/nord-vpn-connected.png");
        QIcon    disconnectedIcon_("../icons/nord-vpn-disconnected.png");
        QMenu*   contextMenu = new QMenu();
        QAction* showAction;
        bool     connected = nord.IsConnected();

        if (connected)
            setIcon(connectedIcon_);
        else
            setIcon(disconnectedIcon_);

        if (connected)
            showAction = new QAction("Disconnect", this);
        else
            showAction = new QAction("Connect", this);

        QAction* quitAction = new QAction("Quit", this);
        contextMenu->addAction(showAction);
        contextMenu->addAction(quitAction);

        connect(showAction, &QAction::triggered, this,
                &SystemTrayIcon::showMessage);
        connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

        setContextMenu(contextMenu);

        show();
    }

   public slots:
    void showMessage() { nord.Toggle(); }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        qWarning("System tray is not available on this system.");
        return 1;
    }

    QApplication::setApplicationName("System Tray for NordVPN");

    SystemTrayIcon systemTrayIcon;
    return app.exec();
}
