/** Expression representing truncation.
 *
 *  The amount of truncation is based on the sizes of the types for the operand and the result. There is no second argument
 *  that says how large the result should be since this would be redundant and possibly inconsistent with the type for the
 *  resulting expression. */
class SgAsmUnaryTruncate: public SgAsmUnaryExpression {};
