#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>



void parseChannel (xmlDocPtr doc, xmlNodePtr cur);
void parseItem(xmlDocPtr doc, xmlNodePtr cur);
static void parseDoc(char *docname);

int main(int argc, char **argv) 
{ 
	char *docname; 
	if (argc <= 1) 
	{ 
		printf("Usage: %s docname\n", argv[0]); 
		return(0); 
	} 
	docname = argv[1]; 
	parseDoc(docname); 
	return 1; 
}


void parseChannel (xmlDocPtr doc, xmlNodePtr cur)
{
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if((!xmlStrcmp(cur->name, (const xmlChar *) "item"))) { 
			parseItem(doc, cur);
		}
		else if((!xmlStrcmp(cur->name, (const xmlChar *) "title"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			printf("BLOG NAME: %s\n", key);
			xmlFree(key);
		}
		else if((!xmlStrcmp(cur->name, (const xmlChar *) "link"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			printf("MY BLOG LINK : %s\n", key);
			xmlFree(key);
		}
		cur = cur->next;
	}
	xmlFreeDoc(doc);
	return;
}




void parseItem(xmlDocPtr doc, xmlNodePtr cur)
{
	xmlChar *key;
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		if((!xmlStrcmp(cur->name, (const xmlChar *) "title"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			printf("제목: %s\n", key);
			xmlFree(key);
		}
		else if((!xmlStrcmp(cur->name, (const xmlChar *) "description"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			printf("내용: %s\n", key);
			xmlFree(key);
		}
		else if((!xmlStrcmp(cur->name, (const xmlChar *) "author"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			printf("글쓴이: %s\n", key);
			xmlFree(key);
		}
		else if((!xmlStrcmp(cur->name, (const xmlChar *) "pubDate"))) {
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode,1);
			printf("등록일자: %s\n", key);
		}
		cur = cur->next;
	}
	return;
}

static void parseDoc(char *docname)
{
	xmlDocPtr doc;
	xmlNodePtr cur;
	doc = xmlParseFile(docname);
	if (doc == NULL ) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return;
	}
	
	cur = xmlDocGetRootElement(doc);
	
	if (cur == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return;
	}
	
	if (xmlStrcmp(cur->name, (const xmlChar *) "rss")) {
		fprintf(stderr,"document of the wrong type, root node != rss");
		xmlFreeDoc(doc);
		return;
	}
	
	printf("---%s---\n", cur->name);
	cur = cur->xmlChildrenNode;  //channel
	while (cur != NULL) {
		printf("%s\n", cur->name);
		if ((!xmlStrcmp(cur->name, (const xmlChar *) "channel"))){
	//		parseChannel (doc, cur);
		}
		
		cur = cur->next;
	}
	
	xmlFreeDoc(doc);
	return;
}
