# Gnuplot script file for plotting data logged by an Arduino
# Expects CSV file with columns millis,stamp,datetime,light,temp,vcc
# This file is called   temp-light-arduino-log.p

set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically
set title 'Temperature and Light logging with Arduino - test'
set term png
set output 'test.png'
plot 'input-data/test-temp-light001.CSV' using 1:4 title 'Light' with lines, \
	 'input-data/test-temp-light001.CSV' using 1:5 title 'Temperature' with lines