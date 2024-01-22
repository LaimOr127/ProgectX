#include <iostream>
#include <map>
#include <string>
#include <dbus-c++/dbus.h>

class AppRegistry : public DBus::ObjectAdaptor {
private:
    std::map<std::string, std::string> formatAppMap;

public:
    AppRegistry(DBus::Connection &connection)
        : DBus::ObjectAdaptor(connection, "/org/example/AppRegistry") {}

    void RegisterFormat(const std::string &format, const std::string &appName) {
        formatAppMap[format] = appName;
        std::cout << "Registered: Format - " << format << ", App - " << appName << std::endl;
    }
};

int main() {
    DBus::default_dispatcher = &DBus::glib_integration;
    DBus::Connection conn = DBus::Connection::SessionBus();

    // Регистрация сервера AppRegistry
    AppRegistry appRegistry(conn);

    // Запуск цикла обработки событий D-Bus
    Glib::MainLoop loop;
    loop.run();

    return 0;
}
