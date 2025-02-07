#pragma once
#include <random>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <list>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

extern HANDLE hAcceptServer, hDispatchServer;
extern int port;
extern CRITICAL_SECTION ListContactCriticalSection;

struct Contact
{
    //состояние сервера подключения
    enum TE {
        EMPTY,              // пустой элемент списка подключений 
        ACCEPT,             // подключен, но не обслуживается
        CONTACT             // передан обслуживающему серверу  
    }    type;

    // состояние обслуживающего сервера
    enum ST {
        WORK,               // идет обмен данными с клиентом
        ABORT,              // обслуживающий сервер завершился ненормально 
        TIMEOUT,            // обслуживающий сервер завершился по таймеру 
        FINISH              // обслуживающий сервер завершился  нормально 
    }      sthread;

    // для хранения параметров соединения
    SOCKET      s;         //сокет для обмена данными с клиентом
    SOCKADDR_IN prms;      //параметры  сокета 
    int         lprms;     //длина prms 


    HANDLE      hthread;   //дескриптор потока  EchoServer
    HANDLE      htimer;    //дескриптор ожидающего таймера, позволяющего ограничить время работы обслуживающего процесса

    bool        TimerOff;  // метка срабатывания таймера
    bool        CloseConn;  // метка завершения обслуживания

    //диагностирующего сообщения и символических имен обрабатывающих потоков.
    char msg[50];           // сообщение 
    char srvname[15];       // имя обслуживающего потока 

    HANDLE hAcceptServer; // Handle обслуживающего потока

    Contact(TE t = EMPTY, const char* namesrv = "") // конструктор 
    {
        memset(&prms, 0, sizeof(SOCKADDR_IN));
        lprms = sizeof(SOCKADDR_IN); //размер сокета
        type = t;
        strcpy_s(srvname, namesrv);
        msg[0] = 0;
        CloseConn = false;
        TimerOff = false;
    };

    void SetST(ST sth, const char* m = "") {
        sthread = sth;
        strcpy_s(msg, m);
    }
};

typedef list<Contact> ListContact;
extern ListContact Contacts;
enum TalkersCommand { START, STOP, EXIT, STATISTICS, WAIT, SHUTDOWN, GETCOMMAND };
string GetErrorMsgText(int code);
string SetErrorMsgText(string msgText, int code);

#define AS_SQUIRT 10

string GetErrorMsgText(int code);
string SetErrorMsgText(string msgText, int code);

#define AS_SQUIRT 10

bool AcceptCycle(int squirt, SOCKET* s);
void CommandsCycle(TalkersCommand& cmd, SOCKET* s);
DWORD WINAPI AcceptServer(LPVOID pPrm);

DWORD WINAPI DispatchServer(LPVOID pPrm);
DWORD WINAPI EchoServer(LPVOID pPrm);
DWORD WINAPI RandServer(LPVOID pPrm);
DWORD WINAPI TimeServer(LPVOID pPrm);

void CALLBACK ASStartMessage(ULONG_PTR Lprm);
void CALLBACK ASFinishMessage(ULONG_PTR Lprm);

#pragma endregion