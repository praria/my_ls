# my_ls

A simplified reimplementation of the Unix `ls` utility in C, supporting a subset of options.  
This project demonstrates understanding of directory reading, file metadata, and sorting — all within strict system call and function constraints.


## Features

- Lists files and directories in one-column format
- Supports the following flags:
  - `-a`: Show hidden files (those starting with `.`)
  - `-t`: Sort entries by modification time (newest first)
  - Combined: `-at` or `-ta`
- Implements custom sorting (bubble sort)
- Memory-safe with dynamic allocation and cleanup


## Build

### To compile
- make 


## Usage 

./my_ls [options] [file...]
./my_ls
./my_ls -a
./my_ls -t
./my_ls -ta dir1 dir2


## Testing

### Create a test environment

```
mkdir test_env && cd test_env
touch file1 file2 file3 .hidden1 .hidden2
mkdir dir1 dir2
touch dir1/fileA dir2/fileB dir1/.hidden_inside
cd ..
```

## Then run:

```
./my_ls test_env > my_ls.output
ls -1 test_env > ls.output
diff my_ls.output ls.output
```

No output from diff means success


