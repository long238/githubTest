#include "mysyntaxhighlighter.h"
#include <QRegExp>

MySyntaxHighlighter::MySyntaxHighlighter(QTextDocument *parent):QSyntaxHighlighter(parent)
{

}

void MySyntaxHighlighter::highlightBlock(const QString &text)
{
    QTextCharFormat format;//字符格式
    format.setFontWeight(QFont::Bold);//设置文本格式的字体粗细为粗细
    format.setBackground(Qt::red);//设置背景色
    format.setForeground(Qt::green);//设置前景(字体)色

    QString pattern = "\\bgood\\b";
    QRegExp expression(pattern);

    int index = text.indexOf(expression);
    while(index >= 0)
    {
        int length = expression.matchedLength();//匹配到的字符长度
        setFormat(index,length,format);
        index = text.indexOf(expression,index+length);
    }
}
