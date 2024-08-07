ECMA262.Proposal.Stricter.TypedArray.creation.from.ArrayBuffers.md

# Proposal: Stricter TypedArray creation from ArrayBuffers

To reduce potential bugs and improve developer experience, we propose:

1. Add an optional 'strict' parameter to TypedArray constructors:

   ```javascript
   new Uint32Array(buffer, byteOffset, length, strict = false);
   ```
When 'strict' is true:
   - Throw a TypeError if the buffer's byte length (minus byteOffset) is not a multiple of the element size.
   - Throw a TypeError if the specified length would exceed the buffer's capacity.
 
Enhance error messages to clearly indicate the mismatch between buffer size and element size.

Consider adding a 'bytesPerElement' static property to each TypedArray class for easier calculations.

These changes would help developers catch potential issues earlier in the development process and make the behavior of TypedArrays more predictable and less error-prone.​​​​​​​​​​​​​​​​
