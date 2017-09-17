if [ $# -ge 1 ]
then
	echo Send mail to $1
	/home/johan/bin/ipstats  --ip --ping --email=$1
else
	/home/johan/bin/ipstats  --ip --ping --verbose
fi
