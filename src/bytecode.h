#ifndef CHPEG_BYTECODE_H
#define CHPEG_BYTECODE_H

#include <stdio.h>

#define CHPEG_INST(op, arg) (((arg) << 8) | (op))

//
// Byte Code
//

typedef struct _ChpegByteCode
{
    int num_defs;
    char **def_names;
    int *def_flags;
    int *def_addrs;
    int num_instructions;
    int *instructions;
    int num_strings;
    unsigned char **strings;
    int *str_len;
} ChpegByteCode;

extern ChpegByteCode *ByteCode_new();
extern void ByteCode_free(ChpegByteCode *self);

extern int ByteCode_compare(const ChpegByteCode *a, const ChpegByteCode *b);
extern void ByteCode_print_instructions(const ChpegByteCode *self);
extern void ByteCode_print_defs(const ChpegByteCode *self);
extern void ByteCode_print(const ChpegByteCode *self);
extern void ByteCode_output_h(const ChpegByteCode *self, FILE *fp,
    const char *basename, const char *varname, const char *prefix, const char *opcodes);
extern void ByteCode_output_c(const ChpegByteCode *self, FILE *fp,
    const char *basename, const char *varname);

// rule/node flags AKA options
enum Flags {
    STOP = 1<<0,    // used - stop automatic unwrapping, forcing this node to be a container
    IGNORE = 1<<1,  // used - deletes nodes matching this identifier
    LEAF = 1<<2,    // used - collects this node and anything underneath as a final leaf (text) node
};

#endif // #ifndef CHPEG_BYTECODE_H
