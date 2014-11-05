# Gnuplot script file for plotting data logged by an Arduino
# Expects CSV file with columns millis,stamp,datetime,light,temp,vcc
# This file is called   temp-light-arduino-log.p

set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels

# Set format to use the datetime column as x axis
# Set input time format
set timefmt '%s'
# Switch x axis to time format. Failing to do so results in annoying "Bad format character" errors.
set xdata time
# Set output time format
set format x '%H:%M'

set title 'Temperature and Light logging with Arduino'

set ylabel 'Lux'
set y2label 'Temp (°C)'
set ytics nomirror
set y2tics
set tics out
set autoscale y
set autoscale y2

# Output is PNG file
set term png
set output 'test.png'

# Input is CSV file
set datafile separator ','

# Plot everything
plot 'input-data/test-temp-light001.CSV' using 2:4 title 'Light' with lines axes x1y1, \
	 'input-data/test-temp-light001.CSV' using 2:5 title 'Temperature' with lines axes x2y2