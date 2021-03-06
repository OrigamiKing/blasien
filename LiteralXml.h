/****************************************************************************
**
** Copyright (C) 2015 Jos van den Oever
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 3 as published by the Free Software Foundation and appearing
** in the file lgpl-3.0.txt included in the packaging of this file.  Please
** review the following information to ensure the GNU Lesser General Public
** License requirements will be met: https://www.gnu.org/licenses/lgpl.html.
**
****************************************************************************/
#ifndef LITERALXML_H
#define LITERALXML_H

template <typename Tag, typename... Atts>
struct ElementStart;

template <typename String_>
struct QName {
    using String = String_;
    static const bool is_tag = true;
    String ns_;
    String name_;
    QName(const String& ns, const String& name) :ns_(ns), name_(name) {}
    const String& ns() const { return ns_; }
    const String& name() const { return name_; }
};

// represents an xpath Step which consists of a NameTest qualified by a Predicate
template <typename NameTestTag, typename Predicate>
struct NameTestWithPredicate {
    const NameTestTag tag;
    const Predicate predicate;
    NameTestWithPredicate(const NameTestTag& testTag, const Predicate& p) :tag(testTag), predicate(p) {}
};

template <typename Tag>
struct AttributeName {
    const Tag tag;
    AttributeName(const Tag& t) :tag(t) {}
};

template <typename XmlTag_>
struct AttributeNode {
    using XmlTag = XmlTag_;
    using String = typename XmlTag::String;
    String value;
    AttributeNode(const String& v) :value(v) {}
};

template <typename String_, const String_* Ns, const String_* Name>
struct XmlTag {
    using String = String_;
    using Self = XmlTag<String,Ns, Name>;
    static constexpr bool is_tag = true;
    static const QName<String> qname;
    static const String& ns() {
        return qname.ns();
    }
    static const String& name() {
        return qname.name();
    }
    template <typename... Atts>
    ElementStart<Self, Atts...>
    operator()(Atts... atts) const {
        return ElementStart<Self,Atts...>(atts...);
    }
    template <typename Predicate>
    NameTestWithPredicate<Self, Predicate>
    operator[](const Predicate& p) const {
        return NameTestWithPredicate<Self,Predicate>(*this, p);
    }
    AttributeName<Self> operator~() const {
        return AttributeName<Self>(*this);
    }
    // set the attribute
    AttributeNode<Self> operator=(const String& val) const {
        return AttributeNode<Self>(val);
    }
};

template <typename String, const String* Ns, const String* Name>
const QName<String> XmlTag<String, Ns, Name>::qname(*Ns, *Name);

template <typename Tag_, typename... Atts>
struct ElementStart {
    using Tag = Tag_;
    const std::tuple<Atts...> atts;
    ElementStart(Atts... atts_) :atts(atts_...) {}
};

struct TextType;
struct AnyType;

template <typename NodeType>
struct allowed_child_types {
    using types = std::tuple<>;
};

template <>
struct allowed_child_types<AnyType> {
    using types = std::tuple<AnyType,TextType>;
};

template <>
struct allowed_child_types<TextType> {
    using types = std::tuple<>;
};

#endif // LITERALXML_H
