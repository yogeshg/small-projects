confirm () {
    # call with a prompt string or use a default
    read -r -p "${1:-Are you sure? [y/N]} " response
    case $response in
        [yY][eE][sS]|[yY])
            true
            ;;
        *)
            false
            ;;
    esac
}

set -x

echo 'generatind ssh key'
confirm && ssh-keygen -q

echo 'granting ssh access'
confirm && cat $PROFILES/id_rsa.pub >> $HOME/.ssh/authorized_keys

echo 'appending vimrc'
confirm && cat $PROFILES/vimrc >> $HOME/.vimrc

echo 'appending gitconfig'
confirm && cat $PROFILES/gitconfig.cfg >> $HOME/.gitconfig

echo 'appending bashrc'
confirm && cat $PROFILES/bashrc.sh >> $HOME/.bashrc

echo 'appending bash_aliases.sh'
confirm && cat $PROFILES/bash_aliases.sh >> $HOME/.bash_aliases

echo 'sourcing bashrc in profile'
confirm && echo 'source $HOME/.bashrc' >> $HOME/.profile
