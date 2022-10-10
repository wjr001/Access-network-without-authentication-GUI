#include <iostream>
#include <winsock2.h> //该头文件需在windows.h之前
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
    //1.初始化套接字库
    WORD socket_version = MAKEWORD(2, 2); //套接字版本
    WSADATA wsaData;
    int flag_init_socket = WSAStartup(socket_version, &wsaData);
    if (flag_init_socket != 0)
    {
        cout << "初始化套接字失败" << endl;
        return false;
    }

    //2.连接socket
    //AF_INET 指的是IPV4协议 //sock_stream 是有保障的(即能保证数据正确传送到对方)面向连接的SOCKET与tcp协议相对应
    //IPPROTO_TCP:传输层采用的协议类型
    //socket参数含义：1.网络层协议 2.传输数据的方式 3.传输层的协议类型
    SOCKET m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    const char* host_url = "192.168.180.1";
    struct hostent* host_info;
    host_info = gethostbyname(host_url);
    //host_info为空 说明没有该消息
    if (host_info == nullptr)
    {
        cout << "该主机url失败！" << endl;
        return false;
    }

    //设置服务器SocketAddr类型--即包括ip地址和端口号
    //设置必要socket地址信息  服务器地址 端口号
    //其中端口号对应相应服务 --：80--》http服务 https://blog.csdn.net/qq_25184739/article/details/70653216
    SOCKADDR_IN SockAddr;
    SockAddr.sin_port = htons(80); //80端口表示http端口
    SockAddr.sin_family = AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long*)host_info->h_addr); //请求服务器的地址 由host_info获取

    //3.连接到服务器
    int flag_connect_socket = connect(m_socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr));
    if (flag_connect_socket != 0)
    {
        cout << "connect to server fail!" << endl;
        return false;
    }

    //4.发送GET请求 
    //设置get请求报文
    //const char* req_header = "GET /HTTP/1.1\r\n"; //请求头
    //const char* total_req_header = "Host:www.baidu.com\r\nConnection: close\r\n\r\n";
    //const char* all_req_header = "GET /index.php?a=a&b=b HTTP/1.1\r\nHost:192.168.31.220\r\nConnection: close\r\n\r\n";
    const char* all_req_header = "GET /ac_portal/get_auth_url?auth_type=dingtalk&ttype=mobile HTTP/1.1\r\nHost: 192.168.180.1\r\nUser-Agent: Mozilla/5.0 (Linux; Android 11) AppleWebKit/537.36 (KHTML, like Gecko) \r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8\r\nAccept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2\r\nAccept-Encoding: gzip, deflate\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\n";
    if (send(m_socket, all_req_header, strlen(all_req_header), 0) > 0)
    {
        //5.接收服务器响应的数据
        char recvBuffer[10000];
        int recvDataLength;
        while ((recvDataLength = recv(m_socket, recvBuffer, 10000, 0)) > 0)
        {
            ofstream temp;
            temp.open("temp.temp", ios::out | ios::trunc);
            temp << "传回的数据为:\n" << endl;
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
        cout << "发送失败";
        closesocket(m_socket);
        WSACleanup();
        return false;
    }
    //6.关闭连接
    closesocket(m_socket);
    WSACleanup();
    return true;
}

void send_req()
{
    
}