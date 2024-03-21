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

## Parens
Single parens are interpreted as `execute in different process`.
Double parens are interpreted as `ariphmetic expression`.

pwd && (cd .. && pwd && (cd .. && pwd)) && pwd     -> {
    /home/emuminov/projects                                                         
    /home/emuminov                                                                  
    /home                                                                           
    /home/emuminov/projects
}

pwd && ((cd .. && pwd && (cd .. && pwd))) && pwd   -> {
    /home/emuminov/projects                                                         
    bash: ((: cd .. && pwd && (cd .. && pwd): syntax error: invalid arithmetic opera
    tor (error token is ".. && pwd && (cd .. && pwd)")
}
