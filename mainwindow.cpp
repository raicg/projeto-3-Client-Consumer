#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <vector>


using namespace std;



MainWindow::MainWindow(QWidget *parent) : //funcao construtora
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);

  connect(ui->pushButtonConnect, //botao connect
          SIGNAL(clicked(bool)),
          this,
          SLOT(TcpConnect()));

  connect(ui->pushButtonDisconnect, //botao disconnect
          SIGNAL(clicked(bool)),
          this,
          SLOT(TcpDisconnect()));

  connect(ui->pushButtonUpdate,  //botao update
          SIGNAL(clicked(bool)),
          this,
          SLOT(updateList()));

  connect(ui->horizontalSliderTime, //barra horizontal timer
          SIGNAL(valueChanged(int)),
          ui->lcdNumberTime,
          SLOT(display(int)));

  connect(ui->pushButtonStart, // botao start
          SIGNAL(clicked(bool)),
          this,
          SLOT(getData()));
}


 // funcao connect, ira se conectar ao servidor
void MainWindow::TcpConnect(){
    socket->connectToHost(ui->lineEditIP->text(),1234); //porta 1234
    if(socket->waitForConnected(3000)){
      qDebug() << "Connected";
    }
    else{
      qDebug() << "Disconnected";
    }
}

// funcao disconnect, ira se desconectar do servidor
void MainWindow::TcpDisconnect(){
    socket->disconnectFromHost();
    if(socket->waitForDisconnected(3000) || socket->state() == QAbstractSocket::UnconnectedState){
        qDebug() << "Disconnected";
    }
}


// funcao updateList, ira atualizar a lista de produtores conectado ao servidor
void MainWindow::updateList(){
    ui->listWidget->clear();
    QString str;
    if(socket->state() == QAbstractSocket::ConnectedState){
      if(socket->isOpen()){
        qDebug() << "reading...";
        socket->write("list");
        socket->waitForBytesWritten();
        socket->waitForReadyRead();
        while(socket->bytesAvailable()){
          str = socket->readLine().replace("\n","").replace("\r","");
          ui->listWidget->addItem(str);
        }
      }
    }
}

// funcao getData, recebe os dados enviados do produtor ao servidor
void MainWindow::getData(){

  vector<float> valores;
  double tmp;
  QString str, ip;
  QStringList list;
  QDateTime datetime;
  vector<qint64> vtemp;
  qDebug() << "to get data...";
  if(socket->state() == QAbstractSocket::ConnectedState){
    if(socket->isOpen()){
       ip = ui->listWidget->currentItem()->text();
       str = "get " + ip;
      qDebug() << "reading...";
      socket->write(str.toStdString().c_str());
      socket->waitForBytesWritten();
      socket->waitForReadyRead();
      qDebug() << socket->bytesAvailable();
      while(socket->bytesAvailable()){
        str = socket->readLine().replace("\n","").replace("\r","");
        list = str.split(" ");
        if(list.size() == 2){
          datetime= QDateTime::fromString(list.at(0),Qt::ISODate);
          tmp = datetime.toMSecsSinceEpoch();
          vtemp.push_back(tmp);
          str = list.at(1);
          valores.push_back(str.toFloat());
          qDebug() << tmp << ": " << str;
        }
      }
    }
  }
}


MainWindow::~MainWindow()
{
  delete socket;
  delete ui;
}
