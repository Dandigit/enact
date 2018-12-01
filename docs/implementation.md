# Matilda
## Planned interpreter structure

Mainly I'm just writing this down for myself, however potential contributors may find this interesting as well.
Matilda is first and foremost an interpreted language, with the possibility of a JIT compiler in the future. It compiles Matilda 
source (`.mt` files) down to a high level bytecode and runs this bytecode on a virtual machine.

Matilda has a planned 5 pass interpreter:
- First, the source is parsed and converted into an AST.
- Next, the AST is walked to resolve variables and check types.
- Afterwards, the AST is walked again and compiled down to bytecode.
- This bytecode is optimized by yet another pass.
- Finally, the VM takes the bytecode and runs it.

Currently, only 2 of these 5 passes exist. The source code is parsed and converted straight into bytecode.
