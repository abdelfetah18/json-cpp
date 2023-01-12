#include <stdio.h>
#include <stdlib.h>


#include "data_structures/ByteBuffer.h"
#include "data_structures/HashTable.h"
#include "data_structures/Json.h"
#include "data_structures/LinkedList.h"
#include "data_structures/String.h"
#include "data_structures/StringView.h"
#include "data_structures/RefPointer.h"
#include "data_structures/Vector.h"


int main() {
  /*
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
  */

  Json::Parser m_parser("{ \"user\" : [\"abdelfetah\", \"Lachenani\"], \"age\": {\"18\": 18 }, \"test\":1235 }");
  m_parser.parse();
  printf("\n\nDone!\n\n");
  return 0;
}
