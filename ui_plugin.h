#ifndef UI_PLUGIN_H
#define UI_PLUGIN_H

#include <QDialog>
#include <QWidget>
#include <QStringListModel>

#include <QMenu>
#include <QAction>
#include <QDir>


#include "choose.h"

namespace Ui {
class UI_Plugin;
}

class UI_Plugin : public QDialog
{
    Q_OBJECT

public:
    explicit UI_Plugin(QString dataFilePath = "resources/", QString unaddedPluginFileName="unaddedPlugin.txt", QString addedPluginFileName="addedPlugin.txt", QWidget *parent = nullptr);
    ~UI_Plugin() override;

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_addPlugin_clicked();

    void on_removePlugin_clicked();

    void on_bottom_clicked();

    void on_down_clicked();

    void on_up_clicked();

    void on_top_clicked();


    void on_added_list_pressed(const QModelIndex &index);

    void on_unadded_list_pressed(const QModelIndex &index);

    void importNewPlugin();

    void deletePlugin();

    void on_unadded_list_customContextMenuRequested(const QPoint &pos);
private:
    QString dataFilePath;
    QString unaddedPluginFileName;
    QString addedPluginFileName;
    void loadPlugin(QStringList * unAddedPlugin, QStringList * addedPlugin);
    void savePlugin();

    Ui::UI_Plugin *ui;
    QStringListModel * unAddedModel;
    QStringListModel * addedModel;

    QMenu *cmenu;
};

#endif // UI_PLUGIN_H
