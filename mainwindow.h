#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>

class QListWidgetItem;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void sendRequest();
    void processReply(QNetworkReply *reply);
    void changeActiveRequest(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager networkAccessManager;
    void initializeCollection();
    void initializeConnections();
    void initializeHeaderTables();
    void initializeVerbComboBox();
};
#endif // MAINWINDOW_H
