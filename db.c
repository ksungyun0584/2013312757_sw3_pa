/*-----------------------------------------------------------
 *
 * SSE2033: System Software Experiment 2 (Fall 2018)
 *
 * Skeleton code for PA#1
 * 
 * CSLab, Sungkyunkwan University
 *
 * Student Id   : 2013313700
 * Student Name : Shin Junho
 *
 *-----------------------------------------------------------
 */



#include "db.h"
#include <stdio.h>
#include <stdlib.h>


db_t* db_open(int size) {
	db_t* db = (db_t*)malloc(sizeof(db_t));
	L_list* ll;
	int i;
	db -> size = size;

	db -> Table = (L_list**)malloc(sizeof(L_list*)*size);
	
	for(i=0; i<size; i++){
		ll = (L_list*)malloc(sizeof(L_list));
		ll -> head = NULL;
		ll -> tail = NULL;
		db -> Table[i] = ll;
	}
	
	return db;
}

void db_close(db_t* db) {
	int i;
	L_node* p;
	L_node* q;
	for(i=0; i<db -> size; i++){
		p = db -> Table[i] -> head;
		while(p != NULL){
			q = p;
			p = p -> next;
			free(q -> key);
			free(q -> value);
			free(q);
		}
		free(db -> Table[i]);
	}
	free(db -> Table);
	free(db);
}

void db_put(db_t* db, 
			char* key, int keylen,
			char* val, int vallen) {
	int i;
	int sum=0;
	int index;
	int diff;
	L_list* ll;
	L_node* p = (L_node*)malloc(sizeof(L_node));
	L_node* q;
	for(i=0; i<keylen; i++){
		sum += key[i];
	}
	index = sum%(db->size);
	ll = db -> Table[index];
	if(ll -> head == NULL && ll -> tail == NULL){
		p -> key = (char*)malloc(sizeof(char)*(keylen+1));
		p -> value = (char*)malloc(sizeof(int));
		for(i=0; i<keylen; i++){
			p -> key[i] = key[i];
		}
		p -> key[i] = '\0';
		p -> keylen = keylen;
		*((int*)p -> value) = 1;
		p -> vallen = vallen;
		p -> next = NULL;
		ll -> head = p;
		ll -> tail = p;
		return;
	}
	q = ll -> head;
	while(q != NULL){
		
		if(q -> keylen != keylen){
			q = q -> next;
			continue;
		}

		diff = 0;
		for(i=0; i<keylen; i++){
			if(key[i] != q -> key[i]){
				diff = 1;
				break;
			}
		}

		if(!diff){
			free(p);
			*((int*)q -> value) += 1;
			return;
		}

		q = q -> next;
		
	}

	q = ll -> tail;

	p -> key = (char*)malloc(sizeof(char)*(keylen+1));
	p -> value = (char*)malloc(sizeof(int));
	for(i=0; i<keylen; i++){
		p -> key[i] = key[i];
	}
	p -> key[i] = '\0';
	p -> keylen = keylen;
	*((int*)p -> value) = 1;
	p -> vallen = vallen;
	p -> next = NULL;
	q -> next = p;
	ll -> tail = p;
	return;

}

/* Returns NULL if not found. A malloc()ed array otherwise.
 * Stores the length of the array in *vallen */
char* db_get(db_t* db,
			char* key, int keylen,
			int* vallen) {
	char* value = NULL;
	int sum=0;
	int index;
	int diff;
	int i;
	L_list* ll;
	L_node* p;
	for(i=0; i<keylen; i++){
		sum += key[i];
	}
	index = sum%(db->size);
	ll = db -> Table[index];
	
	if(ll -> head == NULL && ll -> tail == NULL){
		return value;
	}
	p = ll -> head;
	while(p != NULL){
		
		if(p -> keylen != keylen){
			p = p -> next;
			continue;
		}

		diff = 0;
		for(i=0; i<keylen; i++){
			if(key[i] != p -> key[i]){
				diff = 1;
				break;
			}
		}

		if(!diff){
			*vallen = p -> vallen;
			value = (char*)malloc(sizeof(char)*(*vallen));
			for(i=0; i<*vallen; i++){
				value[i] = p -> value[i];
			}
			value[i] = '\0';
			return value;
		}

		p = p -> next;
		
	}

	return value;
}



