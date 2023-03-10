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
    if(m_type == "string"){
        m_value.str->show();
        printf(" ");
        return;
    }

    if(m_type == "number"){
        m_value.number->show();
        printf(" ");
        return;
    }

    if(m_type == "array"){
        m_value.array->show();
        printf(" ");
        return;
    }

    if(m_type == "object"){
        m_value.object->show();
        printf(" ");
        return;
    }

    if(m_type == "boolean"){
        printf("%s ", m_value.boolean ? "true" : "false");
        return;
    }

    if(m_type == "null"){
        printf("null ");
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

void JsonObject::set(String key,JsonValue value){
    objects.set(key, value);
    /*if(value.m_type == String("string")){
        set(key, *value.asString());
    }
    if(value.m_type == String("number")){
        set(key, *value.asNumber());
    }
    if(value.m_type == String("array")){
        set(key, *value.asArray());
    }
    if(value.m_type == String("object")){
        set(key, *value.asObject());
    }*/
}

void JsonObject::show(){
    objects.show();
}

Parser::Parser(StringView input):m_input(input){
    // Initilization the Parser.
}

Parser::~Parser(){ }

uint Parser::increment(){
    pos += 1;
    return pos;
}

char Parser::lookAhead(){
    return m_input[pos + 1];
}

char Parser::getCur(){
    return m_input[pos];
}

void Parser::skipWhiteSpace(){
    while (getCur() == '\x20' || getCur() == '\x0a' || getCur() == '\x0d' || getCur() == '\x09')
    {
        increment();
    }
}

JsonErr Parser::parseObject(JsonObject& obj){
    // FIXME: handle Errors.
    if(getCur() == '{'){
        increment();
        while(!is_eof() && getCur() != '}'){
            String* key = new String;
            skipWhiteSpace();
            parseString(*key);
            skipWhiteSpace();
            if(getCur() == ':'){
                increment();
                skipWhiteSpace();
                JsonValue val;
                parseValue(val);
                obj.set(*key, val);
                skipWhiteSpace();
                if(getCur() == ','){
                    increment();
                    continue;
                }else{
                    if(getCur() != '}'){
                        printf("Error at: %c\n", getCur());
                        return JsonErr::EXPECTED_COMMA_OR_END_BRACKET;
                    }
                }
            }else{
                printf("Error at: %c Expected ':' !\n", getCur());
                return JsonErr::EXPECTED_COLON; // Expected ':'
            }
        }
        increment();
        return JsonErr::VALID_JSON_DATA;
    }
}

JsonErr Parser::parseString(String& str){
    if(!is_eof() && getCur() == '"'){
        increment();
        while(!is_eof() && getCur() != '"'){
            if(getCur() == '\\'){
                parseEscape(str);
            }
            str.push(getCur());
            increment();
        }
        if(is_eof() || getCur() != '"')
            return JsonErr::EXPECTED_DOUBLE_QUATS;
        return JsonErr::VALID_STRING;
    }else{
        return JsonErr::EXPECTED_DOUBLE_QUATS;
    }
}

JsonErr Parser::parseEscape(String& str){
    // TODO: parse Escaped Values.
}

JsonErr Parser::parseValue(JsonValue& value){
    switch (getCur())
    {
    case '"':
        value.m_value.str = new String;
        value.m_type.set("string");
        return parseString(*value.m_value.str);
        break;
    
    case 't':
    case 'f':
        value.m_type.set("boolean");
        return parseBoolean(value.m_value.boolean);
        break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '-':
        value.m_type.set("number");
        value.m_value.number = new Number;
        return parseNumber(*value.m_value.number);
        break;
    case 'n':
        value.m_type.set("null");
        return parseNull(value);
        break;
    case '[':
        value.m_value.array = new Array;
        value.m_type.set("array");
        return parseArray(*value.m_value.array);
        break;
    case '{':
        value.m_value.object = new JsonObject;
        value.m_type.set("object");
        return parseObject(*value.m_value.object);
        break;
    default:
        break;
    }
    return JsonErr::INVALID_CHARCATER;
}

JsonErr Parser::parseBoolean(bool& v){
    if(getCur() == 't'){
        char* true_str = "true";
        for(uint i = 0; i < 4; i++){
            if(getCur() != true_str[i]){
                return JsonErr::INVALID_KEYWORD;
            }
            increment();
        }
        v = true;
        return JsonErr::VALID_BOOLEAN;
    }
    if(getCur() == 'f'){
        char* false_str = "false";
        for(uint i = 0; i < 5; i++){
            if(getCur() != false_str[i]){
                return JsonErr::INVALID_KEYWORD;
            }
            increment();
        }
        v = false;
        return JsonErr::VALID_BOOLEAN;
    }
    return JsonErr::INVALID_KEYWORD;
}

JsonErr Parser::parseNull(JsonValue& v){
    if(getCur() == 'n'){
        char* null_str = "null";
        for(uint i = 0; i < 4; i++){
            if(getCur() != null_str[i]){
                return JsonErr::INVALID_KEYWORD;
            }
            increment();
        }
        v.m_value.null = nullptr;
        return JsonErr::VALID_NULL;
    }
    return JsonErr::INVALID_KEYWORD;
}

JsonErr Parser::parseNumber(Number& num){
    // TODO: parse a number. Json Spec: integer fraction exponent
    String str_num;
    if(getCur() == '-'){
        str_num.push('-');
        increment();
    }
    while(!is_eof() && getCur() >= '0' && getCur() <= '9'){
        str_num.push(getCur());
        increment();
    }
    num.value = str_num.parseInt();
    return JsonErr::VALID_NUMBER;
}

JsonErr Parser::parseArray(Array& arr){
    if(getCur() == '['){
        increment();
        while(!is_eof() && getCur() != ']'){
            skipWhiteSpace();
            JsonValue val;
            parseValue(val);
            arr.append(val);
            skipWhiteSpace();
            if(getCur() == ','){
                increment();
                continue;
            }
        }
        if(is_eof() || getCur() != ']'){
            return JsonErr::EXPECTED_END_SQUARE_BRACKET;
        }
        increment();
        return JsonErr::VALID_ARRAY;
    }else{
        return JsonErr::EXPECTED_START_SQUARE_BRACKET;
    }
}

JsonErr Parser::parse(){
    if(!is_eof() && getCur() == '{'){
        parseObject(m_object);
        m_object.show();
    }else{
        return JsonErr::EXPECTED_START_BRACKET;
    }
}

bool Parser::is_eof(){
    return pos >= m_input.length(); 
}

char* Json::ErrorMsg(JsonErr err){
    return "empty";
}