This is a tool to help create a reproducer from gdb call stacks' backtrace information.

The call stack within gdb may have AST nodes as input parameters, using their memory addresses.

The program will: 
* parse the AST text dump of the entire AST, storing memory addresses and the associated node information
  * the AST text dump can be generated by using:  p SageInterface::printAST2TextFile(project, "ast.txt", true)
* parse the gdb bt (call stack backtrace) input, extracting stack ID, function name, parameters, file info. etc.
  * gdb's logging can be used to generate the backtrace from an activated breakpoint.
* rewrite the backtrace to match memory addresses with the records in the AST text dump
* output the backtrace with additional AST node information for relevant parameter.


# Step 1: parsing AST text dump

Each line has the following syntax
* anything_prefix ->@memoryaddress Sg_classs_name file_name line:column

We store a dictionary
* memory address : string sg class name, string file name, int line, int column

  unordered_map<string, struct node_record > node_dict; 

# step 2: parsing gdb backtrace text output

Note the first stack at level 0 may miss memory address info.
Please add dummy mem address like '0x00000000004f19ec in' to be consistent with other entries.

# Do the analysis of each call stack level

extract the value from each parameter=value string, if the value matches an entry in the AST dictionary, 
output the dict entry information for Sage class name, file name, line, column numbers.

# Check the output

gdb.txt.analyzed.txt
