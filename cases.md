## Quotes
"e""c""h""o" ""hel'"l"'ooo"" -> hel"l"ooo
'e''c''h''o' ""hel'"l"'ooo'' -> hel"l"ooo
echo "$"                     -> $
echo " $ "                   ->  $
echo $""                     -> {just a new line}
echo $=HOME                  -> $=HOME
echo """''"'hello'"''"""     -> ''hello''

## Execution
cat example.txt | wc -l                  -> 1
cat example.txt > wc -e                  -> {nothing}
cat example.txt > example2.txt | wc -l   -> 0

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
    {"cat", "example.txt", ">" "wc" "-e"}
}

cat -e example.txt 1
> wc               2



{
    {"ls", "-a"}
    {"|"},
    {"grep", "minishell.c"},
    {">"},
    {"output.txt"}
}
