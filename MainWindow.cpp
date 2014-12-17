#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QStringList>
#include <QProcess>
#include <QDebug>
#include <QElapsedTimer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow), settingOptions("--style=linux --add-brackets --mode=c"),
	dialog(NULL)
{
    ui->setupUi(this);
	ui->label_recommoned->setFixedSize(ui->label_recommoned->size());
	ui->btnUseDefault->setFixedSize(ui->btnUseDefault->size());
	ui->centralWidget->setLayout(ui->gridLayout);
	ui->label_CommandLine->setText(settingOptions);

	ui->label_CommandLine->setWordWrap(true);
	InitWithSavedSettings();
}
MainWindow::~MainWindow()
{
	delete dialog;
    delete ui;
}
// find file which contains saved settings
// if found, load it
// if not found, creat one and save with default settings
bool MainWindow::InitWithSavedSettings()
{
	bool initOk = false;
	QString saveFilePath;
	QDir dir;
	QString pathCur = dir.currentPath();
	saveFilePath = pathCur + "/SavedSetting.data";
	QFile file(saveFilePath);
	if (false == file.exists()) {
		file.open(QIODevice::WriteOnly);
		file.write(settingOptions.toLatin1());
		file.flush();
	} else {
		file.open(QIODevice::ReadOnly);
		int fileSize = file.size();
		QString settingContent = file.readAll();
		if (settingContent.size() < fileSize) {
			qDebug("Why? cannot read all data in setting file.");
			return initOk;
		}
		settingOptions = settingContent;
		ui->label_CommandLine->setText(settingOptions);
		int p1 = settingOptions.indexOf("--style=linux",Qt::CaseInsensitive);
		int p2 = settingOptions.indexOf("--add-brackets",Qt::CaseInsensitive);
		int p3 = settingOptions.indexOf("--mode=c",Qt::CaseInsensitive);
		QStringList strlist = settingOptions.split("--", QString::SkipEmptyParts);
		int si = strlist.size();
		if (-1 != p1 && -1 != p2 && -1 != p3 && 3 == si) {
			ui->label_recommoned->setText("Recommoned");
		} else {
			ui->label_recommoned->setText("User defined");
		}

	}
	file.close();
	initOk = true;
	return initOk;
}
bool MainWindow::SaveSettings()
{
	bool saveSettingOk = false;
	QString saveFilePath;
	QDir dir;
	QString pathCur = dir.currentPath();
	saveFilePath = pathCur + "/SavedSetting.data";
	QFile file(saveFilePath);
	bool isOpen = false;
	if (false == file.exists()) {
		isOpen = file.open(QIODevice::WriteOnly);
	} else {
		isOpen = file.open(QIODevice::WriteOnly | QIODevice::Truncate);
	}
	if (false == isOpen) {
		qDebug("File cannot open to save data.");
	} else {
		file.write(settingOptions.toLatin1());
		file.flush();
		saveSettingOk = true;
	}
	file.close();

	return saveSettingOk;
}
void MainWindow::FindSubDir(QString subDirPath)
{
	QDir pathDir(subDirPath);
//	QStringList filters;
//	filters << "*.h" << "*.cpp" << "*.cxx" << "*.cc";
//	pathDir.setNameFilters(filters);
	foreach(QFileInfo mfi ,pathDir.entryInfoList()) {
		if(mfi.isFile()) {
			ui->textEdit->insertPlainText("File : " + mfi.filePath() + "\n");
			if (mfi.suffix().compare("h", Qt::CaseInsensitive) == 0 ||
				mfi.suffix().compare("ic", Qt::CaseInsensitive) == 0 ||
				mfi.suffix().compare("cpp", Qt::CaseInsensitive) == 0) {
				if (false == FormatCodeFileWithAstyle(mfi.filePath())) {
					break;
				}
			}
		} else {
			if(mfi.fileName()=="." || mfi.fileName() == "..") {
				continue;
			}
			ui->textEdit->insertPlainText("Entry Dir : " + mfi.absoluteFilePath() + "\n");
			FindSubDir(mfi.absoluteFilePath());
		}
	}
}
bool MainWindow::FormatCodeFileWithAstyle(QString filePath)
{
	QDir dir;
	QString pathCur = dir.currentPath();
	QString pathAstyle = pathCur + "/astyle.exe";
	QFile astyle(pathAstyle);
	if (false == astyle.exists()) {
		qDebug(pathAstyle.toLatin1());
		qDebug("Astyle.exe not found, please make sure the exe file here.");
		QMessageBox::critical(this, "Sorry",
							  "I didn't found some file very IMPORTANT, please make sure you got the whole application.");
		return false;
	}
	//qDebug("current path %s", pathCur.toLatin1().data());
	QProcess p(0);
	p.start("cmd");
	p.waitForStarted();
	QString command = QString("cd %1/debug\n").arg(pathCur);
	p.write(command.toLatin1());
	QString action_cmd = QString("astyle.exe %1 %2\n").arg(settingOptions).arg(filePath);
	p.write(action_cmd.toLatin1());
	p.closeWriteChannel();
	p.waitForFinished();
	ui->textEdit->insertPlainText(QString::fromLocal8Bit(p.readAllStandardOutput()).toLatin1() + "\n");
	QElapsedTimer t;
	t.start();
	while(t.elapsed()<50) {
		QCoreApplication::processEvents();
	}
	return true;
}
void MainWindow::on_btnUseDefault_clicked()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory contains C++ code"),
													"/home",
													QFileDialog::ShowDirsOnly
													| QFileDialog::DontResolveSymlinks);
	ui->textEdit->insertPlainText(dir + "\n");
	//qDebug(dir.toLatin1());
	ui->textEdit->setEnabled(false);
	FindSubDir(dir);
	ui->textEdit->setEnabled(true);
	qDebug("All Files format finished.");
	ui->textEdit->insertPlainText("All Files format finished.\n");
}
void MainWindow::on_btnSettings_clicked()
{
	if (NULL == dialog) {
		dialog = new SettingsDialog(this);
		connect(dialog, SIGNAL(accepted()), this, SLOT(SetSettingOptions()));
	}
	dialog->PushSettings(settingOptions);
	dialog->show();
	dialog->exec();
}
void MainWindow::SetSettingOptions()
{
	if (NULL == dialog) {
		return;
	} else {
		QString tmpOptions = dialog->GetSettingOptions();
		if (QMessageBox::Apply == QMessageBox::warning(NULL, "Attendion", "Are you sure to use astyle with the option : " + tmpOptions,
													   QMessageBox::Cancel, QMessageBox::Apply)) {
			settingOptions = tmpOptions;
			ui->label_CommandLine->setText(settingOptions);
			SaveSettings();
		}
		int p1 = settingOptions.indexOf("--style=linux",Qt::CaseInsensitive);
		int p2 = settingOptions.indexOf("--add-brackets",Qt::CaseInsensitive);
		int p3 = settingOptions.indexOf("--mode=c",Qt::CaseInsensitive);
		QStringList strlist = settingOptions.split("--", QString::SkipEmptyParts);
		int si = strlist.size();
		if (-1 != p1 && -1 != p2 && -1 != p3 && 3 == si) {
			ui->label_recommoned->setText("Recommoned");
		} else {
			ui->label_recommoned->setText("User defined");
		}
	}
}
