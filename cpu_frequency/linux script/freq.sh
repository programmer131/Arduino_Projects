while [ 1 ]
do
MESSAGE="$(lscpu | grep CPU' 'MHz:)"
mosquitto_pub -m ${MESSAGE:8} -t "frequency"
sleep 0.5s
done
