#include <iostream>
#include <string>
#include <dbus-c++/dbus.h>

class AppRegistryClient {
private:
    DBus::BusDispatcher dispatcher;
    DBus::Connection conn;
    DBus::InterfaceProxy appRegistryProxy;

public:
    AppRegistryClient()
        : conn(DBus::Connection::SessionBus()), appRegistryProxy(conn, "org.example.AppRegistry", "/org/example/AppRegistry") {}

    // Метод для регистрации формата и приложения
    void RegisterFormat(const std::string& format, const std::string& appName) {
        appRegistryProxy->RegisterFormat(format, appName);
    }
};

class AppLauncherClient {
private:
    DBus::BusDispatcher dispatcher;
    DBus::Connection conn;
    DBus::InterfaceProxy appLauncherProxy;

public:
    AppLauncherClient()
        : conn(DBus::Connection::SessionBus()), appLauncherProxy(conn, "org.example.AppLauncher", "/org/example/AppLauncher") {}

    // Метод для запуска приложения с файлом
    void LaunchApp(const std::string& appName, const std::string& file) {
        appLauncherProxy->LaunchApp(appName, file);
    }
};

int main() {
    AppRegistryClient registryClient;
    registryClient.RegisterFormat("txt", "TextEditor");
    registryClient.RegisterFormat("jpg", "ImageViewer");

    AppLauncherClient launcherClient;
    std::string format;
    std::cout << "Введите формат файла: ";
    std::cin >> format;

    std::string selectedFile;
    std::cout << "Введите имя файла: ";
    std::cin >> selectedFile;

    std::string selectedApp = registryClient.GetAppForFormat(format);
    launcherClient.LaunchApp(selectedApp, selectedFile);

    return 0;
}
