/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2019 Tianjin KYLIN Information Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */
#ifndef SHORTCUT_H
#define SHORTCUT_H

#include <QObject>
#include <QtPlugin>
#include <QProcess>
#include <QThread>
#include <QListWidget>
#include <QDBusInterface>

#include "shell/interface.h"

#include "keymap.h"
#include "addshortcutdialog.h"
#include "getshortcutworker.h"
#include "showallshortcut.h"
#include "HoverWidget/hoverwidget.h"
#include "ImageUtil/imageutil.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Shortcut; }
QT_END_NAMESPACE

typedef struct _KeyEntry KeyEntry;

struct _KeyEntry{
//    int keyval;
    QString gsSchema;
    QString keyStr;
    QString valueStr;
    QString descStr;

    QString gsPath;
    QString nameStr;
    QString bindingStr;
    QString actionStr;
};

Q_DECLARE_METATYPE(KeyEntry *)

class Shortcut : public QObject, CommonInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kycc.CommonInterface")
    Q_INTERFACES(CommonInterface)

public:
    Shortcut();
    ~Shortcut();

public:
    QString get_plugin_name() Q_DECL_OVERRIDE;
    int get_plugin_type() Q_DECL_OVERRIDE;
    QWidget *get_plugin_ui() Q_DECL_OVERRIDE;
    void plugin_delay_control() Q_DECL_OVERRIDE;
    const QString name() const  Q_DECL_OVERRIDE;

public:
    void setupComponent();
    void setupConnect();
    void initFunctionStatus();

    void appendGeneralItems();
    void appendCustomItems();
    void buildCustomItem(KeyEntry * nkeyEntry);

    void initItemsStyle(QListWidget * listWidget);
    void initGeneralItemsStyle();
    void initCustomItemsStyle();

    void createNewShortcut(QString path, QString name, QString exec);
    void deleteCustomShortcut(QString path);

    void newBindingRequest(QList<int> keyCode);

    QString getBindingName(QList<int> keyCode);
    bool keyIsForbidden(QString key);
    void connectToServer();

public:
    QStringList showList;

protected:
//    bool event(QEvent *event);
//    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::Shortcut *ui;

    QString pluginName;
    int pluginType;
    QWidget * pluginWidget;

    HoverWidget *addWgt;

private:
    QThread * pThread;
    GetShortcutWorker * pWorker;

    KeyMap * pKeyMap;

    addShortcutDialog * addDialog;
    ShowAllShortcut * showDialog;
    QDBusInterface *cloudInterface;

private slots:
    void shortcutChangedSlot();

Q_SIGNALS:
    void hideDelBtn();


};
#endif // SHORTCUT_H
