#include <QPainter>
#include <QDir>

#include "mouthview.h"

MouthView::MouthView(QWidget *parent) :
	QWidget(parent)
{
	fDoc = NULL;
	fMouthID = 0;
	fFrame = 0;

	// It load LipsyncDoc::Phonemes, but we can take phonemes from
	// file name...
	//LipsyncDoc::LoadDictionaries();

	QString basePath = ":/mouths/mouths/";


	QDir mouthsdir;
	mouthsdir.setFilter( QDir::Dirs );
	mouthsdir.setPath( basePath );
	auto folders = mouthsdir.entryInfoList();

	for (int fi=0; fi<folders.length(); fi++)
		{
		QDir imagedir;
		imagedir.setFilter( QDir::Files );
		imagedir.setPath( folders.at(fi).absoluteFilePath() );
		auto images = imagedir.entryInfoList();

		if (images.length()<=0) continue;

		fMouths.append( QHash<QString,QImage*>() );
		fMouthsName[fi] = folders.at(fi).fileName();

		for (int i=0; i<images.length(); i++)
			{
			QString fn = images.at(i).fileName();
			if (fn.endsWith(".jpg"))
				{
				QString name = fn.left( fn.length() - 4);	// 4-length if ".jpg"
				fMouths.last().insert( name, new QImage( images.at(i).absoluteFilePath() ) );
				}
			}
		}


	/*

	for (int32 mouth = 0; mouth < 4; mouth++)
	{
		QString		basePath;

		switch (mouth)
		{
			case 0:
				basePath = ":/mouths/mouths/1_Mouth_1/";
				break;
			case 1:
				basePath = ":/mouths/mouths/2_Mouth_2/";
				break;
			case 2:
				basePath = ":/mouths/mouths/3_Gary_C_Martin/";
				break;
			case 3:
				basePath = ":/mouths/mouths/4_Preston_Blair/";
				break;
		}

		//for (int32 i = 0; i < LipsyncDoc::Phonemes.size(); i++)
		//{
		//	fMouths[mouth].insert(LipsyncDoc::Phonemes[i], new QImage(basePath + LipsyncDoc::Phonemes[i] + ".jpg"));
		//}
	}
	*/

}

MouthView::~MouthView()
{
}

void MouthView::SetDocument(LipsyncDoc *doc)
{
	fDoc = doc;
	update();
}

int		MouthView::GetMouthSetCount()		{ return fMouths.length(); }
QString MouthView::GetMouthSetName(int i)	{ return fMouthsName[i]; }


void MouthView::SetMouth(int32 id)
{
	fMouthID = PG_CLAMP(id, 0, fMouths.length()-1);
}

void MouthView::onMouthChanged(int id)
{
	SetMouth(id);
	update();
}

void MouthView::onFrameChanged(int frame)
{
	fFrame = frame;
	update();
}

void MouthView::paintEvent(QPaintEvent *event)
{
	PG_UNUSED(event);

	QString		phoneme;
	QImage		*img = NULL;
	QPainter	dc(this);

	if (fDoc && fDoc->fCurrentVoice)
		phoneme = fDoc->fCurrentVoice->GetPhonemeAtFrame(fFrame);
	else
		phoneme = "etc";
	if (phoneme.isEmpty() && fDoc)
		phoneme = fDoc->GetVolumePhonemeAtFrame(fFrame);

	img = fMouths[fMouthID].value(phoneme);
	if (img)
	{
		int32	x = 0, y = 0;
		int32	w = width();
		int32	h = height();
		QColor	backCol(255, 255, 255);
		if (w > h)
		{
			dc.fillRect(QRect(x, y, w, h), backCol);
			x = (w - h) / 2;
			w = h;
		}
		else if (h > w)
		{
			dc.fillRect(QRect(x, y, w, h), backCol);
			y = (h - w) / 2;
			h = w;
		}
		dc.drawImage(QRect(x, y, w, h), *img);
	}
	else
		dc.eraseRect(0, 0, width(), height());
}
