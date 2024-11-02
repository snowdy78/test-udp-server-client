#include <RuneEngine/Engine.hpp>

struct ChatSocket : sf::UdpSocket, rn::LogicalObject
{
    using sf::UdpSocket::UdpSocket;
    ChatSocket()
    {
        setBlocking(true);
    }
    virtual ~ChatSocket() = 0;
    void type_remote_ip_address()
    {
        std::string str_ip;
        std::cout << "type remote ip address: ";
        std::cin >> str_ip;
        remote_ip_address = str_ip;
    }
    void type_port()
    {
        unsigned short port;
        std::cout << "type port: ";
        std::cin >> port;
        this->port = new unsigned short(port);
    }
    void assign_port(unsigned short port)
    {
        this->port = new unsigned short(port);
        std::cout << "my address is: " << ip_address << ":" << port << "\n";
    }
    bool portIsOpen()
    {
        return port != nullptr;
    }
    unsigned short getPort() const
    {
        return *port;
    }
    sf::IpAddress getIPv4() const
    {
        return ip_address;
    }
    sf::IpAddress getRemoteIPv4() const
    {
        return remote_ip_address;
    }
    void type_and_send_message()
    {
        if (!port)
        {
            std::cout << "port is unknown\n";
            return;
        }
        std::string str;
        std::cout << "message: ";
        std::cin >> str;
        packet.clear();
        packet.append(str.c_str(), str.size() * sizeof(char));
        Status send_code = send(packet, remote_ip_address, *port);

        if (send_code != Done)
        {
            std::cout << "Failed to send with code" << send_code << "\n";
        }
    }
    void wait_for_message()
    {
        if (!port)
        {
            std::cout << "port is unknown\n";
            return;
        }
        std::cout << "wait for message\n";

        Status status;
        do
        {
            packet.clear();
            status = receive(packet, remote_ip_address, *port);
        } while (status != Done && status != Partial);

        std::string message;
        auto c_str_message = static_cast<const char *>(packet.getData());
        for (auto ptr = c_str_message; ptr < c_str_message + packet.getDataSize(); ptr++)
        {
            message += ptr;
        }
        std::cout << message << "\n";
    }
protected:
    sf::Packet packet;

private:
    unsigned short *port = nullptr;
    sf::IpAddress ip_address = sf::IpAddress::getLocalAddress();
    sf::IpAddress remote_ip_address = "";
};
ChatSocket::~ChatSocket()
{
    delete port;
}


struct Client : ChatSocket
{
    using ChatSocket::ChatSocket;
    void start() override
    {
        type_port();
        type_remote_ip_address();
    }
    void update() override
    {
        type_and_send_message();

        wait_for_message();
    }
};

struct Server : ChatSocket
{
    using ChatSocket::ChatSocket;
    void start() override
    {
        assign_port(25565);
        int connect_code = bind(getPort(), getIPv4());
        if (connect_code != Done)
        {
            std::cout << "Failed to connect with code: " << connect_code << "\n";
            throw std::exception();
        }
        type_remote_ip_address();
    }
    void update() override
    {
        wait_for_message();
        type_and_send_message();
    }
};

ChatSocket *getSocketType()
{
    std::string c;

    while (true)
    {
        std::cout << "host or connect? (h/c): ";

        std::cin >> c;
        const std::regex client_socket{"c"};
        const std::regex server_socket{"h"};
        if (std::regex_match(c.begin(), c.end(), client_socket))
        {
            return new Client;
        }
        if (std::regex_match(c.begin(), c.end(), server_socket))
        {
            return new Server;
        }
        std::cout << "incorrect.\n";
    }
    return nullptr;
}

int main()
{
    ChatSocket *socket = getSocketType();
    sf::Packet packet;
    socket->start();

    while (true)
    {
        socket->update();
    }

    delete socket;
    std::cin.get();
    return 0;
}