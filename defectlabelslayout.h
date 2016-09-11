#ifndef DEFECTIMAGEFIELD_H
#define DEFECTIMAGEFIELD_H

//makes a vertical layout holding a defect display label and label to display the Frame number

//qt includes
#include <QWidget>
#include <QLayout>
#include <QVBoxLayout>
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



private:
    DefectLabel* defectImageLabel;
    QLabel* defectFrameNumberandLength;
    QVBoxLayout* verticalBox;
    // maybe add the Length as a separate label???
};

#endif // DEFECTIMAGEFIELD_H
