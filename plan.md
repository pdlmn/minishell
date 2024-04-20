For Eldar:
- [ ] Do pre-expansion
  - [x] Analysis for heredoc
  - [ ] Syntax error checking
- [x] Expansion specifically for heredoc

For Ophelia:
- Execution
- Finish heredoc
- Builtins

For cd:
- in sh.env there is an environment as hash table
- you use `ht_set`, `ht_get` to modify them by name
- the ones that are important are `PWD` (current dir) and `OLDPWD` (prev dir)
- on `cd {dir}` append `{dir}` to `PWD` in temporary variable
- check if the new dir is accessible
- if it is, set `OLDPWD` to `PWD`, set `PWD` to new dir
- `chdir()` to a new `PWD`
- if not accessible or something else, throw error

- on `cd -` all of the steps above, but the new dir is `OLDPWD`

- on relative paths the same as above, but remove one level of direcotories
  from the front of the `PWD`
  - if dir is `/home/emuminov/projects/minishell`, `../../` will be
  `/home/emuminov/`

For export and unset:
- use `ht_set` and `ht_get` to manipulate `sh.env`
- for all cases see `cases.md`
- handle `=` and `+=` operators

env:
- use `env_ht_to_arr` function to convert `ht` to array
- free the resulting array with `ft_free_split`
