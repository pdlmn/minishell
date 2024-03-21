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
We don't need to implement builtins for them, except `-n` option for `echo`

### export
There should not be spaces around `=`.
Variable names can contain uppercase, lowercase letters, numbers, underscores, and digits.
They can't start with digits.

export TEST+=123                    -> {concats 123 to TEST}

### cd
`chdir` is for the process. We need to implement our own variables that track
in which directory we are right now.

### echo
`echo -e` enables interpretation of characters like "\t" or "\n". We don't need
to deal with it.
echo $USER          -> emuminov
echo $USER -n       -> emuminov -n
echo -n $USER       -> emuminov{no new line}
echo -n -n $USER    -> emuminov{no new line}
echo -n -nn $USER   -> emuminov{no new line}
echo -n-n $USER     -> -n-n emuminov

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

## Signals
<Ctrl-C>           -> ^C
asd<Ctrl-C>        -> asd^C
<Ctrl-D>           -> exit {quits the shell}
asd<Ctrl-D>        -> {nothing}
