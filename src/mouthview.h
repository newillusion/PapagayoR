#ifndef MOUTHVIEW_H
#define MOUTHVIEW_H

#include <QWidget>

#include "lipsyncdoc.h"

class MouthView : public QWidget
{
	Q_OBJECT
public:
	explicit MouthView(QWidget *parent = 0);
	~MouthView();

	void SetDocument(LipsyncDoc *doc);
	void SetMouth(int32 id);
	int GetMouthSetCount();
	QString GetMouthSetName(int i);

signals:

public slots:
	void onMouthChanged(int id);
	void onFrameChanged(int frame);

protected:
	void paintEvent(QPaintEvent *event);

private:
	LipsyncDoc					*fDoc;
	int32						fMouthID;
	int32						fFrame;
	QHash<int,QString>			fMouthsName;
	QList<QHash<QString, QImage*>>	fMouths;

};

#endif // MOUTHVIEW_H
