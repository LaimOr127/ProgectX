#include <iostream>
#include <map>
#include <string>
#include <dbus-c++/dbus.h>

class AppLauncher : public DBus::ObjectAdaptor {
public:
    AppLauncher(DBus::Connection &connection)
        : DBus::ObjectAdaptor(connection, "/org/example/AppLauncher") {}

    void LaunchApp(const std::string &appName, const std::string &file) {
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
