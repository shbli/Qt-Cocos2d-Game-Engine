#ifndef XML_CACHE_H
#define XML_CACHE_H

/*

  This is a singleton class, that controlls the game, it contains many static instances, for all the objects to contact

*/

#include <QObject>
#include <QDomDocument>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QTime>

//#define debug_xml_cache

#define max_number_of_cached_files 40

struct xmlElement {
    QDomDocument* domDocumentPtr;
    int xmlElementUsage;
    QString xml_file_name;
};

class xml_cache : public QObject
{
    Q_OBJECT
public:
    ~xml_cache();
    static xml_cache* shared_xml_cache();
    QDomDocument* get_xml_document(QString xml_file_name);
    QDomDocument* release_xml_document(QString xml_file_name);
    void clear_cache();

private:

    QList <xmlElement> xml_elements_list;
    static xml_cache* xmlSharedCache;
    xml_cache();
    void removeLeastUsedElement();
#ifdef debug_xml_cache
    void print_all_elements();
#endif
    
};

#endif // XML_CACHE_H
