#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <QXmlStreamWriter>
#include <LiteralXml.h>
#include <XmlSink.h>

template <typename Base = void, typename Tag = void>
class XmlWriter {
public:
    static constexpr bool is_xmlsink = true;
    QXmlStreamWriter& writer;
    explicit XmlWriter(QXmlStreamWriter& w) :writer(w) {}
    template <typename ChildTag>
    void startElement(const ChildTag &tag) const {
        writer.writeStartElement(tag.ns(), tag.name());
    }
    void endElement() const {
        writer.writeEndElement();
    }
    template <typename ChildTag>
    void writeAttribute(const ChildTag &tag, const QString& value) const {
        writer.writeAttribute(tag.ns(), tag.name(), value);
    }
    void writeCharacters(const QString& value) const {
        writer.writeCharacters(value);
    }
};

#endif // XMLWRITER_H
