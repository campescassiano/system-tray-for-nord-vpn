#include <QApplication>
#include <QMenu>
#include <QSystemTrayIcon>

class SystemTrayIcon : public QSystemTrayIcon {
   public:
    SystemTrayIcon() {
        // Create a system tray icon
        QIcon icon("../icons/nord-vpn-connected.png");  // Replace with the path
                                                        // to your icon
        setIcon(icon);

        // Create a context menu
        QMenu*   contextMenu = new QMenu();
        QAction* showAction  = new QAction("Show", this);
        QAction* quitAction  = new QAction("Quit", this);
        contextMenu->addAction(showAction);
        contextMenu->addAction(quitAction);

        // Connect actions to slots
        connect(showAction, &QAction::triggered, this,
                &SystemTrayIcon::showMessage);
        connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);

        // Set the context menu
        setContextMenu(contextMenu);

        // Show the system tray icon
        show();
    }

   public slots:
    void showMessage() {
        // Show a message when the "Show" action is triggered
        // showMessage("System Tray Icon", "Hello, this is a system tray
        // icon!");
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Check if the system supports system tray icons
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        qWarning("System tray is not available on this system.");
        return 1;
    }

    // Set application information
    QApplication::setApplicationName("System Tray for NordVPN");
    // QApplication::setOrganizationName("Cassiano Campes");

    // Create and run the application
    SystemTrayIcon systemTrayIcon;
    return app.exec();
}
