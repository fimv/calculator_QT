
#include <QtWidgets>
#include "Calculator.h"
#include <cmath>
# define PI          3.141592653589793238462643383279502884L /* pi */


// ----------------------------------------------------------------------
Calculator::Calculator(QWidget* pwgt/*= 0*/) : QWidget(pwgt)
{
    m_plcd = new QLCDNumber(12);
    m_plcd->setSegmentStyle(QLCDNumber::Flat);
    m_plcd->setMinimumSize(150, 50);

    QString bButtons[4] = {"sqrt", "reve", "squa", "CE"};

    QChar aButtons[4][4] = {
                            {'7', '8', '9', '/'},
                            {'4', '5', '6', '*'},
                            {'1', '2', '3', '-'},
                            {'0', '.', '=', '+'}
                           };

    //Layout setup
    QGridLayout* ptopLayout = new QGridLayout;
    ptopLayout->addWidget(m_plcd, 0, 0, 1, 4);
   // ptopLayout->addWidget(createButton("CE"), 1, 3);

    for (int i = 0; i < 4; ++i) {
                   ptopLayout->addWidget(createButton(bButtons[i]), 2 , i);
            }


    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
           ptopLayout->addWidget(createButton(aButtons[i][j]), i + 3, j);
        }
    }
    setLayout(ptopLayout);
}

// ----------------------------------------------------------------------
QPushButton* Calculator::createButton(const QString& str)
{
    QPushButton* pcmd = new QPushButton(str);
    pcmd->setMinimumSize(60, 60);
    connect(pcmd, SIGNAL(clicked()), SLOT(slotButtonClicked()));
    return pcmd;
}


// ----------------------------------------------------------------------
void Calculator::calculate()
{
    qreal   fOperand2    = m_stk.pop().toFloat();
    QString strOperation = m_stk.pop();
    qreal   fOperand1    = m_stk.pop().toFloat();
    qreal   fResult      = 0;


    if (strOperation == "+") {
        fResult = fOperand1 + fOperand2;
    }
    if (strOperation == "-") {
        fResult = fOperand1 - fOperand2;
    }
    if (strOperation == "/") {
        fResult = fOperand1 / fOperand2;
    }
    if (strOperation == "*") {
        fResult = fOperand1 * fOperand2;
    }

    m_plcd->display(fResult);
}


// ----------------------------------------------------------------------
void Calculator::calculate2()
{
    QString strOperation = m_stk.pop();
    qreal   fOperand1    = m_stk.pop().toFloat();
    qreal   fResult      = 0;



    if (strOperation == "sqrt") {
        fResult = std::sqrt(fOperand1);
    }

    if (strOperation == "reve") {
        fResult = 1 / fOperand1;
    }
    if (strOperation == "squa") {
        fResult = fOperand1 * fOperand1;
    }
    m_plcd->display(fResult);
}

// ----------------------------------------------------------------------
void Calculator::slotButtonClicked()
{
    QString str = ((QPushButton*)sender())->text();

    if (str == "CE") {
        m_stk.clear();
        m_strDisplay = "";
        m_plcd->display("0");
        return;
    }


    if (str.contains(QRegExp("[0-9]"))) {
        m_strDisplay += str;
        m_plcd->display(m_strDisplay.toDouble());
    }
    else if (str == ".") {
        m_strDisplay += str;
        m_plcd->display(m_strDisplay);
    }
    else {
     if ((str == "sqrt") || (str == "reve") || (str == "squa")) {
          // m_strDisplay += str;
          m_stk.push(QString().setNum(m_plcd->value()));
           // m_stk.push(0);
            m_stk.push(str);
            calculate2();
          m_stk.clear();
           m_stk.push(QString().setNum(m_plcd->value()));
             }

          else if   (m_stk.count() >= 2 ){
            m_stk.push(QString().setNum(m_plcd->value()));
            calculate();
            m_stk.clear();
            m_stk.push(QString().setNum(m_plcd->value()));
            m_strDisplay = "";
            if (str != "=") {
             m_stk.push(str);

          }

          }

            else {
            m_stk.push(QString().setNum(m_plcd->value()));
            m_stk.push(str);
            m_strDisplay = "";
        }
}
}

