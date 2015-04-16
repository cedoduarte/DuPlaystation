#include "DuPlayButton.h"

DuPlayButton::DuPlayButton(const QString &title, int type,
                           const QString &display, QWidget *parent)
    : QPushButton(display, parent)
{
    mFilename = title;
    mType = type;

    connect(this, &DuPlayButton::clicked, [&]() {
        emit clickedRef(this);
    });
}
