#include "downloader.h"

Downloader::Downloader(QObject *parent) : QObject(parent)
{

}

void Downloader::doDownload()
{
    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    manager->get(QNetworkRequest(QUrl("http://api.ownradio.ru/v3/tracks/16f1d9a7-5325-4167-b73e-3360e55b087d/next")));
}

void Downloader::replyFinished (QNetworkReply *reply)
{
    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else
    {
        //qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        //qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();;
        //qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        //qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

        QString strReply = (QString)reply->readAll();

        //qDebug() << strReply;

        QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());

        QJsonObject jsonObj = jsonResponse.object();


        //qDebug() << jsonObj.length();

        qDebug() << "artist:" << jsonObj.value("artist").toString();
        qDebug() << "name:" << jsonObj.value("name").toString();
    }

    reply->deleteLater();
}
