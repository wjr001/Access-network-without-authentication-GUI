#include <iostream>
#include <winsock2.h> //��ͷ�ļ�����windows.h֮ǰ
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
#include "WindowsProject1.h"
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable : 4996)

bool HttpGetReq()
{
    //1.��ʼ���׽��ֿ�
    WORD socket_version = MAKEWORD(2, 2); //�׽��ְ汾
    WSADATA wsaData;
    int flag_init_socket = WSAStartup(socket_version, &wsaData);
    if (flag_init_socket != 0)
    {
        cout << "��ʼ���׽���ʧ��" << endl;
        return false;
    }

    //2.����socket
    //AF_INET ָ����IPV4Э�� //sock_stream ���б��ϵ�(���ܱ�֤������ȷ���͵��Է�)�������ӵ�SOCKET��tcpЭ�����Ӧ
    //IPPROTO_TCP:�������õ�Э������
    //socket�������壺1.�����Э�� 2.�������ݵķ�ʽ 3.������Э������
    SOCKET m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    const char* host_url = "192.168.180.1";
    struct hostent* host_info;
    host_info = gethostbyname(host_url);
    //host_infoΪ�� ˵��û�и���Ϣ
    if (host_info == nullptr)
    {
        cout << "������urlʧ�ܣ�" << endl;
        return false;
    }

    //���÷�����SocketAddr����--������ip��ַ�Ͷ˿ں�
    //���ñ�Ҫsocket��ַ��Ϣ  ��������ַ �˿ں�
    //���ж˿ںŶ�Ӧ��Ӧ���� --��80--��http���� https://blog.csdn.net/qq_25184739/article/details/70653216
    SOCKADDR_IN SockAddr;
    SockAddr.sin_port = htons(80); //80�˿ڱ�ʾhttp�˿�
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long*)host_info->h_addr); //����������ĵ�ַ ��host_info��ȡ

    //3.���ӵ�������
    int flag_connect_socket = connect(m_socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr));
    if (flag_connect_socket != 0)
    {
        cout << "connect to server fail!" << endl;
        return false;
    }

    //4.����GET���� 
    //����get������
    //const char* req_header = "GET /HTTP/1.1\r\n"; //����ͷ
    //const char* total_req_header = "Host:www.baidu.com\r\nConnection: close\r\n\r\n";
    //const char* all_req_header = "GET /index.php?a=a&b=b HTTP/1.1\r\nHost:192.168.31.220\r\nConnection: close\r\n\r\n";
    const char* all_req_header = "GET /ac_portal/get_auth_url?auth_type=dingtalk&ttype=mobile HTTP/1.1\r\nHost: 192.168.180.1\r\nUser-Agent: Mozilla/5.0 (Linux; Android 11) AppleWebKit/537.36 (KHTML, like Gecko) \r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\r\nAccept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2\r\nAccept-Encoding: gzip, deflate\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\n";
    if (send(m_socket, all_req_header, strlen(all_req_header), 0) > 0)
    {
        //5.���շ�������Ӧ������
        char recvBuffer[10000];
        int recvDataLength;
        while ((recvDataLength = recv(m_socket, recvBuffer, 10000, 0)) > 0)
        {
            ofstream temp;
            temp.open("temp.temp", ios::out | ios::trunc);
            temp << "���ص�����Ϊ:\n" << endl;
            int i = 0;
            while (recvBuffer[i] >= 32 || recvBuffer[i] == '\n' || recvBuffer[i] == '\r')
            {

                temp << recvBuffer[i];
                i += 1;
            }
            temp.close();
            break;
        }

    }
    else
    {
        cout << "����ʧ��";
        closesocket(m_socket);
        WSACleanup();
        return false;
    }
    //6.�ر�����
    closesocket(m_socket);
    WSACleanup();
    return true;
}

void send_req()
{
    
}