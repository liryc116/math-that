#ifndef PARSER_H
#define PARSER_H

// return a vector of token in the IPN order
// frees v
struct vector *shunting_yard(struct vector *v);

// Makes a tree from the vector
// frees v
struct tree *parser(struct vector *v);

#endif /* ! PARSER_H */
