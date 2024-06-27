# Plan
- [ ] `ls | cat '    '` -- leaks
- [ ] `exit | cat`      -- exits but should't

# My changes
- Fixed heredoc lexing
- Rename `expend_heredoc` to `parse_unquoted_heredoc_input`.
