# Plan
- [x] `ls | cat '    '`                             -- leaks
- [x] `exit | cat`                                  -- exits but should't

## Major problems
- [x] `cd` with no arguments just crushes
  - modified `find_newpwd` to fix it, added `handle_path_of_cd_with_no_args` function
`
  - normed
  - it leaks atm

## Minor problems
- [x] `exit 1 | exit 1`                             -- does not set any status
- [x] `exit 1 2 | exit 1 2`                         -- does not print any error message
- [x] empty commands should not go to history
- [x] `""`                                          -- is ignored, but it should be `"": command not found`
- [ ] `mkdir a/b -p; cd a/b; rm -rf ../../a; cd ..` -- does not work properly, does not cd back

## My changes
- Fixed heredoc lexing
- Rename `expend_heredoc` to `parse_unquoted_heredoc_input`.
