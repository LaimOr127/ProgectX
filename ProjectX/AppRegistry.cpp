#include <iostream>
#include <map>
#include <string>
#include <dbus-c++/dbus.h>

class AppRegistry : public DBus::ObjectProxy {
private:
    std::map<std::string, std::string> formatAppMap;

public:
    AppRegistry(DBus::Connection& connection)
        : DBus::ObjectProxy(connection, "/org/example/AppRegistry", "org.example.AppRegistry") {}

    // ����� ��� ����������� ������� � ����������
    void RegisterFormat(const std::string& format, const std::string& appName) {
        formatAppMap[format] = appName;
        std::cout << "Registered: Format - " << format << ", App - " << appName << std::endl;
    }
};

int main() {
    DBus::default_dispatcher = &DBus::glib_integration;
    DBus::Connection conn = DBus::Connection::SessionBus();

    // ����������� ������� AppRegistry
    AppRegistry appRegistry(conn);

    // ������ ����� ��������� ������� D-Bus
    Glib::MainLoop loop;
    loop.run();

    return 0;
}
