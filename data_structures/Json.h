#ifndef JSON_H
#define JSON_H

#include "ByteBuffer.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "String.h"
#include "StringView.h"
#include "RefPointer.h"
#include "Vector.h"

namespace Json {
    
class Number {
    public:
    Number();
    Number(uint num):value(num){ }
    uint value;
    void show(){
        printf("%u", value);
    }
};

class Array;
class JsonObject;

class JsonValue {
public:
    JsonValue();
    JsonValue(String);
    JsonValue(Number);
    JsonValue(Array);
    JsonValue(JsonObject);

    String* asString();
    Number* asNumber();
    Array* asArray();
    JsonObject* asObject();

    void operator =(JsonValue& other);
    void operator =(String);
    void operator =(Number);
    void operator =(Array);
    void operator =(JsonObject);
    void show();

    union JsonV {
        String* str;
        Number* number;
        Array* array;
        JsonObject* object;
        bool boolean;
    };
    JsonV m_value;
    String m_type;
};


class Array {
public:
    Array();
    void append(JsonValue value);
    JsonValue operator [](uint index);
    void show();
private:
    Vector<JsonValue> m_array;
};

class JsonObject {
public:
    JsonValue operator [](char key[]);
    void set(String,String);
    void set(String,Number);
    void set(String,Array);
    void set(String,JsonObject);

    void show();
private:
    HashTable<String,JsonValue> objects;

};

};
#endif