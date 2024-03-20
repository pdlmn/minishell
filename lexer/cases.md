## Quotes
"e""c""h""o" ""hel'"l"'ooo"" -> hel"l"ooo
'e''c''h''o' ""hel'"l"'ooo'' -> hel"l"ooo
echo "$"                     -> $
echo " $ "                   ->  $
echo $""                     -> {just a new line}
echo $=HOME                  -> $=HOME
echo """''"'hello'"''"""     -> ''hello''

## Export
There should not be spaces around `=`.
Variable names can contain uppercase, lowercase letters, numbers, underscores, and digits.

ls -a | grep minishell.c > output.txt

{
    "ls", "-a", "grep", "minishell.c", "output.txt"
}



enum
DEFAULT
FILE
PIPE

{
    {"ls", "-a"}
    {"|"},
    {"grep", "minishell.c"},
    {">"},
    {"output.txt"}
}
