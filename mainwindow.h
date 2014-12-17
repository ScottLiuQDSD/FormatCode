#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingsdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
	void FindSubDir(QString subDirPath);
	bool FormatCodeFileWithAstyle(QString filePath);
	bool InitWithSavedSettings();
	bool SaveSettings();
private slots:
	void on_btnUseDefault_clicked();

	void on_btnSettings_clicked();

	void SetSettingOptions();
private:
    Ui::MainWindow *ui;
	SettingsDialog *dialog;
	QString settingOptions;
};

#endif // MAINWINDOW_H
