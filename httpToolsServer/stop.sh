DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PID_FILE=$DIR/instance.pid

while read pid
	do echo $pid
	kill -SIGINT $pid; sleep 5
	kill -SIGTERM $pid; sleep 5
	kill -SIGKILL $pid;
done < $PID_FILE
rm $PID_FILE
