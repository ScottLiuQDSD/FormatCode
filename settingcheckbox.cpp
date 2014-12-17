#include "settingcheckbox.h"

SettingCheckBox::SettingCheckBox(QString text, QWidget *parent) :
	QCheckBox(text, parent)
{
}
QString SettingCheckBox::GetSettingText()
{
	if (true == this->isChecked()) {
		QString tex = this->text();
		if (false == tex.contains("=")) {
			tex += " ";
		}
		return tex;
	}
	return QString();
}
void SettingCheckBox::GotInitSetting(QString initSettings)
{
	if (initSettings.contains(this->text())) {
		this->setChecked(true);
		emit clicked(true);
	}
}
