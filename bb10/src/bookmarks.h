/*
  Copyright (C) 2017 Michal Kosciesza <michal@mkiol.net>

  This file is part of Zimpedia application.

  This Source Code Form is subject to the terms of
  the Mozilla Public License, v.2.0. If a copy of
  the MPL was not distributed with this file, You can
  obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef BOOKMARKS_H
#define BOOKMARKS_H

#ifdef BB10
#include <QVariantList>
#endif
#ifdef SAILFISH
#include <QJsonArray>
#endif
#include <QList>
#include <QString>
#include <QObject>

class Bookmarks : public QObject
{
    Q_OBJECT
    Q_PROPERTY (bool busy READ getBusy NOTIFY busyChanged)

public:

    struct Bookmark {
        QString title;
        QString url;
        QString favicon;
        QString zimUuid;
        QString zimTitle;
        QString zimLanguage;
        bool valid;

        bool operator< (const Bookmark &b) const {
            return title < b.title;
        }
    };

    static Bookmarks* instance();
    Q_INVOKABLE void addBookmark(const QString &title,
                                 const QString &url,
                                 const QString &favicon);
    Q_INVOKABLE void updateBookmark(const QString &oldUrl,
                                    const QString &title,
                                    const QString &url,
                                    const QString &favicon);
    Q_INVOKABLE void deleteBookmark(const QString &url);
    Q_INVOKABLE const QString changeUuid(const QString &url, const QString &newUuid);
    Q_INVOKABLE bool validateUrl(const QString &url);

    void init();
    QList<Bookmark> getBookmarks();
    bool getBusy();

signals:
    void busyChanged();
    void bookmarkAdded();
    void bookmarkDeleted();
    void bookmarkUpdated();
    void bookmarkExists();

private slots:
    void finderBusyHandler();

private:
    static const QString bookmarkFilename;
    static Bookmarks *inst;

    bool busy;

    explicit Bookmarks(QObject *parent = 0);
    const QString articleUrl(const QString &url);
#ifdef BB10
    QVariantList readBookmarks();
    bool writeBookmarks(const QVariantList &json);
#endif
#ifdef SAILFISH
    QJsonArray readBookmarks();
    bool writeBookmarks(const QJsonArray &json);
#endif
};

#endif // BOOKMARKS_H
