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

## Builtins
Some builtins are not executable and we need to implement it ourselves:
`cd`
`export`
`unset`
`exit`

Unsure about `env`, because it's executable, but it will not use our variables.

## Signals
<Ctrl-C>           -> ^C
asd<Ctrl-C>        -> asd^C
<Ctrl-D>           -> exit {quits the shell}
asd<Ctrl-D>        -> {nothing}

## Export
There should not be spaces around `=`.
Variable names can contain uppercase, lowercase letters, numbers, underscores, and digits.
