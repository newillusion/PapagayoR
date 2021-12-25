#ifndef BREAKDOWNDIALOG_H
#define BREAKDOWNDIALOG_H

#include <QDialog>

namespace Ui {
class BreakdownDialog;
}

class LipsyncWord;

class BreakdownDialog : public QDialog
{
	Q_OBJECT

public:
	explicit BreakdownDialog(LipsyncWord *word, QList<QString>* phonemes, QWidget *parent = 0);
	~BreakdownDialog();

	QString PhonemeString();

private slots:
	void onButton(int i);

private:
	void AddPhoneme(QString phoneme);

	Ui::BreakdownDialog *ui;

	LipsyncWord*	fWord;
	QList<QString>*	fPhonemes;
};

#endif // BREAKDOWNDIALOG_H
