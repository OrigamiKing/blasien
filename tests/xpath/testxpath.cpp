#include <QObject>
#include <QTest>
#include <XmlPath.h>
#include <XmlBuilder.h>

class TestXPath : public QObject
{
    Q_OBJECT
private Q_SLOTS: // tests
    void iterateWithTag();
    void iterateWithTags();
    void iterateWithOr();

};

namespace {
const QString htmlns = QStringLiteral("http://www.w3.org/1999/xhtml");
const QString htmlTag = QStringLiteral("html");
const QString headTag = QStringLiteral("head");
const QString bodyTag = QStringLiteral("body");
const QString titleTag = QStringLiteral("title");
const QString idTag = QStringLiteral("id");
const QString classTag = QStringLiteral("class");
const QString empty;
XmlTag<&htmlns, &htmlTag, false, true> html;
XmlTag<&htmlns, &headTag, false, true> head;
XmlTag<&htmlns, &bodyTag, false, true> body;
XmlTag<&htmlns, &titleTag, false, true> title;
//XmlTag<&empty, &idTag, true, false> id;
//XmlTag<&empty, &classTag, true, false> class_;

QDomDocument getExampleDoc1() {
    QDomDocument dom("test");
    XmlBuilder(dom)
    <html
      <head
        <title
          <"Hello World!"
        >title
      >head
      <body
      >body
    >html;
    return dom;
}
}

void
TestXPath::iterateWithTag() {
    QDomDocument dom = getExampleDoc1();
    int count = 0;
    for (auto node: dom/html) {
         ++count;
    }
    QCOMPARE(count, 1);
}

void
TestXPath::iterateWithTags() {
    QDomDocument dom = getExampleDoc1();
    int count = 0;
    for (auto node: dom/html/head) {
         ++count;
    }
    QCOMPARE(count, 1);
}

void
TestXPath::iterateWithOr() {
    QDomDocument dom = getExampleDoc1();
    int count = 0;
    for (auto node: dom/html/(body|head)) {
        ++count;
    }
    QCOMPARE(count, 2);
}

QTEST_APPLESS_MAIN(TestXPath)
#include "testxpath.moc"
