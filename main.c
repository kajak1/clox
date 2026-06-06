#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]) {
  Chunk chunk;
  initChunk(&chunk);

  // writeConstant(&chunk, 1.2, 123);
  // writeConstant(&chunk, 2.1, 123);

  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  int sixseven = addConstant(&chunk, 67);
  writeChunk(&chunk, OP_CONSTANT_LONG, 123);
  writeChunk(&chunk, sixseven, 123);

  writeChunk(&chunk, OP_RETURN, 123);

  disassembleChunk(&chunk, "test chunk");


  freeChunk(&chunk);
}
