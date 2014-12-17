#ifndef SETTINGCHECKBOX_H
#define SETTINGCHECKBOX_H

#include <QCheckBox>

class SettingCheckBox : public QCheckBox
{
	Q_OBJECT
public:
	explicit SettingCheckBox(QString text, QWidget *parent = 0);
	QString GetSettingText();
signals:

public slots:
	void GotInitSetting(QString initSettings);
};

#endif // SETTINGCHECKBOX_H
