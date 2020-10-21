# problem_manager

## introduction

This is a manager for you to manage the problem or other things.

## usage

The system will create two files when you run it for the first.

One is the direction of your code, the other is the attributions of the problems you saved. 

The system  will read the file first when you run it.

Then you can input commands appending ">>>".

The legal commands are listed below:

> -a

Add a problem in the style: "problem_name number_of_tag tag_1 tag_2 ... tag_n".

You can query more than one problem like the example.

if you add "-f" before the number_of_tag, you should input number_of_tag + 1 strings, and the last one is the relative path.

see example "test2" in detailed.

Example:

```
>>> -a
test1 4 t1 t2 t3 t4
test2 -f 2 t1 t2 test2.cpp
end
```

> -q -p

Query the problems by name, and the program will output the information of the problems.

You can query more than one problem.

Example:

```
>>> -q -p
test1
test2
end
```

> -q -c

Query the problems by tag, more than one tag is supported, it follows logical or.

Example:

```
>>> -q -c
t1
t2
end
```

> -d -p

Delete problems by name. More than one tag is supported.

Example:

```
>>> -d -p
test1
test2
end
```

> -d -c

Delete problems by tag. More than one tag is supported. It follows logical or.

Example:

```
>>> -d -c
t1
t2
end
```

> -s

Save the change.

Example:

```
>>> -s
```

> -c

Clear the buffer.

Example:

```
>>> -c
```

> -e

Exit the system.

Example:

```
>>> -e
```
> -o

Open the code by vscode.

Example:

```
>>> -o
test1
test2
end
```
## What's New

### script file supported

Run script file automatically is supported, you can write the same commands to a file and run the file.

> -lc path

Open the script and run it. If there is a command "-e" in your script, the system will be terminated.

Example:

```
>>> -lc d:\\cmtest
```

### script string supported

If you want to run commands in your program, function run is overloaded as run(const std::string&), the system will run the string as a script.
