#include "Json.h"

using namespace Json;

Number::Number(){ }
Array::Array(){ }

JsonValue::JsonValue(){ }

JsonValue::JsonValue(String value){
    m_value.str = new String(value);
    m_type.set("string");
}

JsonValue::JsonValue(Number value){ 
    m_value.number = new Number(value);
    m_type.set("number");
}

JsonValue::JsonValue(Array value){ 
    m_value.array = new Array(value);
    m_type.set("array");
}

JsonValue::JsonValue(JsonObject value){ 
    m_value.object = new JsonObject(value);
    m_type.set("object");
}

String* JsonValue::asString(){
    return m_value.str;
}

Number* JsonValue::asNumber(){
    return m_value.number;
}

Array* JsonValue::asArray(){
    return m_value.array;
}

JsonObject* JsonValue::asObject(){
    return m_value.object;
}

void JsonValue::operator=(JsonValue& other){
    m_type = other.m_type;
    m_value = other.m_value;
}

void JsonValue::operator=(String str){
    m_value.str = new String(str);
    m_type.set("string");
}

void JsonValue::operator=(Number number){
    m_value.number = new Number(number);
    m_type.set("number");
}

void JsonValue::operator=(Array array){
    m_value.array = new Array(array);
    m_type.set("array");
}

void JsonValue::operator=(JsonObject object){
    m_value.object = new JsonObject(object);
    m_type.set("object");
}

void JsonValue::show(){
    String string("string");
    if(m_type == string){
        m_value.str->show();
        printf(" ");
        return;
    }

    String number("number");
    if(m_type == number){
        m_value.number->show();
        printf(" ");
        return;
    }

    String array("array");
    if(m_type == array){
        m_value.array->show();
        printf(" ");
        return;
    }

    String object("object");
    if(m_type == object){
        m_value.object->show();
        printf(" ");
        return;
    }
}

JsonValue Array::operator[](uint index){
    if(m_array[index] != nullptr)
        return *m_array[index];
    return { nullptr };
}

void Array::append(JsonValue value){
    m_array.append(value);
}

void Array::show(){
    printf("[ ");
    for(uint i = 0; i < m_array.size(); i++){
        m_array[i]->show();
        printf(" ");
    }
    printf("]");
}

JsonValue JsonObject::operator[](char key[]){
    JsonValue js_value;
    if(objects.get(String(key), js_value)){
        return js_value;
    }
    return { nullptr };
}

void JsonObject::set(String key,String value){
    objects.set(key, value);
}

void JsonObject::set(String key,Number value){
    objects.set(key, value);
}

void JsonObject::set(String key,Array value){
    objects.set(key, value);
}

void JsonObject::set(String key,JsonObject value){
    objects.set(key, value);
}

void JsonObject::show(){
    objects.show();
}