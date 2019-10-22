s = serialport("COM1",115200);
for i = 1:100
    y(i) = readline(s);
end
y = str2double(y);
y1 = movmean(y,3);
y2 = medfilt1(y);
[a,b] = butter(1,10/100,'low');
y3 = filter(a,b,y);
subplot(2,2,1), plot(y)
hold on
subplot(2,2,2), plot(y)
hold on
subplot(2,2,3), plot(y)
hold on
subplot(2,2,1), plot(y1)
title('Moving average');
subplot(2,2,2), plot(y2)
title('Median filter');
subplot(2,2,3), plot(y3)
title('Low-pass filter');