/*
 * Copyright (C) by Dominik Schmidt <dev@dominik-schmidt.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */


#ifndef SOCKETAPI_H
#define SOCKETAPI_H

#include <QWeakPointer>
#include <QTcpSocket>
#include <QTcpServer>

#include "mirall/syncfileitem.h"

class QUrl;
class QLocalSocket;
class QStringList;

namespace Mirall {

class SocketApi : public QObject
{
Q_OBJECT

public:
    SocketApi(QObject* parent, const QUrl& localFile);
    virtual ~SocketApi();

public slots:
    void slotUpdateFolderView(const QString&);

private slots:
    void slotNewConnection();
    void onLostConnection();
    void slotReadSocket();
    void slotJobCompleted(const QString &, const SyncFileItem &);

private:
    void sendMessage(QTcpSocket* socket, const QString& message);
    void broadcastMessage(const QString& message);

    Q_INVOKABLE void command_RETRIEVE_FOLDER_STATUS(const QString& argument, QTcpSocket* socket);
    Q_INVOKABLE void command_RETRIEVE_FILE_STATUS(const QString& argument, QTcpSocket* socket);

private:
    QTcpServer *_localServer;
    QList<QTcpSocket*> _listeners;
};

}
#endif // SOCKETAPI_H
