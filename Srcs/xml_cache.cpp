#include "xml_cache.h"
#include "global_keys.h"

xml_cache* xml_cache::xmlSharedCache = NULL;

//constructor
xml_cache::xml_cache() {

}



//destructor
xml_cache::~xml_cache() {

}

xml_cache *xml_cache::shared_xml_cache() {
    if (xmlSharedCache == NULL) {
        xmlSharedCache = new xml_cache;
    }
    return xmlSharedCache;
}

QDomDocument *xml_cache::get_xml_document(QString xml_file_name) {


    for (int i = 0; i < xml_elements_list.size(); i++) {
        if (xml_elements_list.at(i).xml_file_name == xml_file_name  ) {
            //cahced xml is found
            xmlElement tempElemen;
            tempElemen.xml_file_name = xml_elements_list.at(i).xml_file_name;
            tempElemen.domDocumentPtr = xml_elements_list.at(i).domDocumentPtr;
            tempElemen.xmlElementUsage = xml_elements_list.at(i).xmlElementUsage + 1;
            xml_elements_list.takeAt(i);
            xml_elements_list.append(tempElemen);
            removeLeastUsedElement();
            return tempElemen.domDocumentPtr;
        }
    }


   //no cahced xml matching the same name is found
    QDomDocument *xmlDocument = new QDomDocument;
    QFile openxml(
            #ifdef useResourcesForFiles
                resourcesPreFixForFile +
            #endif
                xml_file_name);

    if (! openxml.open( QIODevice::ReadOnly | QIODevice::Text)) {
        //error message
        QMessageBox box;
        QString messagetext;
        messagetext = QString::fromUtf8("Error, can't read") + xml_file_name + " Please contact us with a screen shot, or a copy of this error message";
        box.setText(messagetext);
        box.exec();
    } else {

        xmlDocument->setContent(&openxml);
    }

    openxml.close();


    xmlElement tempElemen;
    tempElemen.xml_file_name = xml_file_name;
    tempElemen.domDocumentPtr = xmlDocument;
    tempElemen.xmlElementUsage = 1;
    xml_elements_list.append(tempElemen);
    removeLeastUsedElement();
    return tempElemen.domDocumentPtr;
}

QDomDocument *xml_cache::release_xml_document(QString xml_file_name) {
    for (int i = 0; i < xml_elements_list.size(); i++) {
        if (xml_elements_list.at(i).xml_file_name.contains(xml_file_name,Qt::CaseInsensitive)) {
            //cahced xml is found
            xmlElement tempElemen;
            tempElemen.xml_file_name = xml_elements_list.at(i).xml_file_name;
            tempElemen.domDocumentPtr = xml_elements_list.at(i).domDocumentPtr;
            tempElemen.xmlElementUsage = xml_elements_list.at(i).xmlElementUsage - 1;
            xml_elements_list.replace(i,tempElemen);
        }
    }
}

void xml_cache::clear_cache() {
    while (!xml_elements_list.isEmpty()) {
        //the element is unused, let's go ahead and remove it
        delete xml_elements_list.takeFirst().domDocumentPtr;
    }
}

void xml_cache::removeLeastUsedElement() {
    if (xml_elements_list.size() > max_number_of_cached_files) {
        //we need to remove one element if possible
        if (xml_elements_list.first().xmlElementUsage <= 0) {
            //the element is unused, let's go ahead and remove it
            delete xml_elements_list.takeFirst().domDocumentPtr;
        }
    }
#ifdef debug_xml_cache
    print_all_elements();
#endif
}

#ifdef debug_xml_cache
void xml_cache::print_all_elements() {
    fileStream << " --- Printing all elementts --- ";
    for (int i = 0; i < xml_elements_list.size(); i++) {
        fileStream << "Element " << i << " xml = " << xml_elements_list.at(i).xml_file_name << " usage = " << xml_elements_list.at(i).xmlElementUsage;
    }
    fileStream << " --- Finished printing all elementts --- ";
}
#endif
