#ifndef THTTPSOCKET_H
#define THTTPSOCKET_H

#include <QTcpSocket>
#include <QByteArray>
#include <QDateTime>
#include <THttpRequest>
#include <TTemporaryFile>
#include <TGlobal>
#ifdef Q_OS_UNIX
# include "tfcore_unix.h"
#endif


class T_CORE_EXPORT THttpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    THttpSocket(QObject *parent = 0);
    virtual ~THttpSocket();

    QList<THttpRequest> read();
    bool canReadRequest() const;
    qint64 write(const THttpHeader *header, QIODevice *body);
    int idleTime() const;
    bool setSocketDescriptor(qintptr socketDescriptor, SocketState socketState = ConnectedState, OpenMode openMode = ReadWrite);

protected:
    qint64 writeRawData(const char *data, qint64 size);

protected slots:
    void readRequest();

signals:
    void newRequest();

private:
    Q_DISABLE_COPY(THttpSocket)

    qint64 lengthToRead;
    QByteArray readBuffer;
    TTemporaryFile fileBuffer;
    QDateTime lastProcessed;

    friend class TActionThread;
};

#endif // THTTPSOCKET_H
