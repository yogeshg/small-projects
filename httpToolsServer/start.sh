DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PID_FILE=$DIR/instance.pid

cd $DIR/..
nohup python -m httpToolsServer 8080 --loglevel INFO --logfile $DIR/logs/log &> /dev/null &
echo $! >> $PID_FILE
