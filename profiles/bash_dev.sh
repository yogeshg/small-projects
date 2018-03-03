
export WORKON_HOME=$HOME/.venvs
# export PROJECT_HOME=$HOME/Devel
export VIRTUALENVWRAPPER_PYTHON=$(brew --prefix)/bin/python2
source $(brew --prefix)/bin/virtualenvwrapper.sh

if [ -f $(brew --prefix)/etc/bash_completion ]; then
  source $(brew --prefix)/etc/bash_completion
fi
