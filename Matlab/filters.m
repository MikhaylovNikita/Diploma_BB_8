s = serialport("COM1",115200);
for i = 1:100
    y(i) = readline(s);
end
y = str2double(y);
n=length(y);

w = input('Window length for moving average = ');
buf1 = 0;
for i = 1:w
    buf1 = buf1+y(i);
    y1(i) = buf1/i;
end
for i = (w+1):n
    buf1 = buf1+y(i)-y(i-w);
    y1(i) = buf1/w;
end

y2(1) = y(1);
for i = 2:n-1
  buf21 = y(i-1:i+1);
  while 1
      count = 0;
      for j = 2:3
        if buf21(j) < buf21(j-1)
            buf22 = buf21(j);
            buf21(j) = buf21(j-1);
            buf21(j-1) = buf22;
            count = count+1;
        end
      end
      if count == 0 
          y2(i) = buf21(2);
          break 
      end
  end
end
y2(n) = y(n);


a = input('Cutoff frequency (from 0 to 1 of signal frequency) = ');
y3 = y;
for i = 2:n
    y3(i) = y3(i-1)*(1-a)+y3(i)*a;
end

subplot(3,1,1), plot(y)
hold on
subplot(3,1,2), plot(y)
hold on
subplot(3,1,3), plot(y)
hold on
subplot(3,1,1), plot(y1)
title(['Moving average (window length is ', num2str(w), ' )']);
subplot(3,1,2), plot(y2)
title('Median filter');
subplot(3,1,3), plot(y3)
title(['Low-pass filter (cutoff frequency is ', num2str(a), ' of signal frequency)']);
print('filters','-dpng');