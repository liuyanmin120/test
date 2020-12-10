#ifndef MSGBOX_H
#define MSGBOX_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include "WdgDef.h"

namespace Ui {
	class msgbox;
}

typedef void(*FuncMsgCloseCall)(bool bOk, void* pParam);
class MsgBox : public QDialog
{
	Q_OBJECT

	MOUSEDRAG(40);
	WIDGETROUND(4);
public:
	explicit MsgBox(QWidget *parent, bool bAutoDel = true, int autoCloseTime = 0);
	~MsgBox();

	void ShowDlg(FuncMsgCloseCall func = NULL, void* pFuncParam = NULL);
	void SetMainInfo(QString strMsg, QString strTitle = "");
	void SetBtnInfo(bool bShowCancel, QString strOk = "", QString strCancel = "");

	void* GetPar() {
		return _pParames;
	}

signals:
	void sgCloseMsgBox(bool bOk, MsgBox* pDlg);

private slots:
	void onButtonClick();
	void onUpdateTimer();

protected:
	void closeEvent(QCloseEvent *event);

private:
	Ui::msgbox *ui;

	QTimer*			_pTimer;

	int				_nHasTime;
	FuncMsgCloseCall _funCall;
	void*			_pParames;
	bool			_bOk;
};

#endif // MSGBOX_H
