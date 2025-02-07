#pragma once
#include "pch.h"
#include "EchoServer.h"

DWORD WINAPI RandServer(LPVOID pPrm) {
    Contact* client = (Contact*)pPrm;
    char ibuf[100];
    memset(ibuf, 0, sizeof(ibuf));

    char Error[15] = "ErrorInquiry", RandomError[15] = "ErrorRandom", Start[20] = "Start Message";

    int recv_len;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 100);

    try
    {
        QueueUserAPC(ASStartMessage, client->hAcceptServer, (ULONG_PTR)_strdup(client->srvname)); 
        int random_number = distrib(gen);
        cout << "Random is " << random_number << endl;

        // доп сообщение из-за неблокир. сокета
        if ((send(client->s, Start, sizeof(Start), NULL)) == SOCKET_ERROR) {
            if (WSAGetLastError() == WSAECONNABORTED || WSAGetLastError() == WSAECONNRESET) {
                client->sthread = Contact::FINISH;
            }
            else throw  SetErrorMsgText("TimeServer Send:", WSAGetLastError());
        }

        bool work = false;
        while (!client->TimerOff) {
            client->sthread = Contact::WORK;
            if (client->TimerOff) break;
            if ((recv(client->s, ibuf, sizeof(ibuf), NULL)) == SOCKET_ERROR) {
                if (WSAGetLastError() == WSAEWOULDBLOCK) {
                    Sleep(100);
                }
                else if (WSAGetLastError() == WSAECONNABORTED || WSAGetLastError() == WSAECONNRESET) {
                    client->sthread = Contact::FINISH;
                    break;
                }
                else throw  SetErrorMsgText("RandServer Recv:", WSAGetLastError());
            }
            else {
                int clientNumber = stoi(ibuf);
                if (clientNumber != random_number) {
                    if ((send(client->s, RandomError, sizeof(RandomError), NULL)) == SOCKET_ERROR) {
                        if (WSAGetLastError() == WSAECONNABORTED || WSAGetLastError() == WSAECONNRESET) {
                            client->sthread = Contact::FINISH;
                            break;
                        }
                        else throw  SetErrorMsgText("RandServer Send:", WSAGetLastError());
                    }
                    break;
                }
                if (client->TimerOff) break;
                if ((send(client->s, ibuf, sizeof(ibuf), NULL)) == SOCKET_ERROR) {
                    if (WSAGetLastError() == WSAECONNABORTED || WSAGetLastError() == WSAECONNRESET) {
                        client->sthread = Contact::FINISH;
                        break;
                    }
                    else throw  SetErrorMsgText("RandServer Send:", WSAGetLastError());
                }
            }
        }

        QueueUserAPC(ASFinishMessage, client->hAcceptServer, (ULONG_PTR)_strdup(client->srvname)); 
        client->sthread = Contact::FINISH;
        CancelWaitableTimer(client->htimer);
    }
    catch (string errorMsgText)
    {
        client->sthread = Contact::ABORT;
        CancelWaitableTimer(client->htimer);
        cout << endl << errorMsgText;
    }
    DWORD rc = 0;
    ExitThread(rc);
}