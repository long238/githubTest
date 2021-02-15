#ifndef MYSYNTAXHIGHLIGHTER_H
#define MYSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class MySyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    MySyntaxHighlighter(QTextDocument *parent = 0);

protected:
    //重写实现该方法
    void highlightBlock(const QString &text);
};

#endif // MYSYNTAXHIGHLIGHTER_H
