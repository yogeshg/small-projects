alias grep='grep --color=auto'
alias fgrep='fgrep --color=auto'
alias egrep='egrep --color=auto'

alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'

alias les='less -S'
alias csvv='column -s, -t'
alias psvv='column -s\| -t'

function timestamp() { date +"%Y%m%d_%H%M%S"; }
function hr() { printf -v buff "%-$(tput cols)s" " "; echo "${buff// /${1:-"-"}}"; }

