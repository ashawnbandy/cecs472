set history=150
set path=( ~/bin /usr/ucb /usr/bin /bin /etc /usr/etc /sbin /usr/sbin /usr/bin/X11 /usr/local/bin . /usr/local/omni/bin/i586_linux_2.0_glibc2.1 )
umask 022
set host=`hostname`
set prompt="${host}> "
setenv PRINTER jaguar
alias lf ls -aCF
alias l ls -al
alias term 'set noglob ; eval `tset -rsQ \!*` ; set glob'
alias gxx "g++ -O2 -D__OMNIORB4__ -D_REENTRANT -D__x86__ -D __linux__  -D_OSVERSION__=2 -I/usr/local/omni/include \!* -L/usr/local/omni/lib/i586_linux_2.0_glibc2.1/  -lomniORB4 -lomnithread -lpthread "
setenv LD_LIBRARY_PATH /usr/local/lib/
