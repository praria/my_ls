# my_ls

A simplified reimplementation of the Unix `ls` utility in C.
It supports a limited subset of `ls` feature, including:
- Listing files and directories
- Showing hidden files (`-a`)
- Sorting by modification time (`-t`)

## Features

- Lists files and directories passed as arguments
- Default to current directory if none specified
- Supports the following flags:
  - `-a`: Show hidden files
  - `-t`: Sort entries by modification time (newest first)
  - Combined: `-at` or `-ta`
- Handles multiple files and directories
- Memory-safe with dynamic allocation and cleanup


## Build

### To compile
- make 


## Usage 

```
./my_ls [options] [file...]

# List current directory (excluding hidden files)
./my_ls

# List all files including hidden
./my_ls -a

# Sort by modification time
./my_ls -t

# Combine options
./my_ls -at

# List a specific directory
./my_ls src/

# List multiple files and directories
./my_ls file1.c dir1 file2.c

```


## Testing

### Create a test environment

```
mkdir test && cd test_env
touch file1 file2 file3 .hidden1 .hidden2
mkdir dir1 dir2
touch dir1/fileA dir2/fileB dir1/.hidden_inside
cd ..
```

### Then run:

```
./my_ls test > my_ls.output
ls -1 test > ls.output
diff my_ls.output ls.output
```

No output from diff means success


