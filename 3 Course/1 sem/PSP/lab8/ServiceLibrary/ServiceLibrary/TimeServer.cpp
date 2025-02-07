#pragma once
#include "pch.h"
#include "EchoServer.h"

DWORD WINAPI TimeServer(LPVOID pPrm) {
    Contact* client = (Contact*)pPrm;
    char ibuf[100];
    memset(ibuf, 0, sizeof(ibuf));

    char Error[15] = "ErrorInquiry", RandomError[15] = "ErrorTime",  Start[20] = "Start Message";

    int recv_len;

    try
    {
        QueueUserAPC(ASStartMessage, client->hAcceptServer, (ULONG_PTR)_strdup(client->srvname));
        SYSTEMTIME stt;
        GetLocalTime(&stt);
        printf("%d.%d.%d %d:%02d Server Time\n", stt.wDay, stt.wMonth, stt.wYear, stt.wHour, stt.wMinute);

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
                else throw  SetErrorMsgText("TimeServer Recv:", WSAGetLastError());
            }
            else {
                SYSTEMTIME userTime = { 0 };
                sscanf_s(ibuf, "%02hu.%02hu.%04hu %02hu:%02hu",
                    &userTime.wDay,
                    &userTime.wMonth,
                    &userTime.wYear,
                    &userTime.wHour,
                    &userTime.wMinute);
                userTime.wSecond = 0;
                userTime.wMilliseconds = 0;

                FILETIME ftCurrent, ftUser;
                SystemTimeToFileTime(&stt, &ftCurrent);
                SystemTimeToFileTime(&userTime, &ftUser);

                if (CompareFileTime(&ftCurrent, &ftUser) != 0) {
                    if ((send(client->s, RandomError, sizeof(RandomError), NULL)) == SOCKET_ERROR) {
                        if (WSAGetLastError() == WSAECONNABORTED || WSAGetLastError() == WSAECONNRESET) {
                            client->sthread = Contact::FINISH;
                            break;
                        }
                        else throw  SetErrorMsgText("TimeServer Send:", WSAGetLastError());
                    }
                    break;
                }
                if (client->TimerOff) break;
                if ((send(client->s, ibuf, sizeof(ibuf), NULL)) == SOCKET_ERROR) {
                    if (WSAGetLastError() == WSAECONNABORTED || WSAGetLastError() == WSAECONNRESET) {
                        client->sthread = Contact::FINISH;
                        break;
                    }
                    else throw  SetErrorMsgText("TimeServer Send:", WSAGetLastError());
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