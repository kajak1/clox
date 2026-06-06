//
// Created by korzonki on 14.07.2025.
//

#ifndef CLOX_CHUNK_H
#define CLOX_CHUNK_H

#include "common.h"
#include "value.h"
#include "lines.h"

typedef enum {
  OP_RETURN,
  OP_CONSTANT,
  OP_CONSTANT_LONG
} OpCode;

typedef struct {
  int count;
  int capacity;
  uint8_t* code;
  ValueArray constants;
  int linesCapacity;
  int linesSize;
  int* lines;
  // LineStart* lines;
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
void freeChunk(Chunk* chunk);
int addConstant(Chunk* chunk, Value value);
void writeConstant(Chunk* chunk, Value value, int line);
int getLine(Chunk* chunk, int index);

#endif //CLOX_CHUNK_H
