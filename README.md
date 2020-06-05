# problem_manager

## introduce

This is a manager for you to manage the problem or other thing.

## usage

Create a txt at you disk whose path is "D:\problemdata\problemdata.txt" before your run it for the first time. 

The program  will read the file first when you run it.

Then you can input commands appending ">>>".

The legal commands are listed below:

> -a

Add a problem in the style: "problem_name number_of_tag tag_1 tag_2 ... tag_n".

For example: input the string "test1 4 t1 t2 t3 t4".

> -q -p

Query the problems by name, and the program will output the information of the problems.

You can query more than one problem by input "p1 p2 p3", and input "end" to terminate.

> -q -c

Query the problems by tag, more than one tag is supported, it follows logical or.

> -d -p

Delete problems by name. More than one tag is supported.

> -d -c

Delete problems by tag. More than one tag is supported. It follows logical or.

> -s

Save the change.

> -c

Clear the buffer.

> -e

Exit the program.
