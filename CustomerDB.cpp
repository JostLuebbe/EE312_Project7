/*
 * Name: Jost Luebbe
 * EID: jl64249
 * Project 7, CRM part 2
 * EE 312, Spring 2017
 */
#include <iostream>
#include <cassert>
#include "String.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(String name) { // done, please do not edit
	this->bottles = 0;
	this->rattles = 0;
	this->diapers = 0;
	this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

int CustomerDB::size(void) {
	return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
	delete[] this->data;
}

void CustomerDB::clear(void) { // done, please do not edit
	delete[] this->data;
	this->capacity = default_capacity;
	this->data = new Customer[this->capacity];
	this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
	assert(k >= 0 && k < this->length);
	return this->data[k];
}

Customer& CustomerDB::operator[](String name) { // not done, your effort goes here
	for(int i=0; i<this->size(); i++){
		if(this->data[i].name == name){
			return data[i];
		}
	}

	if(this->size()==this->capacity){
		this->capacity *= 2;
		Customer* c_data = new Customer[capacity];
		for(int i=0; i<this->size();i++){
			c_data[i].name = this->data[i].name;
			c_data[i].bottles = this->data[i].bottles;
			c_data[i].diapers = this->data[i].diapers;
			c_data[i].rattles = this->data[i].rattles;
		}
		delete[] data;
		this->data = c_data;
	}
	Customer* c = new Customer(name);
	this->data[this->size()] = *c;
	this->length++;
	return *c;
}



bool CustomerDB::isMember(String name) { // not done, your effort goes here
	for(int i=0; i<this->size(); i++){
		if(this->data[i].name == name){
			return true;
		}
	}
	return false;
}


