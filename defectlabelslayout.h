#ifndef DEFECTIMAGEFIELD_H
#define DEFECTIMAGEFIELD_H

//makes a vertical layout holding a defect display label and label to display the Frame number

//qt includes
#include <QWidget>
#include <QLayout>
#include <QVBoxLayout>
#include <QPixmap>
#
//local includes
#include "defectLabel.h"

//struct defectlabels
//{
//   DefectLabel defectimageLabel;



//};

class DefectLabelsLayout : public QWidget
{
      Q_OBJECT
public:
    DefectLabelsLayout(QWidget *parent);
    ~DefectLabelsLayout();
    void setDefectFrameNumber(QString);
    void setDefectImage(QPixmap &);
    void setDefectPositionInWeb(QString);
    int getDefectLabelWidth() const;
    int getDefectLabelHeight() const;



private:
    DefectLabel* defectImageLabel;
    QLabel* defectFrameNumber;
    QLabel* defectFramePositionInWeb;
    QVBoxLayout* verticalBox;

};

#endif // DEFECTIMAGEFIELD_H
