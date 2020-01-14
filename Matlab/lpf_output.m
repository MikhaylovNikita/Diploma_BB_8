s = serialport("COM1",115200);
for i = 1:30
    for j = 1:2
    y(i,j) = readline(s);
    end
end
y = str2double(y);

plot(y);
print('lpf_output','-dpng');