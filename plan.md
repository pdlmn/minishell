# Plan
- [ ] `ls | cat '    '`                             -- leaks
- [ ] `exit | cat`                                  -- exits but should't



## Minor problems
- [ ] `mkdir a/b -p; cd a/b; rm -rf ../../a; cd ..` -- does not work properly, does not cd back
- [ ] `cat not_exist | ls`                          -- closes file descriptor twice

## My changes
- Fixed heredoc lexing
- Rename `expend_heredoc` to `parse_unquoted_heredoc_input`.
