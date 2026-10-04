This a driver which would allow u to write data to the real ssd...

Here I have created a basic character driver which would allow u to write data in the kernel buffer which is situated in RAM
Then using Block I/O operations,the data can be moved from the RAM to any of the LBA sector in ur SSD..

For safety purpose I created an additional space in ssd and this program would allow me to move it to LBA sector 0.
