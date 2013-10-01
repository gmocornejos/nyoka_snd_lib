set title "Audio plot, Frequency domain"
set xlabel "Frequency (Hz)"
set ylabel "relative Amplitude"
plot "outputdata.txt" using 1:2 with lines
pause -1
