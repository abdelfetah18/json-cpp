#include <stdio.h>
#include <stdlib.h>


#include "data_structures/ByteBuffer.h"
#include "data_structures/HashTable.h"
#include "data_structures/Json.h"
#include "data_structures/LinkedList.h"
#include "data_structures/String.h"
#include "data_structures/StringView.h"
#include "data_structures/RefPointer.h"

// TODO: Work around Json.h and Json.cpp.

#include "data_structures/Vector.h"

int main() {
  Json::JsonObject obj,nested;
  Json::Array array;

  array.append(String("JavaScript"));
  array.append(String("C"));
  array.append(String("Cpp"));
  array.append(String("Python"));
  array.append(String("Php"));
  array.append(String("NodeJS"));
  array.append(String("ReactJs"));
  array.append(String("NextJs"));
  array.append(String("Html"));
  array.append(String("TailWindCss"));
  
  obj.set("Username", "Abdelfetah");
  obj.set("Age", 19);
  obj.set("Skills", array);

  obj.show();
  printf("\n\n");

/*
  nested.set("skill_1", "JavaScript");
  nested.set("skill_2", "Cpp");

  obj.set("username", "abdelfetah-dev");
  obj.set("age", Json::Number(19));

  for(uint i = 0; i < 8; i++){
    array.append(Json::Number(i));
  }

  array.append(nested);
  array.append(String("abdelfetah"));

  for(uint i = 0; i < 8; i++){
    array.append(Json::Number(i));
  }
  
  obj.set("skills", array);


  obj.show();
*/
  return 0;
}
