set title "Audio plot, Time domain"
set xlabel "Time (s)"
set ylabel "relative Amplitude"
plot "outputdata.txt" using 1:2 with dots
pause -1
