// /**
//  * @file Socket_test.cc
//  * @author czy (suoni1919@gmail.com)
//  * @date 2022-07-08
//  * 
//  * @copyright Copyright (c) 2022
//  * 
//  */

// #include "Socket.h"
// #include "InetAddress.h"
// #include <thread>
// #include <unistd.h>


// void clnt() {
//     ChanNet::Socket client;
//     ChanNet::InetAddress server_addr("0.0.0.0", 6666);

//     ChanNet::InetAddress addr("0.0.0.0", 9999);
//     client.Bind(&addr);
//     client.Connect(&server_addr);
//     close(client.getFd());
// }


// void serv() {
//     ChanNet::Socket server;
//     ChanNet::InetAddress server_addr("0.0.0.0", 6666);
//     server.Bind(&server_addr);
//     //阻塞socket 仅测试功能
//     // server.setNonBlocking();
//     server.Listen();
//     ChanNet::InetAddress clnt_addr;
//     server.Accept(&clnt_addr);
// }
// /**
//  * serv 函数会阻塞住 等待链接到来 
//  * 而server.join()会等待 [client] --> [server] 成功后main结束
//  */
// int main () {
//     std::thread server (serv);
//     std::thread cilent (clnt);
    
//     cilent.join();
//     return 0;
// }