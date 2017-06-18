#include "widget.h"
#include "ui_widget.h"
#include "ethernet.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    Ethernet *et = new Ethernet( ui->lineEdit_preamble->text(), ui->lineEdit_sfd->text(), ui->lineEdit_TMAC->text(),
                                ui->lineEdit_SMAC->text(), ui->textEdit_DATA->toPlainText());
    ui->label_LengthValue->setText(QString::number(ui->textEdit_DATA->toPlainText().length(), 16));
    ui->label_fcsvalue->setText(et->GetCheck(et->GetData()));
}

