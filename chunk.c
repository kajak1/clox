#include "memory.h"
#include "chunk.h"

void initChunk(Chunk *chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;

    initValueArray(&chunk->constants);

    chunk->lines = NULL;
    chunk->linesCapacity = 0;
    chunk->linesSize = 0;
}

void writeChunk(Chunk *chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        const int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code,
                                 oldCapacity, chunk->capacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines,
    oldCapacity, chunk->capacity);

        // if (line != chunk->lines[chunk->linesSize - 1].line) {
        //     const int oldLinesCapacity = chunk->linesCapacity;
        //     chunk->capacity = GROW_CAPACITY(oldLinesCapacity);
        //     chunk->lines = GROW_ARRAY(LineStart, chunk->lines,
        //                               oldLinesCapacity, chunk->linesCapacity);
        // }
    }

    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    // LineStart lineStart;
    // lineStart.line = line;
    // lineStart.offset = chunk->count + 1;
    // chunk->lines[chunk->linesSize] = lineStart;
    chunk->count++;
}

void freeChunk(Chunk *chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

int addConstant(Chunk *chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

void writeConstant(Chunk *chunk, Value value, int line) {
    int constant_index = addConstant(chunk, value);
    if (constant_index <= 255) {
        writeChunk(chunk, OP_CONSTANT, line);
        writeChunk(chunk, constant_index, line);
    } else {
        writeChunk(chunk, OP_CONSTANT_LONG, line);
        writeChunk(chunk, (uint8_t) (constant_index & 0xff), line);
        writeChunk(chunk, (uint8_t) ((constant_index >> 8) & 0xff), line);
        writeChunk(chunk, (uint8_t) ((constant_index >> 16) & 0xff), line);
    }
}

int getLine(Chunk *chunk, int index) {
    for (;;) {

    }
}
