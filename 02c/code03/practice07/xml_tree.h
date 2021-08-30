#include "typedef.h"
#include "xml_builder.h"

#ifndef XML_TREE_H
#define XML_TREE_H

typedef enum _XmlNodeType
{
    XML_NODE_NONE,
    XML_NODE_PI,
    XML_NODE_TEXT,
    XML_NODE_NORMAL,
    XML_NODE_COMMENT
} XmlNodeType;

typedef struct _XmlAttr
{
    char *name;
    char *value;

    struct _XmlAttr *next;
} XmlAttr;

typedef struct _XmlNodePi
{
    char *name;
    XmlAttr *first_attr;
} XmlNodePi;

typedef struct _XmlNodeNormal
{
    char *name;
    XmlAttr *first_attr;
} XmlNodeNormal;

typedef struct _XmlNode
{
    XmlNodeType type;
    union
    {
        char *text;
        char *comment;
        XmlNodePi pi;
        XmlNodeNormal normal;
    } u;
    struct _XmlNode *parent;
    struct _XmlNode *children;
    struct _XmlNode *sibling;
} XmlNode;

typedef Ret (*XmlNodeVisitFunc)(void* ctx, int level, XmlNode* node);

XmlNode* xml_node_create_text(const char* text);
XmlNode* xml_node_create_comment(const char* comment);
XmlNode* xml_node_create_pi(const char* name, const char** attrs);
XmlNode* xml_node_create_normal(const char* name, const char** attrs); 
XmlNode* xml_node_append_sibling(XmlNode* node, XmlNode* sibling);
XmlNode* xml_node_append_child(XmlNode* node, XmlNode* child);

void xml_node_visit(XmlNode* node, XmlBuilder* builder);
void xml_node_print(XmlNode* node);

void xml_node_destroy(XmlNode* node);

#endif