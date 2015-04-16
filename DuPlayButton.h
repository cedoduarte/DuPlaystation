#ifndef DUPLAYBUTTON_H
#define DUPLAYBUTTON_H

#include <QPushButton>

class DuPlayButton : public QPushButton
{
    Q_OBJECT
public:
    DuPlayButton(const QString &filename, int type, const QString &display,
                 QWidget *parent = nullptr);

    QString filename() const
    {
        return mFilename;
    }

    int type() const
    {
        return mType;
    }
signals:
    void clickedRef(DuPlayButton *);
private:
    QString mFilename;
    int mType;
};

#endif // DUPLAYBUTTON_H
