#include "settingswindownew.h"
#include "ui_settingswindownew.h"

SettingsWindowNew::SettingsWindowNew(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsWindowNew)
{
    ui->setupUi(this);
}

SettingsWindowNew::~SettingsWindowNew()
{
    delete ui;
}
