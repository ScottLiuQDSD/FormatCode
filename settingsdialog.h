#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QButtonGroup>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QSpinBox>
#include <QSplitter>
#include <QWidget>
#include <QLineEdit>
#include "settingcheckbox.h"

class SettingsDialog : public QDialog
{
	Q_OBJECT
public:
	explicit SettingsDialog(QWidget *parent = 0);
//	~SettingsDialog();
	QString GetSettingOptions();
signals:
	void PushSettingToCheckBox(QString settings);
public slots:
	void ClickBtn(QAbstractButton* btn);
	void ConnectSettingCheckBox();
	void SettingToComBox();
	void SettingToSpinBox();
	void SettingToLineEdit();
	void PushSettings(QString settingOptions);
private:
	void InitBracketStyleOptionsGroup();
	void InitTabOptionsGroup();
	void InitBracketModifyOptionsGroup();
	void InitIndentationOptionsGroup();
	void InitPaddingOptionsGroup();
	void InitFormattingOptionsGroup();
	void InitObjectiveCOptionsGroup();
	void InitOtherOptionsGroup();
	void GetSetting();
	void SetSettingToComBox(QComboBox *combx, QString flagStr, QString splitStr = " ");
	void SetSettingToSpinBox(QSpinBox *spinbox, QString flagStr, QString jumpStr = "");
	void SetSettingToLineEdit(QLineEdit *lineEdit, QString flagStr, QString splitStr = " ");

private:
	QString settingResult;
	QGridLayout *gridLayout;
	//part 0-0
	QGroupBox *grpbxBracketStyleOption;
	QGridLayout *grdLytBracketStyleOption;
	QComboBox *cmbxBracketStyleOption;
	//part 0-1
	QGroupBox *grpbxTabOptions;
	QGridLayout *grdLytTabOptions;
	QHBoxLayout* hbxLytIndent;
	SettingCheckBox *chkIndent;
	QComboBox *cmbxIndentUnit;
	QSpinBox *spbxIndentCount;
	SettingCheckBox *chkIndentForceTab;
	QSpinBox *spbxIndentForceTabCount;
	//part 1
	QGroupBox *grpbxBracketModifyOptions;
	QGridLayout *grdLytBracketModifyOptions;
	SettingCheckBox *chkAttchNamespaces;
	SettingCheckBox *chkAttchInlines;
	SettingCheckBox *chkAttchClasses;
	SettingCheckBox *chkAttchExternC;
	//part 2
	QGroupBox *grpbxIndentationOptions;
	QGridLayout *grdLytIndentationOptions;
	SettingCheckBox *chkIndentClasses;
	SettingCheckBox *chkIndentModifiers;
	QHBoxLayout* hbxLytMinConditionalIndent;
	SettingCheckBox *chkMinConditionalIndent;
	QSpinBox *spbxMinConditionalIndent;
	QHBoxLayout* hbxLytMaxInstatementIndent;
	SettingCheckBox *chkMaxInstatementIndent;
	QSpinBox *spbxMaxInstatementIndent;
	SettingCheckBox *chkIndentLabels;
	SettingCheckBox *chkIndentPreprocDefine;
	SettingCheckBox *chkIndentCases;
	SettingCheckBox *chkIndentPreprocCond;
	SettingCheckBox *chkIndentNamespaces;
	SettingCheckBox *chkIndentSwitches;
	SettingCheckBox *chkIndentCol1Comments;
	//part 3
	QGroupBox *grpbxPaddingOptions;
	QGridLayout *grdLytPaddingOptions;
	SettingCheckBox *chkPadParen;
	SettingCheckBox *chkUnpadParen;
	SettingCheckBox *chkBreakBlocks;
	SettingCheckBox *chkPadParenOut;
	SettingCheckBox *chkPadHeader;
	SettingCheckBox *chkBreakBlocksAll;
	SettingCheckBox *chkPadFirstParenOut;
	SettingCheckBox *chkPadOper;
	SettingCheckBox *chkDeleteEmptyLines;
	SettingCheckBox *chkPadParenIn;
	SettingCheckBox *chkFillEmptyLines;
	//part4
	QGroupBox *grpbxFormattingOptions;
	QGridLayout *grdLytFormattingOptions;
	SettingCheckBox *chkCovertTabs;
	SettingCheckBox *chkBreakClosingBrackets;
	SettingCheckBox *chkAddBrackes;
	SettingCheckBox *chkCloseTemplates;
	SettingCheckBox *chkBreakElseIfs;
	SettingCheckBox *chkAddOneLineBracket;
	QHBoxLayout* hbxAlignPointerEqu;
	SettingCheckBox *chkAlignPointerEqu;
	QComboBox *cmbxAlignPointer;
	QHBoxLayout* hbxMaxCodeLengthEqu;
	SettingCheckBox *chkMaxCodeLengthEqu;
	QSpinBox *spbxMaxCodeLength;
	SettingCheckBox *chkRemoveBrackets;
	QHBoxLayout* hbxAlignReferenceEqu;
	SettingCheckBox *chkAlignReferenceEqu;
	QComboBox *cmbxAlignReference;
	SettingCheckBox *chkBreakAfterLogical;
	SettingCheckBox *chkKeepOneLineBlocks;
	QHBoxLayout* hbxLytModeEqu;
	SettingCheckBox *chkModeEqu;
	QComboBox *cmbxModeEqu;
	SettingCheckBox *chkRemoveCommentPrefix;
	SettingCheckBox *chkKeepOneLineStatements;
	//part 5
	QGroupBox *grpbxObjectiveCOptions;
	QGridLayout *grdLytObjectiveCOptions;
	SettingCheckBox *chkAlignMethodColon;
	SettingCheckBox *chkPadMethodPrefix;
	SettingCheckBox *chkUnpadMethodPrefix;
	QHBoxLayout* hbxPadMethodColonEqu;
	SettingCheckBox *chkPadMethodColonEqu;
	QComboBox *cmbxPadMethodColonEqu;
	//part 6
	QGroupBox *grpbxOtherOptions;
	QGridLayout *grdLytOtherOptions;
	QHBoxLayout* hbxSuffixEqu;
	SettingCheckBox *chkSuffixEqu;
	QLineEdit *lineEdtSuffix;
	SettingCheckBox *chkSuffixNone;
	SettingCheckBox *chkRecursive;
	QHBoxLayout *hbxExcludeEqu;
	SettingCheckBox *chkExclude;
	QLineEdit *lineEdtExclude;
	SettingCheckBox *chkIgnoreExcludeErrors;
	SettingCheckBox *chkIgnoreExcludeErrorsX;
	SettingCheckBox *chkErrorsToStdout;
	SettingCheckBox *chkPreserveDate;
	SettingCheckBox *chkVerbose;
	SettingCheckBox *chkFormatted;
	SettingCheckBox *chkQuite;
	QHBoxLayout* hbxLineEndEqu;
	SettingCheckBox *chkLineEndEqu;
	QComboBox *cmbxLineEnd;

	QDialogButtonBox *buttonBox;
	bool initSucceed;
};

#endif // SETTINGSDIALOG_H
