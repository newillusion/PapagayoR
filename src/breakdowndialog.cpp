#include "breakdowndialog.h"
#include "ui_breakdowndialog.h"
#include "lipsyncdoc.h"
#include <QPushButton>

BreakdownDialog::BreakdownDialog(LipsyncWord* word, QList<QString>* phonemes, QWidget* parent) :
	QDialog(parent),
	ui(new Ui::BreakdownDialog)
{
	fWord = word;
	fPhonemes = phonemes;

	ui->setupUi(this);
	ui->wordLabel->setText(tr("Break down the word:") + " " + fWord->fText);

	for (int i=0; i<phonemes->count(); i++)
		{
		auto b = new QPushButton( phonemes->at(i) );
		//b->setText(  );

		ui->gridLayout->addWidget( b, i / 4, i & 3 );

		connect( b, b->clicked, this, [i,this]{ this->onButton(i); } );
		}

	QString str;
	for (int i = 0; i < fWord->fPhonemes.size(); i++)
	{
		str += " ";
		str += fWord->fPhonemes[i]->fText;
	}

	ui->breakdownEdit->setText(str.trimmed());
}

BreakdownDialog::~BreakdownDialog()
{
	delete ui;
}

QString BreakdownDialog::PhonemeString()
{
	return ui->breakdownEdit->text().trimmed();
}


void BreakdownDialog::onButton(int i)
	{
	AddPhoneme( fPhonemes->at(i) );
	}

void BreakdownDialog::AddPhoneme(QString phoneme)
{
	QString str = ui->breakdownEdit->text().trimmed();
	str += " ";
	str += phoneme;
	ui->breakdownEdit->setText(str.trimmed());
}

