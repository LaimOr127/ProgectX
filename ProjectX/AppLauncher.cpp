#include <iostream>
#include <map>
#include <string>
#include <dbus-c++/dbus.h>

class AppLauncher : public DBus::ObjectProxy {
public:
    AppLauncher(DBus::Connection& connection)
        : DBus::ObjectProxy(connection, "/org/example/AppLauncher", "org.example.AppLauncher") {}

    // ����� ��� ������� ���������� � ������
    void LaunchApp(const std::string& appName, const std::string& file) {
        std::cout << "Launching: " << appName << " with file: " << file << std::endl;
    }
};

int main() {
    DBus::default_dispatcher = &DBus::glib_integration;
    DBus::Connection conn = DBus::Connection::SessionBus();

    // ����������� ������� AppLauncher
    AppLauncher appLauncher(conn);

    // ������ ����� ��������� ������� D-Bus
    Glib::MainLoop loop;
    loop.run();

    return 0;
}
