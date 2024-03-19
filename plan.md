1. [ ] Prompt and history
    - This stuff essentially will be handled by readline GNU library
2. [ ] Parsing
    2.1 [ ] Do the lexing/tokenizing
        - `(char *) -> (lst<t_token>)`
        - Check for words
        - Check for operators (like > or |)
        - Check for quoted words
        - Check if they are singly or doubly quoted
        - Check if there is a space after quoted words
        - We need to handle these cases correctly:
        ```
        "e""c""h""o" hellooo
        "e""c""h""o" ""hel'"l"'ooo"" 
        ```
    2.2 [ ] Hash map implementation for variable expansion
3. [ ] Signal handling
4. [ ] Execution & piping
