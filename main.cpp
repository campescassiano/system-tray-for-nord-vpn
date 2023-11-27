#include <QApplication>
#include <QMenu>
#include <QSystemTrayIcon>
#include <thread>

#include "NordVPN.hpp"

class SystemTrayIcon : public QSystemTrayIcon {
   private:
    NordVPN nord_;
    QMenu*   contextMenu;
    QAction* showAction;
    QAction* quitAction;
    QIcon*    connectedIcon_;
    QIcon*    disconnectedIcon_;
   public:
    SystemTrayIcon() {
        connectedIcon_ = new QIcon("../icons/nord-vpn-connected.png");
        disconnectedIcon_ = new QIcon("../icons/nord-vpn-disconnected.png");
        contextMenu = new QMenu();
        bool connected = nord_.IsConnected();

        if (connected)
            setIcon(*connectedIcon_);
        else
            setIcon(*disconnectedIcon_);

        if (connected)
            showAction = new QAction("Disconnect", this);
        else
            showAction = new QAction("Connect", this);

        quitAction = new QAction("Quit", this);
        contextMenu->addAction(showAction);
        contextMenu->addAction(quitAction);

        connect(showAction, &QAction::triggered, this,
                &SystemTrayIcon::showMessage);
        connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

        setContextMenu(contextMenu);

        show();
    }

    void Update(void)
    {
        bool connected = nord_.IsConnected();

        if (connected)
            setIcon(*connectedIcon_);
        else
            setIcon(*disconnectedIcon_);

        if (connected)
            showAction->setText("Disconnect");
        else
            showAction->setText("Connect");
    }

   public slots:
    void showMessage() { nord_.Toggle(); }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QApplication::setApplicationName("System Tray for NordVPN");

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        qWarning("System tray is not available on this system.");
        return 1;
    }

    SystemTrayIcon systemTrayIcon;

    std::thread update{[&systemTrayIcon] {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            systemTrayIcon.Update();
        }
    }};
    return app.exec();
}
