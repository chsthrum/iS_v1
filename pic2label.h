#ifndef PIC2LABEL
#define PIC2LABEL
//qt includes
#include <QLabel>
#include <QPixmap>


class ScaledLabel : public QLabel
{
public:
    explicit ScaledLabel(QWidget *parent = 0);
    ~ScaledLabel();

    void setPix(const QPixmap&);
    QPixmap scaledPixmap() const;
    int heightForWidth( int width ) const;
    QSize sizeHint() const;


private:
    QPixmap pix;

};

#endif // PIC2LABEL

