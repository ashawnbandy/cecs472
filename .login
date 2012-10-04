set ignoreeof
set noglob
eval `tset -Qsn -m 'vt300:vt300' -m 'sun:sun' -m 'network:?vt100'`
unset noglob
umask 022
alias bye "logout"
