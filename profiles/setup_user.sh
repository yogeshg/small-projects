set -x
ssh-keygen -q
cat $PROFILES/id_rsa.pub >> $HOME/.ssh/authorized_keys

cat $PROFILES/vimrc >> $HOME/.vimrc
cat $PROFILES/gitconfig.cfg >> $HOME/.gitconfig
cat $PROFILES/bashrc.sh >> $HOME/.bashrc
cat $PROFILES/bash_aliases.sh >> $HOME/.bash_aliases
echo 'source $HOME/.bashrc' >> .profile

