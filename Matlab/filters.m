s = serialport("COM1",115200);
for i = 1:100
    y(i) = readline(s);
end
y = str2double(y);
n=length(y);

buf1 = 0;
for i = 1:3
    buf1 = buf1+y(i);
    y1(i) = buf1/i;
end
for i = 4:n
    buf1 = buf1+y(i)-y(i-3);
    y1(i) = buf1/3;
end

y2(1) = y(1);
for i = 2:n-1
  buf2 = y(i-1:i+1);
  y2(i) = median(buf2);
end
y2(n) = y(n);

a = input('Cutoff frequency (% of signal frequency) = ');
y3 = y;
for i = 2:n
    y3(i) = y3(i-1)*(1-(a/100))+y3(i)*(a/100);
end

subplot(3,1,1), plot(y)
hold on
subplot(3,1,2), plot(y)
hold on
subplot(3,1,3), plot(y)
hold on
subplot(3,1,1), plot(y1)
title('Moving average');
subplot(3,1,2), plot(y2)
title('Median filter');
subplot(3,1,3), plot(y3)
title('Low-pass filter');
print('filters','-dpng');