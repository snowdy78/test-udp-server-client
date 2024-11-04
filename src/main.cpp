#include <RuneEngine/Engine.hpp>

struct ChatSocket : sf::UdpSocket, rn::LogicalObject
{
    using sf::UdpSocket::UdpSocket;
    ChatSocket()
    {
        setBlocking(true);
    }
    virtual ~ChatSocket() = 0;
    void type_remote_address()
    {
        std::cout << "type remote address 'ip:port': ";
        std::string address;
        std::cin >> address;
        std::regex ip_port_rgx(R"(([0-9]*\.[0-9]*\.[0-9]*\.[0-9]*|local|l):([0-9]{5}))");
        std::smatch matches;
        if (std::regex_search(address, matches, ip_port_rgx))
        {
            if (matches.size() == 3)
            {
                remote_ip_address = std::regex_match(address, std::regex("l|local"))
                    ? sf::IpAddress::getLocalAddress()
                    : sf::IpAddress(matches[1]);
                remote_port = new unsigned short(std::stoi(matches[2]));
            }
        }
    }
    void type_port()
    {
        unsigned short port;
        std::cout << "type port: ";
        std::cin >> port;
        this->port = new unsigned short(port);
        std::cout << "my address is: " << ip_address << ":" << port << "\n";
    }
    void assign_port(unsigned short port)
    {
        this->port = new unsigned short(port);
        std::cout << "my address is: " << ip_address << ":" << port << "\n";
    }
    bool portIsOpen() const
    {
        return port != nullptr;
    }
    unsigned short getPort() const
    {
        return *port;
    }
    unsigned short getRemotePort() const
    {
        return *remote_port;
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
        std::getline(std::cin, str);
        packet.clear();
        packet.append(str.c_str(), str.size() * sizeof(char));
        Status send_code = send(packet, remote_ip_address, *remote_port);

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
            status = receive(packet, remote_ip_address, *remote_port);
        } while (status != Done && status != Partial);
        size_t size = packet.getDataSize();
        char *p = new char[size + 1];
        std::memcpy(p, packet.getData(), size);
        *(p + size) = '\0';
        std::cout << p << "\n";
        packet.clear();
        delete[] p;
    }
protected:
    sf::Packet packet{};

private:
    unsigned short *remote_port = nullptr;
    unsigned short *port = nullptr;
    sf::IpAddress ip_address = sf::IpAddress::getLocalAddress();
    sf::IpAddress remote_ip_address = "";
};
ChatSocket::~ChatSocket()
{
    delete port;
    delete remote_port;
}


struct Client : ChatSocket
{
    using ChatSocket::ChatSocket;
    void start() override
    {
        type_port();
        type_remote_address();
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
        type_port();
        int connect_code = bind(getPort(), getIPv4());
        if (connect_code != Done)
        {
            std::cout << "Failed to connect with code: " << connect_code << "\n";
            throw std::exception();
        }
        type_remote_address();
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
        const std::regex client_socket{"c|connect", std::regex_constants::icase};
        const std::regex server_socket{"h|host", std::regex_constants::icase};
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

    try
    {
        socket->start();

        while (true)
        {
            socket->update();
        }
    } catch (std::exception &err)
    {
        std::cin.get();
        delete socket;
        throw err;
    }

    std::cin.get();
    delete socket;
    return 0;
}