#include "MsgBox.h"
#include "ui_MsgBox.h"

const int MulHeight = 253;
const int SingleHeight = 193;

MsgBox::MsgBox(QWidget *parent, bool bAutoDel/* = true*/, int autoCloseTime/* = 0*/) :
	QDialog(parent),
	ui(new Ui::msgbox)
{
	ui->setupUi(this);
	setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setFixedSize(width(), height());
	setAttribute(Qt::WA_DeleteOnClose, bAutoDel);
	// init
	_bOk = false;
	_funCall = NULL;
	_nHasTime = autoCloseTime;
	_pParames = NULL;
	_pTimer = NULL;
	if (_nHasTime > 0) {
		_pTimer = new QTimer(this);
		connect(_pTimer, SIGNAL(timeout()), this, SLOT(onUpdateTimer()));
		//delay->singleShot(60000,this,SLOT(toplay()));
		_pTimer->start(_nHasTime * 1000);
	}
	ui->labMsg->setWordWrap(true);
	ui->labMsg->setAlignment(Qt::AlignCenter);

	connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(onButtonClick()));
	connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(onButtonClick()));
	connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(onButtonClick()));
}

MsgBox::~MsgBox()
{
	if (_pTimer) {
		if (_pTimer->isActive()) {
			_pTimer->stop();
		}
		
	}

	delete ui;
}

void MsgBox::ShowDlg(FuncMsgCloseCall func /*= NULL*/, void* pFuncParam /*= NULL*/)
{
	_funCall = func;
	_pParames = pFuncParam;
	show();
	raise();
}

void MsgBox::SetMainInfo(QString strMsg, QString strTitle /*= ""*/)
{
	ui->labMsg->setText(strMsg);
	if (!strTitle.isEmpty()) {
		setWindowTitle(strTitle);
	}
	if (strMsg.length() < 100) {
		setFixedHeight(SingleHeight);
	}
	else {
		setFixedHeight(MulHeight);
	}
}

void MsgBox::SetBtnInfo(bool bShowCancel, QString strOk /*= ""*/, QString strCancel /*= ""*/)
{
	if (!strOk.isEmpty()) {
		ui->btnOk->setText(strOk);
	}
	if (!strCancel.isEmpty()) {
		ui->btnCancel->setText(strCancel);
	}
	ui->btnCancel->setVisible(bShowCancel);
}

void MsgBox::closeEvent(QCloseEvent *event)
{
	emit sgCloseMsgBox(_bOk, this);
	if (_funCall) {
		_funCall(_bOk, _pParames);
	}
    _bOk = false;
	QDialog::closeEvent(event);
}

void MsgBox::onButtonClick()
{
	QPushButton *pBtn = qobject_cast<QPushButton*>(sender());
	if (pBtn == ui->btnOk) {
		_bOk = true;
	}
	else if (pBtn == ui->btnCancel || pBtn == ui->btnClose) {
		_bOk = false;
	}
	hide();
	close();
}

void MsgBox::onUpdateTimer()
{
	close();
}
