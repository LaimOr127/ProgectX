#include <iostream>
#include <map>
#include <string>
#include <dbus-c++/dbus.h>

class AppLauncher : public DBus::ObjectProxy {
public:
    AppLauncher(DBus::Connection& connection)
        : DBus::ObjectProxy(connection, "/org/example/AppLauncher", "org.example.AppLauncher") {}

    // Метод для запуска приложения с файлом
    void LaunchApp(const std::string& appName, const std::string& file) {
        std::cout << "Launching: " << appName << " with file: " << file << std::endl;
    }
};

int main() {
    DBus::default_dispatcher = &DBus::glib_integration;
    DBus::Connection conn = DBus::Connection::SessionBus();

    // Регистрация сервера AppLauncher
    AppLauncher appLauncher(conn);

    // Запуск цикла обработки событий D-Bus
    Glib::MainLoop loop;
    loop.run();

    return 0;
}
