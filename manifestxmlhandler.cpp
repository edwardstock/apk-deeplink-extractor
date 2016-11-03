#include "manifestxmlhandler.h"
#include "manifestparser.h"

ManifestXmlHandler::ManifestXmlHandler(ManifestParser *parser): QXmlDefaultHandler()
{
    this->parser = parser;
}

ManifestXmlHandler::~ManifestXmlHandler()
{
}

bool ManifestXmlHandler::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts)
{
    qDebug() << "Tag name: " << localName;
//    qDebug() << "qName" << qName;
    if(localName == "data") {
        ManifestParser::Link link;
        size_t collected = 0;

        for(int i = 0; i < atts.length(); i++) {
            QString type = atts.type(i);
//            qDebug() << "Attr name: " << type;
            if(type == "android:scheme") {
                link.scheme = atts.value(i);
                collected++;
            }
            if(type == "android:host") {
                link.route = atts.value(i);
                collected++;
            }
        }

        if(collected == 2) {
            this->parser->deeplinks.push_back(link);
        }
    }

    return true;
}

bool ManifestXmlHandler::characters(const QString &ch)
{
    qDebug() << "Chars: " << ch;
}
