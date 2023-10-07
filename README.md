# A Kernel Seedling
Kernel module that counts and outputs number of active kernel processes.

## Building
To build and load module:
```shell
# build program
make
# load module
sudo insmod proc_count.ko
```

## Running
To run module:
```shell
cat /proc/count
```
Outputs your system's number of kernel processes.

## Cleaning Up
To clean previous build:
```shell
# remove module
sudo rmmod proc_count
# clean directory
make clean
```

## Testing
To test module:
```python
python -m unittest
```
Outputs whether module succeeded or failed with rudimentary cause of failure.

To check kernel release version:
```shell
uname -r -s -v
```
Tested on kernel version 5.14.8.