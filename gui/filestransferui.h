#ifndef FILIESTRANSFER_H
#define FILIESTRANSFER_H

#include "core/driveengine.h"

//class FilesManager;

class FilesTransferUI : public QObject
{
    Q_OBJECT
public:
    explicit FilesTransferUI(QObject *parent = 0);

public:
    void upload(void);
    void download(void);

private slots:
    void slotDownload(void);
    void slotUpload(void);

};

#endif // FILIESTRANSFER_H
