Problems to fix:
- [x] `pwd` inside of the deleted directory exits the shell.
  - I changed `pwd` builtin to say that it can't find the directory if it was deleted.
- [x] `cd`ing somewhere if `PWD` is unset, entering a new directory won't reset it, it will remain empty.
- [x] Calling `env` after `unset PWD` and `cd`ing somewhere will crash the shell. It's because `cd` sets `OLDPWD` to `PWD`, but it's unset, so it's NULL.
  - Fixed both of the issued above by reversing the order of `ht` functions inside of the `cd` function.
  ```c
	if (!ht_set(env, "PWD", newpwd)
		|| !ht_set(env, "OLDPWD", ht_get(env, "PWD")))
  ```
- [ ] `cat | cat | cat | l` gives bad free error.
- [x] `export 1asd` just passes without errors.
- [x] `export A-` just passes without errors.
- [x] `export` leaks on incorrect identifiers.

Minor problems:
- [ ] `echo hello > example` doesn't add a new line character to the end of the file (5 bytes vs 6 bytes in bash).
- [ ] Inside of `bt_env` malloced variable `envp` is unprotected
- [ ] In `export` function `key` variable isn't malloc protected.
- [ ] `export a+sd=123` gives exit status 255.
- [x] `export 123` just works.
- [ ] On redirection to the file with no permissions status code is 0.
- [x] Wrong status on execution of non-existant file.
- [ ] Wrong status on redirection from non-existant file (like `cat < not_exists`, should be `1`).
- [ ] Return status `13` on expanding non-existant variable (like `$NOT_EXISTS`, should be `0`).
- [ ] `cd` prints directory we are going to each time, not just on `-`.
