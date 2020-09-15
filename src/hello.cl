__kernel void hello(__global char* data)
{
data[0]  = 'H';
data[1]  = 'e';
data[2]  = 'l';
data[3]  = 'l';
data[4]  = 'l';
data[5]  = 'o';
data[6]  = ',';
data[7]  = ' ';
data[8]  = 'W';
data[9]  = 'o';
data[10] = 'r';
data[11] = 'l';
data[12] = 'd';
data[13] = '!';
data[14] = '\n';
}