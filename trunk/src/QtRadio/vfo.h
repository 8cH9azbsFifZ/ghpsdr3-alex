#ifndef VFO_H
#define VFO_H

#include <QWidget>
#include <QWheelEvent>
#include <QBasicTimer>
#include <QSettings>
namespace Ui {
    class vfo;
}

class vfo : public QWidget
{
    Q_OBJECT

public:
    explicit vfo(QWidget *parent = 0);
    ~vfo();
//    void SaveMySettings(){
//        writeSettings();
    void readSettings(QSettings* settings);
    void writeSettings(QSettings* settings);
//    }

public slots:
    void togglePTT(bool pttRq); //Request to toggle ptt & return freq
    void getFrequency(int freq); //Displays "freq" on current vfo according to ptt state

signals:
    void sendVfoFreq(int freq);
    void sendTxFreq(int freq, bool ptt);
    void setFreq(int freq, bool ptt);
    void frequencyChanged(long long freq);

protected:
    void wheelEvent( QWheelEvent*);
    void mousePressEvent( QMouseEvent*);
//    void closeEvent(QCloseEvent *);

private slots:
    void btnGrpBand(int);
    void on_pBtnvfoA_clicked();
    void on_pBtnvfoB_clicked();
    void on_pBtnScanDn_clicked();
    void on_pBtnScanUp_clicked();
    void on_pBtnSplit_clicked();
    void on_pBtnExch_clicked();
    void on_pBtnAtoB_clicked();
    void on_pBtnBtoA_clicked();
    void processRIT(int);

    void on_pBtnRIT_clicked();

private:
    Ui::vfo *ui;
    QSettings *settings;
    QBasicTimer timer;
    void writeA(int);
    void writeB(int);
    void vfoEnabled(bool setA, bool setB);
    void storeVFO();
    void setBandButton(int freq);
    void timerEvent(QTimerEvent *event);
    int **bands;
    int readA();
    int readB();
    int getDigit(int x, int y);
    int cur_Band;
    int browsePtr; // Memory browsing pointer
    bool ptt; // ptt on = true, ptt off = false
    char selectedVFO; //'A', 'B', 'S' to indicate which vfo state.
    long long spectrumFrequency;
    enum BandData
        {
            bDat_mem00,
            bDat_mem01,
            bDat_mem02,
            bDat_mem03,
            bDat_cFreq,
            bDat_fqmin,
            bDat_fqmax,
            bDat_modee,
            bDat_filtH,
            bDat_filtL,
            bDat_index
        };

};

#endif // VFO_H
