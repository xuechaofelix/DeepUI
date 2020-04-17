#ifndef CONFIGURATIONVIEW_H
#define CONFIGURATIONVIEW_H


#define ROBUSTNESS_TYPE_LINFBALL "LINFBALL"
#define ROBUSTNESS_TYPE_BRIGHTNESS "brightness"
#define ROBUSTNESS_TYPE_CUSTOMBOX "CUSTOMBOX"

#define UI_DELTA_PRECISION 3

#include <QWidget>
#include "project.h"

namespace Ui {
class ConfigurationView;
}

class ConfigurationView : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigurationView(Project * pro, QWidget *parent = nullptr);
    ~ConfigurationView();

    QString getRobustnessType();
    double getDelta();

    void changeNetworkFile(QString path, QString fileName);
    void changeInputFile(QString path, QString fileName);

private slots:
    void on_importNetwork_clicked();


    void on_chooseInput_clicked();

    void on_robustnessType_currentIndexChanged(const QString &arg1);

    void changeSlideValue(double value);
    void changeSpinboxValue(int value);

    void on_run_clicked();

private:
    Ui::ConfigurationView *ui;

    Project * project = nullptr;
    QString roubustnessType = ROBUSTNESS_TYPE_LINFBALL;

    void importNetwork();
    void importInputFile();

signals:
    void run();
    void SIGNAL_importNetwork();
    void SIGNAL_importInput();

};

#endif // CONFIGURATIONVIEW_H
