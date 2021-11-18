#include "widget.h"
#include "ui_widget.h"
#include "QCamera"
#include "QCameraViewfinder"
#include "QCameraImageCapture"
#include "QVBoxLayout"
#include "QMenu"
#include "QAction"
#include <QFileDialog>
#include <QFile>
widget::widget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::widget)
{
    ui->setupUi(this);
    mCamera =new QCamera(this);
    mCameraViewfinder =new QCameraViewfinder(this);
    mCameraImageCapture =new QCameraImageCapture(mCamera,this);
    mLayout =new QVBoxLayout;
    mOptionMenu =new QMenu("Options", this);
    mEncenderAction =new QAction("Encender",this);
    mApagarAction =new QAction ("Apagar", this);

    mCapturarAaction =new QAction("Capturar", this);


    mOptionMenu->addActions({mEncenderAction ,mApagarAction,mCapturarAaction});
    ui->optionspush->setMenu(mOptionMenu);
    mCamera->setViewfinder(mCameraViewfinder);


    mLayout->addWidget(mCameraViewfinder);
    mLayout->setMargin(0);
    ui->scrollArea->setLayout(mLayout);

    connect(mEncenderAction, &QAction::triggered ,[&]() {mCamera->start();});
    connect(mApagarAction, &QAction::triggered ,[&]() {mCamera->stop();});
    connect(mCapturarAaction, &QAction::triggered ,[&]() {
       auto filename= QFileDialog ::getSaveFileName(this,"capturar","/","Imagen(*.jpg;*jpeg)");
        if (filename.isEmpty()){return; }
        mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);

    QImageEncoderSettings ImageEncoderSettings; ImageEncoderSettings.setCodec("image/jpeg");
    ImageEncoderSettings.setResolution(1600,1200);
    mCameraImageCapture->setEncodingSettings(ImageEncoderSettings);
    mCamera->setCaptureMode(QCamera::CaptureStillImage);
    mCamera->start();
    mCamera->searchAndLock();
    mCameraImageCapture->capture(filename);
    mCamera->unlock();


    });


}

widget::~widget()
{
    delete ui;
}

