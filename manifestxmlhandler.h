#ifndef MANIFESTXMLHANDLER_H
#define MANIFESTXMLHANDLER_H
#include <QVector>
#include <QXmlSimpleReader>
#include <QString>
#include <QFile>
#include <QDebug>

class ManifestParser; // fd

class ManifestXmlHandler: public QXmlDefaultHandler
{
public:
    ManifestXmlHandler(ManifestParser *parser);
    ~ManifestXmlHandler();

    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
    bool characters(const QString &ch);

private:
    ManifestParser *parser;
};

#endif // MANIFESTXMLHANDLER_H
