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

## Signals
<Ctrl-C>           -> ^C
asd<Ctrl-C>        -> asd^C
<Ctrl-D>           -> exit {quits the shell}
asd<Ctrl-D>        -> {nothing}

## Builtins
We don't need to implement builtins for them, except `-n` option for `echo`

### export
There should not be spaces around `=`.
Variable names can contain uppercase, lowercase letters, numbers, underscores, and digits.
They can't start with digits.

export TEST+=123                    -> {concats 123 to TEST or creates variable TEST}
export ASD=asd=                     -> asd=
export ASD=echo; $ASD heh           -> heh
export ASD=; echo $ASD              -> {just new line}
export ASD                          -> {does nothing}
export 1ASD=1                       -> {error: export: 1ASD=1: not a valid identifier}

### cd
`chdir` is for the process. We need to implement our own variables that track
in which directory we are right now.

cd -                -> {goes to OLDPWD}
ls -                -> 'No such file or directory'

### echo
`echo -e` enables interpretation of characters like "\t" or "\n". We don't need
to deal with it.
echo -n $USER       -> emuminov{no new line}
echo -n -n $USER    -> emuminov{no new line}
echo -n -nn $USER   -> emuminov{no new line}
echo -n-n $USER     -> -n-n emuminov
echo $USER -n       -> emuminov -n
echo $       a      -> $ a

## Error handling
`echo | > Makefile`                     -> {valid}
`echo | < Makefile`                     -> {valid}
`echo | << Makefile`                    -> {valid}
`echo | >> Makefile`                    -> {valid}
`< Makefile`                            -> {valid}
`> Makefile`                            -> {valid}
`> Makefile`                            -> {valid}
`> Makefile`                            -> {valid}
`echo > | Makefile`                     -> syntax error near unexpected token `|`
`echo > > Makefile`                     -> syntax error near unexpected token `>`
`echo | | Makefile`                     -> syntax error near unexpected token `|`
`|`                                     -> syntax error near unexpected token `|`
`echo < | Makefile`                     -> syntax error near unexpected token `|`
`echo >`                                -> syntax error near unexpected token `newline`
`cat << | EOF`                          -> syntax error near unexpected token `|`
`echo "ASD`                             -> {error, unclosed quote}

## Expansion
echo $USER                     -> emuminov
echo $123a                     -> 23a
echo ..                        -> ..
echo ~                         -> /home/emuminov
echo ~a                        -> ~a

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

asd<Ctrl-C>        -> asd^C
<Ctrl-D>           -> exit {quits the shell}
asd<Ctrl-D>        -> {nothing}

## Operators
### Heredoc
Rules for the heredoc expansion are here:
`https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_07_04`

minishell ->  cat << test
> $USER
> test
omougel

minishell ->  cat << "test"
> $USER
> test
$USER

minishell -> cat << $HOME
> haha$HOME
> $HOME                                         
haha/home/emuminov

minishell -> cat << "$HOME"
> haha$HOME
> $HOME
haha$HOME

minishell -> cat << ""$HOME
> haha$HOME
> $HOME
haha$HOME

minishell -> cat << ""$HOME > example.txt
> haha$HOME
> $HOME
{haha$HOME in example.txt, nothing is printed in the terminal}

## Existing problems
cat << EOF hello                  -> heap overflow
cat Makefile >> example.txt       -> segfault
rev < Makefile                    -> segfault
cat example.txt | rev > hello     -> segfault
