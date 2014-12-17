#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
	QDialog(parent), settingResult(""),initSucceed(false)
{
	gridLayout = new QGridLayout(this);

	try {
		InitBracketStyleOptionsGroup();
		InitTabOptionsGroup();
		InitBracketModifyOptionsGroup();
		InitIndentationOptionsGroup();
		InitPaddingOptionsGroup();
		InitFormattingOptionsGroup();
		InitObjectiveCOptionsGroup();
		InitOtherOptionsGroup();
		initSucceed = true;
	} catch (...) {
		initSucceed = false;
		return;
	}

	buttonBox = new QDialogButtonBox(Qt::Orientation::Horizontal);
	buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Apply);
	connect(buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(ClickBtn(QAbstractButton*)));

	gridLayout->addWidget(grpbxBracketStyleOption, 0, 0, 1, 1);
	gridLayout->addWidget(grpbxTabOptions, 0, 1, 1, 1);
	gridLayout->addWidget(grpbxBracketModifyOptions, 1, 0, 1, 2);
	gridLayout->addWidget(grpbxIndentationOptions, 2, 0, 1, 2);
	gridLayout->addWidget(grpbxPaddingOptions, 3, 0, 1, 2);
	gridLayout->addWidget(grpbxFormattingOptions, 4, 0, 1, 2);
	gridLayout->addWidget(grpbxObjectiveCOptions, 5, 0, 1, 2);
	gridLayout->addWidget(grpbxOtherOptions, 6, 0, 1, 2);
	gridLayout->addWidget(buttonBox, 7, 1, 1, 1);

	gridLayout->setColumnStretch(0, 1);
	gridLayout->setColumnStretch(1, 1);
	ConnectSettingCheckBox();
}
//SettingsDialog::~SettingsDialog()
//{
//	//part 0-0
//	delete cmbxBracketStyleOption;
//	delete grdLytBracketStyleOption;
//	delete grpbxBracketStyleOption;
//	//part 0-1
//	delete chkIndent;
//	delete cmbxIndentUnit;
//	delete spbxIndentCount;
//	delete chkIndentForceTab;
//	delete spbxIndentForceTabCount;
//	delete hbxLytIndent;
//	delete grdLytTabOptions;
//	delete grpbxTabOptions;
//	//part 1
//	delete chkAttchNamespaces;
//	delete chkAttchInlines;
//	delete chkAttchClasses;
//	delete chkAttchExternC;
//	delete grdLytBracketModifyOptions;
//	delete grpbxBracketModifyOptions;
//	//part 2
//	delete chkIndentClasses;
//	delete chkIndentModifiers;
//	delete chkMinConditionalIndent;
//	delete spbxMinConditionalIndent;
//	delete chkMaxInstatementIndent;
//	delete spbxMaxInstatementIndent;
//	delete chkIndentLabels;
//	delete chkIndentPreprocDefine;
//	delete chkIndentCases;
//	delete chkIndentPreprocCond;
//	delete chkIndentNamespaces;
//	delete chkIndentSwitches;
//	delete chkIndentCol1Comments;
//	delete hbxLytMaxInstatementIndent;
//	delete hbxLytMinConditionalIndent;
//	delete grdLytIndentationOptions;
//	delete grpbxIndentationOptions;
//	//part 3
//	delete chkPadParen;
//	delete chkUnpadParen;
//	delete chkBreakBlocks;
//	delete chkPadParenOut;
//	delete chkPadHeader;
//	delete chkBreakBlocksAll;
//	delete chkPadFirstParenOut;
//	delete chkPadOper;
//	delete chkDeleteEmptyLines;
//	delete chkPadParenIn;
//	delete chkFillEmptyLines;
//	delete grdLytPaddingOptions;
//	delete grpbxPaddingOptions;
//	//part4
//	delete chkCovertTabs;
//	delete chkBreakClosingBrackets;
//	delete chkAddBrackes;
//	delete chkCloseTemplates;
//	delete chkBreakElseIfs;
//	delete chkAddOneLineBracket;
//	delete cmbxAlignPointer;
//	delete chkAlignPointerEqu;
//	delete chkMaxCodeLengthEqu;
//	delete spbxMaxCodeLength;
//	delete chkRemoveBrackets;
//	delete chkAlignReferenceEqu;
//	delete cmbxAlignReference;
//	delete chkBreakAfterLogical;
//	delete chkKeepOneLineBlocks;
//	delete chkModeEqu;
//	delete cmbxModeEqu;
//	delete chkRemoveCommentPrefix;
//	delete chkKeepOneLineStatements;
//	delete hbxLytModeEqu;
//	delete hbxAlignReferenceEqu;
//	delete hbxMaxCodeLengthEqu;
//	delete hbxAlignPointerEqu;
//	delete grdLytFormattingOptions;
//	delete grpbxFormattingOptions;
//	//part 5
//	delete chkAlignMethodColon;
//	delete chkPadMethodPrefix;
//	delete chkUnpadMethodPrefix;
//	delete chkPadMethodColonEqu;
//	delete cmbxPadMethodColonEqu;
//	delete hbxPadMethodColonEqu;
//	delete grdLytObjectiveCOptions;
//	delete grpbxObjectiveCOptions;
//	//part 6
//	delete chkSuffixEqu;
//	delete lineEdtSuffix;
//	delete chkSuffixNone;
//	delete chkRecursive;
//	delete chkExclude;
//	delete lineEdtExclude;
//	delete chkIgnoreExcludeErrors;
//	delete chkIgnoreExcludeErrorsX;
//	delete chkErrorsToStdout;
//	delete chkPreserveDate;
//	delete chkVerbose;
//	delete chkFormatted;
//	delete chkQuite;
//	delete chkLineEndEqu;
//	delete cmbxLineEnd;
//	delete hbxLineEndEqu;
//	delete hbxExcludeEqu;
//	delete hbxSuffixEqu;
//	delete grdLytOtherOptions;
//	delete grpbxOtherOptions;

//	delete buttonBox;

//	delete gridLayout;
//}
QString SettingsDialog::GetSettingOptions()
{
	if ((0 == settingResult.size()) || (0 == settingResult.compare("--style=linux --add-brackets --mode=c",Qt::CaseInsensitive))) {
		GetSetting();
	}
	return settingResult;
}
void SettingsDialog::InitBracketStyleOptionsGroup()
{
	//part 0-0 Bracket Style Options
	grpbxBracketStyleOption = new QGroupBox("Bracket Style Options");
	grdLytBracketStyleOption = new QGridLayout();
	grpbxBracketStyleOption->setLayout(grdLytBracketStyleOption);
	cmbxBracketStyleOption = new QComboBox(this);
	QStringList styleList;
	styleList << "allman" << "java" << "kr" << "stroustrup"
			  << "whitesmith" << "banner" << "gun" << "linux"
			  << "horstmann" << "1tbs" << "google" << "pico" << "lisp";
	cmbxBracketStyleOption->addItems(styleList);
	grdLytBracketStyleOption->addWidget(cmbxBracketStyleOption);
	cmbxBracketStyleOption->setFixedWidth(cmbxBracketStyleOption->width());
	grdLytBracketStyleOption->setAlignment(cmbxBracketStyleOption, Qt::AlignLeft);
}
void SettingsDialog::InitTabOptionsGroup()
{
	//part 0-1 Tab Options
	grpbxTabOptions = new QGroupBox("Tab Options");
	grdLytTabOptions = new QGridLayout();
	grpbxTabOptions->setLayout(grdLytTabOptions);
	hbxLytIndent = new QHBoxLayout();
	chkIndent = new SettingCheckBox("--indent=");
	cmbxIndentUnit = new QComboBox(this);
	QStringList indentUnitList;
	indentUnitList << "spaces" << "tab" << "force-tab";
	cmbxIndentUnit->addItems(indentUnitList);
	hbxLytIndent->addWidget(chkIndent);
	hbxLytIndent->addWidget(cmbxIndentUnit);
	cmbxIndentUnit->setDisabled(true);
	spbxIndentCount = new QSpinBox(this);
	spbxIndentCount->setRange(2, 20);
	spbxIndentCount->setValue(4);
	spbxIndentCount->setDisabled(true);
	chkIndentForceTab = new SettingCheckBox("--indent=force-tab-x=");
	spbxIndentForceTabCount = new QSpinBox(this);
	spbxIndentForceTabCount->setRange(2, 20);
	spbxIndentForceTabCount->setValue(8);
	spbxIndentForceTabCount->setDisabled(true);
	grdLytTabOptions->addLayout(hbxLytIndent, 0, 0, 1, 1);
	grdLytTabOptions->addWidget(spbxIndentCount, 0, 1, 1, 1);
	grdLytTabOptions->addWidget(chkIndentForceTab, 1, 0, 1, 1);
	grdLytTabOptions->addWidget(spbxIndentForceTabCount, 1, 1, 1, 1);

	//connect slots & signals
	connect(chkIndent, SIGNAL(clicked(bool)), cmbxIndentUnit, SLOT(setEnabled(bool)));
	connect(chkIndent, SIGNAL(clicked(bool)), spbxIndentCount, SLOT(setEnabled(bool)));
	connect(chkIndentForceTab, SIGNAL(clicked(bool)), spbxIndentForceTabCount, SLOT(setEnabled(bool)));
}
void SettingsDialog::InitBracketModifyOptionsGroup()
{
	//part 1 Bracket Modify Options
	grpbxBracketModifyOptions = new QGroupBox("Bracket Modify Options");
	grdLytBracketModifyOptions = new QGridLayout();
	grpbxBracketModifyOptions->setLayout(grdLytBracketModifyOptions);
	chkAttchNamespaces = new SettingCheckBox("--attach-namespaces");
	chkAttchInlines = new SettingCheckBox("--attach-inlines");
	chkAttchClasses = new SettingCheckBox("--attach-classes");
	chkAttchExternC = new SettingCheckBox("--attach-extern-c");
	grdLytBracketModifyOptions->addWidget(chkAttchNamespaces, 0, 0, 1, 1);
	grdLytBracketModifyOptions->addWidget(chkAttchInlines, 0, 1, 1, 1);
	grdLytBracketModifyOptions->addWidget(chkAttchClasses, 1, 0, 1, 1);
	grdLytBracketModifyOptions->addWidget(chkAttchExternC, 1, 1, 1, 1);
}
void SettingsDialog::InitIndentationOptionsGroup()
{
	//part 2 Indentation Options
	grpbxIndentationOptions = new QGroupBox("Indentation Options");
	grdLytIndentationOptions = new QGridLayout();
	grpbxIndentationOptions->setLayout(grdLytIndentationOptions);
	chkIndentClasses = new SettingCheckBox("--indent-classes");
	chkIndentModifiers = new SettingCheckBox("--indent-modifiers");
	chkIndentSwitches = new SettingCheckBox("--indent-switches");
	chkIndentCases = new SettingCheckBox("--indent-cases");
	chkIndentNamespaces = new SettingCheckBox("--indent-namespaces");
	chkIndentLabels = new SettingCheckBox("--indent-labels");
	chkIndentPreprocDefine = new SettingCheckBox("--indent-preproc-define");
	chkIndentPreprocCond = new SettingCheckBox("--indent-preproc-cond");
	chkIndentCol1Comments = new SettingCheckBox("--indent-col1-comments");
	hbxLytMinConditionalIndent = new QHBoxLayout();
	chkMinConditionalIndent = new SettingCheckBox("--min-conditional-indent=");
	spbxMinConditionalIndent = new QSpinBox(this);
	hbxLytMinConditionalIndent->addWidget(chkMinConditionalIndent);
	hbxLytMinConditionalIndent->addWidget(spbxMinConditionalIndent);
	spbxMinConditionalIndent->setRange(0, 3);
	spbxMinConditionalIndent->setValue(2);
	spbxMinConditionalIndent->setDisabled(true);
	hbxLytMaxInstatementIndent = new QHBoxLayout();
	chkMaxInstatementIndent = new SettingCheckBox("--max-instatement-indent=");
	spbxMaxInstatementIndent = new QSpinBox(this);
	hbxLytMaxInstatementIndent->addWidget(chkMaxInstatementIndent);
	hbxLytMaxInstatementIndent->addWidget(spbxMaxInstatementIndent);
	spbxMaxInstatementIndent->setRange(40, 120);
	spbxMaxInstatementIndent->setValue(40);
	spbxMaxInstatementIndent->setSingleStep(10);
	spbxMaxInstatementIndent->setDisabled(true);

	grdLytIndentationOptions->addWidget(chkIndentClasses, 0, 0, 1, 1);
	grdLytIndentationOptions->addWidget(chkIndentModifiers, 0, 1, 1, 1);
	grdLytIndentationOptions->addWidget(chkIndentSwitches, 0, 2, 1, 1);

	grdLytIndentationOptions->addWidget(chkIndentCases, 1, 0, 1, 1);
	grdLytIndentationOptions->addWidget(chkIndentNamespaces, 1, 1, 1, 1);
	grdLytIndentationOptions->addWidget(chkIndentLabels, 1, 2, 1, 1);

	grdLytIndentationOptions->addWidget(chkIndentPreprocDefine, 2, 0, 1, 1);
	grdLytIndentationOptions->addWidget(chkIndentPreprocCond, 2, 1, 1, 1);
	grdLytIndentationOptions->addWidget(chkIndentCol1Comments, 2, 2, 1, 1);

	grdLytIndentationOptions->addLayout(hbxLytMinConditionalIndent, 3, 0, 1, 1);
	grdLytIndentationOptions->addLayout(hbxLytMaxInstatementIndent, 3, 1, 1, 1);

	//connect slots & signals
	connect(chkMinConditionalIndent, SIGNAL(clicked(bool)), spbxMinConditionalIndent, SLOT(setEnabled(bool)));
	connect(chkMaxInstatementIndent, SIGNAL(clicked(bool)), spbxMaxInstatementIndent, SLOT(setEnabled(bool)));
}
void SettingsDialog::InitPaddingOptionsGroup()
{
	//part 3 Padding Options
	grpbxPaddingOptions = new QGroupBox("Padding Options");
	grdLytPaddingOptions = new QGridLayout();
	grpbxPaddingOptions->setLayout(grdLytPaddingOptions);
	chkBreakBlocks = new SettingCheckBox("--break-blocks");
	chkBreakBlocksAll = new SettingCheckBox("--break-blocks=all");
	chkPadOper = new SettingCheckBox("--pad-oper");
	chkPadParen = new SettingCheckBox("--pad-paren");
	chkPadParenOut = new SettingCheckBox("--pad-paren-out");
	chkPadFirstParenOut = new SettingCheckBox("--pad-first-paren-out");
	chkPadParenIn = new SettingCheckBox("--pad-paren-in");
	chkPadHeader = new SettingCheckBox("--pad-header");
	chkUnpadParen = new SettingCheckBox("--unpad-paren");
	chkDeleteEmptyLines = new SettingCheckBox("--delete-empty-lines");
	chkFillEmptyLines = new SettingCheckBox("--fill-empty-lines");
	hbxAlignPointerEqu = new QHBoxLayout();
	chkAlignPointerEqu = new SettingCheckBox("--align-pointer=");
	QStringList alignPointerList;
	alignPointerList << "type" << "middle" << "name";
	cmbxAlignPointer = new QComboBox(this);
	cmbxAlignPointer->addItems(alignPointerList);
	hbxAlignPointerEqu->addWidget(chkAlignPointerEqu);
	hbxAlignPointerEqu->addWidget(cmbxAlignPointer);
	cmbxAlignPointer->setDisabled(true);
	hbxAlignReferenceEqu = new QHBoxLayout();
	chkAlignReferenceEqu = new SettingCheckBox("--align-reference=");
	alignPointerList.push_front("none");
	cmbxAlignReference = new QComboBox(this);
	cmbxAlignReference->addItems(alignPointerList);
	hbxAlignReferenceEqu->addWidget(chkAlignReferenceEqu);
	hbxAlignReferenceEqu->addWidget(cmbxAlignReference);
	cmbxAlignReference->setDisabled(true);

	grdLytPaddingOptions->addWidget(chkBreakBlocks, 0, 0, 1, 1);
	grdLytPaddingOptions->addWidget(chkBreakBlocksAll, 0, 1, 1, 1);
	grdLytPaddingOptions->addWidget(chkPadOper, 0, 2, 1, 1);

	grdLytPaddingOptions->addWidget(chkPadParen, 1, 0, 1, 1);
	grdLytPaddingOptions->addWidget(chkPadParenOut, 1, 1, 1, 1);
	grdLytPaddingOptions->addWidget(chkPadFirstParenOut, 1, 2, 1, 1);

	grdLytPaddingOptions->addWidget(chkPadParenIn, 2, 0, 1, 1);
	grdLytPaddingOptions->addWidget(chkPadHeader, 2, 1, 1, 1);
	grdLytPaddingOptions->addWidget(chkUnpadParen, 2, 2, 1, 1);

	grdLytPaddingOptions->addWidget(chkDeleteEmptyLines, 3, 0, 1, 1);
	grdLytPaddingOptions->addWidget(chkFillEmptyLines, 3, 1, 1, 1);
	grdLytPaddingOptions->addLayout(hbxAlignPointerEqu, 3, 2, 1, 1);

	grdLytPaddingOptions->addLayout(hbxAlignReferenceEqu, 4, 0, 1, 1);

	//connect slots & signals
	connect(chkAlignPointerEqu, SIGNAL(clicked(bool)), cmbxAlignPointer, SLOT(setEnabled(bool)));
	connect(chkAlignReferenceEqu, SIGNAL(clicked(bool)), cmbxAlignReference, SLOT(setEnabled(bool)));
}
void SettingsDialog::InitFormattingOptionsGroup()
{
	//part4 Formatting Options
	grpbxFormattingOptions = new QGroupBox("Formatting Options:");
	grdLytFormattingOptions = new QGridLayout();
	grpbxFormattingOptions->setLayout(grdLytFormattingOptions);
	chkBreakClosingBrackets = new SettingCheckBox("--break-closing-brackets");
	chkBreakElseIfs = new SettingCheckBox("--break-elseifs");
	chkAddBrackes = new SettingCheckBox("--add-brackets");
	chkAddOneLineBracket = new SettingCheckBox("--add-one-line-brackets");
	chkRemoveBrackets = new SettingCheckBox("--remove-brackets");
	chkKeepOneLineBlocks = new SettingCheckBox("--keep-one-line-blocks");
	chkKeepOneLineStatements = new SettingCheckBox("--keep-one-line-statements");
	chkCovertTabs = new SettingCheckBox("--convert-tabs");
	chkCloseTemplates = new SettingCheckBox("--close-templates");
	chkRemoveCommentPrefix = new SettingCheckBox("--remove-comment-prefix");
	hbxMaxCodeLengthEqu = new QHBoxLayout();
	chkMaxCodeLengthEqu = new SettingCheckBox("--max-code-length=");
	spbxMaxCodeLength = new QSpinBox(this);
	spbxMaxCodeLength->setRange(50, 200);
	spbxMaxCodeLength->setDisabled(true);
	hbxMaxCodeLengthEqu->addWidget(chkMaxCodeLengthEqu);
	hbxMaxCodeLengthEqu->addWidget(spbxMaxCodeLength);
	chkBreakAfterLogical = new SettingCheckBox("--break-after-logical");
	hbxLytModeEqu = new QHBoxLayout();
	chkModeEqu = new SettingCheckBox("--mode=");
	QStringList modeList;
	modeList << "c" << "java" << "cs";
	cmbxModeEqu = new QComboBox(this);
	cmbxModeEqu->addItems(modeList);
	hbxLytModeEqu->addWidget(chkModeEqu);
	hbxLytModeEqu->addWidget(cmbxModeEqu);
	cmbxModeEqu->setDisabled(true);

	grdLytFormattingOptions->addWidget(chkBreakClosingBrackets, 0, 0, 1, 1);
	grdLytFormattingOptions->addWidget(chkBreakElseIfs, 0, 1, 1, 1);
	grdLytFormattingOptions->addWidget(chkAddBrackes, 0, 2, 1, 1);

	grdLytFormattingOptions->addWidget(chkAddOneLineBracket, 1, 0, 1, 1);
	grdLytFormattingOptions->addWidget(chkRemoveBrackets, 1, 1, 1, 1);
	grdLytFormattingOptions->addWidget(chkKeepOneLineBlocks, 1, 2, 1, 1);

	grdLytFormattingOptions->addWidget(chkKeepOneLineStatements, 2, 0, 1, 1);
	grdLytFormattingOptions->addWidget(chkCovertTabs, 2, 1, 1, 1);
	grdLytFormattingOptions->addWidget(chkCloseTemplates, 2, 2, 1, 1);

	grdLytFormattingOptions->addWidget(chkRemoveCommentPrefix, 3, 0, 1, 1);
	grdLytFormattingOptions->addLayout(hbxMaxCodeLengthEqu, 3, 1, 1, 1);
	grdLytFormattingOptions->addWidget(chkBreakAfterLogical, 3, 2, 1, 1);

	grdLytFormattingOptions->addLayout(hbxLytModeEqu, 4, 0, 1, 1);

	//connect slots & signals
	connect(chkMaxCodeLengthEqu, SIGNAL(clicked(bool)), spbxMaxCodeLength, SLOT(setEnabled(bool)));
	connect(chkModeEqu, SIGNAL(clicked(bool)), cmbxModeEqu, SLOT(setEnabled(bool)));
}
void SettingsDialog::InitObjectiveCOptionsGroup()
{
	//part 5 Objective-C Options
	grpbxObjectiveCOptions = new QGroupBox("Objective-C Options");
	grdLytObjectiveCOptions = new QGridLayout();
	grpbxObjectiveCOptions->setLayout(grdLytObjectiveCOptions);
	chkAlignMethodColon = new SettingCheckBox("--align-method-colon");
	chkPadMethodPrefix = new SettingCheckBox("--pad-method-prefix");
	chkUnpadMethodPrefix = new SettingCheckBox("--unpad-method-prefix");
	hbxPadMethodColonEqu = new QHBoxLayout();
	chkPadMethodColonEqu = new SettingCheckBox("--pad-method-colon=");
	QStringList methodColonList;
	methodColonList << "none" << "all" << "after" << "before";
	cmbxPadMethodColonEqu = new QComboBox(this);
	cmbxPadMethodColonEqu->addItems(methodColonList);
	hbxPadMethodColonEqu->addWidget(chkPadMethodColonEqu);
	hbxPadMethodColonEqu->addWidget(cmbxPadMethodColonEqu);
	cmbxPadMethodColonEqu->setDisabled(true);
	grdLytObjectiveCOptions->addWidget(chkAlignMethodColon, 0, 0, 1, 1);
	grdLytObjectiveCOptions->addWidget(chkPadMethodPrefix, 0, 1, 1, 1);
	grdLytObjectiveCOptions->addWidget(chkUnpadMethodPrefix, 0, 2, 1, 1);
	grdLytObjectiveCOptions->addLayout(hbxPadMethodColonEqu, 1, 0, 1, 1);

	//connect slots & signals
	connect(chkPadMethodColonEqu, SIGNAL(clicked(bool)), cmbxPadMethodColonEqu, SLOT(setEnabled(bool)));
}
void SettingsDialog::InitOtherOptionsGroup()
{
	//part 6 Other Options
	grpbxOtherOptions = new QGroupBox("Other Options");
	grdLytOtherOptions = new QGridLayout();
	grpbxOtherOptions->setLayout(grdLytOtherOptions);
	hbxSuffixEqu = new QHBoxLayout();
	chkSuffixEqu = new SettingCheckBox("--suffix=");
	lineEdtSuffix = new QLineEdit(".orig");
	lineEdtSuffix->setFixedWidth(100);
	lineEdtSuffix->setDisabled(true);
	lineEdtSuffix->setToolTip("Append the suffix #### instead of '.orig' to original filename.");
	hbxSuffixEqu->addWidget(chkSuffixEqu, 1);
	hbxSuffixEqu->addWidget(lineEdtSuffix, 1);
	chkSuffixNone = new SettingCheckBox("--suffix=none");
	chkRecursive = new SettingCheckBox("--recursive");
	hbxExcludeEqu = new QHBoxLayout();
	chkExclude = new SettingCheckBox("--exclude=");
	lineEdtExclude = new QLineEdit("");
	lineEdtExclude->setFixedWidth(100);
	lineEdtExclude->setDisabled(true);
	hbxExcludeEqu->addWidget(chkExclude, 1);
	hbxExcludeEqu->addWidget(lineEdtExclude, 1);
	chkIgnoreExcludeErrors = new SettingCheckBox("--ignore-exclude-errors");
	chkIgnoreExcludeErrorsX = new SettingCheckBox("--ignore-exclude-errors-x");
	chkErrorsToStdout = new SettingCheckBox("--errors-to-stdout");
	chkPreserveDate = new SettingCheckBox("--preserve-date");
	chkVerbose = new SettingCheckBox("--verbose");
	chkFormatted = new SettingCheckBox("--formatted");
	chkQuite = new SettingCheckBox("--quiet");
	hbxLineEndEqu = new QHBoxLayout();
	chkLineEndEqu = new SettingCheckBox("--lineend=");
	QStringList endTypeList;
	endTypeList << "windows" << "linux" << "macold";
	cmbxLineEnd = new QComboBox(this);
	cmbxLineEnd->addItems(endTypeList);
	hbxLineEndEqu->addWidget(chkLineEndEqu);
	hbxLineEndEqu->addWidget(cmbxLineEnd);
	cmbxLineEnd->setDisabled(true);
	grdLytOtherOptions->addLayout(hbxSuffixEqu, 0, 0, 1, 1);
	grdLytOtherOptions->addWidget(chkSuffixNone, 0, 1, 1, 1);
	grdLytOtherOptions->addWidget(chkRecursive, 0, 2, 1, 1);
	grdLytOtherOptions->addLayout(hbxExcludeEqu, 1, 0, 1, 1);
	grdLytOtherOptions->addWidget(chkIgnoreExcludeErrors, 1, 1, 1, 1);
	grdLytOtherOptions->addWidget(chkIgnoreExcludeErrorsX, 1, 2, 1, 1);
	grdLytOtherOptions->addWidget(chkErrorsToStdout, 2, 0, 1, 1);
	grdLytOtherOptions->addWidget(chkPreserveDate, 2, 1, 1, 1);
	grdLytOtherOptions->addWidget(chkVerbose, 2, 2, 1, 1);
	grdLytOtherOptions->addWidget(chkQuite, 3, 0, 1, 1);
	grdLytOtherOptions->addLayout(hbxLineEndEqu, 3, 1, 1, 1);

	//connect slots & signals
	connect(chkSuffixEqu, SIGNAL(clicked(bool)), lineEdtSuffix, SLOT(setEnabled(bool)));
	connect(chkExclude, SIGNAL(clicked(bool)), lineEdtExclude, SLOT(setEnabled(bool)));
	connect(chkLineEndEqu, SIGNAL(clicked(bool)), cmbxLineEnd, SLOT(setEnabled(bool)));
}
void SettingsDialog::GetSetting()
{
	settingResult.clear();
	//part 0-0
	settingResult += "--style=" + cmbxBracketStyleOption->currentText();
	settingResult += " ";
	//part 0-1
	settingResult += chkIndent->GetSettingText();
	if (true == chkIndent->isChecked()) {
		settingResult += cmbxIndentUnit->currentText();
		settingResult += "=";
		settingResult += spbxIndentCount->text();
		settingResult += " ";
	}

	settingResult += chkIndentForceTab->GetSettingText();
	if (true == chkIndentForceTab->isChecked()) {
		settingResult += spbxIndentForceTabCount->text();
		settingResult += " ";
	}

	//part 1
	settingResult += chkAttchNamespaces->GetSettingText();

	settingResult += chkAttchInlines->GetSettingText();

	settingResult += chkAttchClasses->GetSettingText();

	settingResult += chkAttchExternC->GetSettingText();

	//part 2
	settingResult += chkIndentClasses->GetSettingText();

	settingResult += chkIndentModifiers->GetSettingText();

	settingResult += chkMinConditionalIndent->GetSettingText();
	if (true == chkMinConditionalIndent->isChecked()) {
		settingResult += spbxMinConditionalIndent->text();
		settingResult += " ";
	}

	settingResult += chkMaxInstatementIndent->GetSettingText();
	if (true == chkMaxInstatementIndent->isChecked()) {
		settingResult += spbxMaxInstatementIndent->text();
		settingResult += " ";
	}

	settingResult += chkIndentLabels->GetSettingText();

	settingResult += chkIndentPreprocDefine->GetSettingText();

	settingResult += chkIndentCases->GetSettingText();

	settingResult += chkIndentPreprocCond->GetSettingText();

	settingResult += chkIndentNamespaces->GetSettingText();

	settingResult += chkIndentSwitches->GetSettingText();

	settingResult += chkIndentCol1Comments->GetSettingText();

	//part 3
	settingResult += chkPadParen->GetSettingText();

	settingResult += chkUnpadParen->GetSettingText();

	settingResult += chkBreakBlocks->GetSettingText();

	settingResult += chkPadParenOut->GetSettingText();

	settingResult += chkPadHeader->GetSettingText();

	settingResult += chkBreakBlocksAll->GetSettingText();

	settingResult += chkPadFirstParenOut->GetSettingText();

	settingResult += chkPadOper->GetSettingText();

	settingResult += chkDeleteEmptyLines->GetSettingText();

	settingResult += chkPadParenIn->GetSettingText();

	settingResult += chkFillEmptyLines->GetSettingText();

	//part4
	settingResult += chkCovertTabs->GetSettingText();

	settingResult += chkBreakClosingBrackets->GetSettingText();

	settingResult += chkAddBrackes->GetSettingText();

	settingResult += chkCloseTemplates->GetSettingText();

	settingResult += chkBreakElseIfs->GetSettingText();

	settingResult += chkAddOneLineBracket->GetSettingText();

	settingResult += chkAlignPointerEqu->GetSettingText();
	if (true == chkAlignPointerEqu->isChecked()) {
		settingResult += cmbxAlignPointer->currentText();
		settingResult += " ";
	}

	settingResult += chkMaxCodeLengthEqu->GetSettingText();
	if (true == chkMaxCodeLengthEqu->isChecked()) {
		settingResult += spbxMaxCodeLength->text();
		settingResult += " ";
	}

	settingResult += chkRemoveBrackets->GetSettingText();

	settingResult += chkAlignReferenceEqu->GetSettingText();
	if (true == chkAlignReferenceEqu->isChecked()) {
		settingResult += cmbxAlignReference->currentText();
		settingResult += " ";
	}

	settingResult += chkBreakAfterLogical->GetSettingText();

	settingResult += chkKeepOneLineBlocks->GetSettingText();

	settingResult += chkModeEqu->GetSettingText();
	if (true == chkModeEqu->isChecked()) {
		settingResult += cmbxModeEqu->currentText();
		settingResult += " ";
	}

	settingResult += chkRemoveCommentPrefix->GetSettingText();

	settingResult += chkKeepOneLineStatements->GetSettingText();

	//part 5
	settingResult += chkAlignMethodColon->GetSettingText();

	settingResult += chkPadMethodPrefix->GetSettingText();

	settingResult += chkUnpadMethodPrefix->GetSettingText();

	settingResult += chkPadMethodColonEqu->GetSettingText();
	if (true == chkPadMethodColonEqu->isChecked()) {
		settingResult += cmbxPadMethodColonEqu->currentText();
		settingResult += " ";
	}

	//part 6
	settingResult += chkSuffixEqu->GetSettingText();
	if (true == chkSuffixEqu->isChecked()) {
		settingResult += lineEdtSuffix->text();
		settingResult += " ";
	}

	settingResult += chkSuffixNone->GetSettingText();

	settingResult += chkRecursive->GetSettingText();

	settingResult += chkExclude->GetSettingText();
	if (true == chkExclude->isChecked()) {
		settingResult += lineEdtExclude->text();
		settingResult += " ";
	}

	settingResult += chkIgnoreExcludeErrors->GetSettingText();

	settingResult += chkIgnoreExcludeErrorsX->GetSettingText();

	settingResult += chkErrorsToStdout->GetSettingText();

	settingResult += chkPreserveDate->GetSettingText();

	settingResult += chkVerbose->GetSettingText();

	settingResult += chkFormatted->GetSettingText();

	settingResult += chkQuite->GetSettingText();

	settingResult += chkLineEndEqu->GetSettingText();
	if (true == chkLineEndEqu->isChecked()) {
		settingResult += cmbxLineEnd->currentText();
		settingResult += " ";
	}
}
void SettingsDialog::ClickBtn(QAbstractButton * btn)
{
	if (btn->text() == QString("Cancel") ) {
		emit reject();
	} else if (btn->text() == QString("Apply") ) {
		GetSetting();
		emit accepted();
	}
	close();
}
void SettingsDialog::ConnectSettingCheckBox()
{
	if (true != initSucceed) {
		qDebug("Not init this dialog, Are you kidding me ?");
		return;
	} else {
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkIndent, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkIndentForceTab, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkAttchNamespaces, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkAttchInlines, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkAttchClasses, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkAttchExternC, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkIndentClasses, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkIndentModifiers, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkMinConditionalIndent, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkMaxInstatementIndent, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkIndentLabels, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkIndentPreprocDefine, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkIndentCases, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkIndentPreprocCond, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkIndentNamespaces, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkIndentSwitches, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkIndentCol1Comments, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkPadParen, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkUnpadParen, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkBreakBlocks, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkPadParenOut, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkPadHeader, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkBreakBlocksAll, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkPadFirstParenOut, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkPadOper, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkDeleteEmptyLines, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkPadParenIn, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkFillEmptyLines, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkCovertTabs, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkBreakClosingBrackets, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkAddBrackes, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkCloseTemplates, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkBreakElseIfs, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkAddOneLineBracket, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkAlignPointerEqu, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkMaxCodeLengthEqu, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkRemoveBrackets, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkAlignReferenceEqu, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkBreakAfterLogical, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkKeepOneLineBlocks, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkModeEqu, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkRemoveCommentPrefix, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkKeepOneLineStatements, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkAlignMethodColon, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkPadMethodPrefix, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkUnpadMethodPrefix, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkPadMethodColonEqu, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkSuffixEqu, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkSuffixNone, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkRecursive, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkExclude, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkIgnoreExcludeErrors, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkIgnoreExcludeErrorsX, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkErrorsToStdout, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkPreserveDate, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkVerbose, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkFormatted, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkQuite, SLOT(GotInitSetting(QString)));
		connect(this, SIGNAL(PushSettingToCheckBox(QString)), chkLineEndEqu, SLOT(GotInitSetting(QString)));
	}
}
void SettingsDialog::SettingToComBox()
{
	if (true != initSucceed) {
		qDebug("Not init this dialog, Are you kidding me ?");
		return;
	} else {
		SetSettingToComBox(cmbxBracketStyleOption, "--style=");
		SetSettingToComBox(cmbxIndentUnit, "--indent=", "=");
		SetSettingToComBox(cmbxAlignPointer, "--align-pointer=");
		SetSettingToComBox(cmbxAlignReference, "--align-reference=");
		SetSettingToComBox(cmbxModeEqu, "--mode=");
		SetSettingToComBox(cmbxPadMethodColonEqu, "--pad-method-colon=");
		SetSettingToComBox(cmbxLineEnd, "--lineend=");
	}
}
void SettingsDialog::SettingToSpinBox()
{
	if (true != initSucceed) {
		qDebug("Not init this dialog, Are you kidding me ?");
		return;
	} else {
		SetSettingToSpinBox(spbxIndentCount, "--indent=", "=");
		SetSettingToSpinBox(spbxIndentForceTabCount, "--indent=force-tab-x=");
		SetSettingToSpinBox(spbxMinConditionalIndent, "--min-conditional-indent=");
		SetSettingToSpinBox(spbxMaxInstatementIndent, "--max-instatement-indent=");
		SetSettingToSpinBox(spbxMaxCodeLength, "--max-code-length=");
	}
}
void SettingsDialog::SettingToLineEdit()
{
	if (true != initSucceed) {
		qDebug("Not init this dialog, Are you kidding me ?");
		return;
	} else {
		SetSettingToLineEdit(lineEdtSuffix, "--suffix=");
		SetSettingToLineEdit(lineEdtExclude, "--exclude=");
	}
}
void SettingsDialog::SetSettingToComBox(QComboBox *combx, QString flagStr, QString splitStr /*= " "*/)
{
	if (true == settingResult.contains(flagStr)) {
		int pos  = settingResult.indexOf(flagStr, 0, Qt::CaseInsensitive)+flagStr.size();
		int posBlank = settingResult.indexOf(splitStr, pos, Qt::CaseInsensitive);
		QString styleStr = settingResult.mid(pos, posBlank-pos);
		combx->setCurrentText(styleStr);
	}
}
void SettingsDialog::SetSettingToSpinBox(QSpinBox *spinbox, QString flagStr, QString jumpStr /*= "="*/)
{
	if (true == settingResult.contains(flagStr)) {
		int pos  = settingResult.indexOf(flagStr, 0, Qt::CaseInsensitive)+flagStr.size();
		if (0 < jumpStr.size()) {
			pos = settingResult.indexOf(jumpStr, pos, Qt::CaseInsensitive)+jumpStr.size();
		}
		int posBlank = settingResult.indexOf(" ", pos, Qt::CaseInsensitive);
		QString styleStr = settingResult.mid(pos, posBlank-pos);
		spinbox->setValue(styleStr.toInt());
	}
}
void SettingsDialog::SetSettingToLineEdit(QLineEdit *lineEdit, QString flagStr, QString splitStr /*= " "*/)
{
	if (true == settingResult.contains(flagStr)) {
		int pos  = settingResult.indexOf(flagStr, 0, Qt::CaseInsensitive)+flagStr.size();
		int posBlank = settingResult.indexOf(splitStr, pos, Qt::CaseInsensitive);
		QString styleStr = settingResult.mid(pos, posBlank-pos);
		lineEdit->setText(styleStr);
	}
}
// emit a signal to every checkbox
void SettingsDialog::PushSettings(QString settingOptions)
{
	if (0 < settingOptions.size()) {
		settingResult = settingOptions;
		emit PushSettingToCheckBox(settingOptions);
		SettingToComBox();
		SettingToSpinBox();
		SettingToLineEdit();
	}
}
