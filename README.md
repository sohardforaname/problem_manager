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

You can query more than one problem like the example.

Example:

'''
>>> -a
test1 4 t1 t2 t3 t4
test2 2 t1 t2
end
'''

> -q -p

Query the problems by name, and the program will output the information of the problems.

You can query more than one problem.

Example:

'''
>>> -q -p
test1
test2
end
'''

> -q -c

Query the problems by tag, more than one tag is supported, it follows logical or.

Example:

'''
>>> -q -c
t1
t2
end
'''

> -d -p

Delete problems by name. More than one tag is supported.

Example:

'''
>>> -d -p
test1
test2
end
'''

> -d -c

Delete problems by tag. More than one tag is supported. It follows logical or.

Example:

'''
>>> -d -c
t1
t2
end
'''

> -s

Save the change.

Example:

'''
>>> -s
'''

> -c

Clear the buffer.

Example:

'''
>>> -c
'''

> -e

Exit the program.

Example:

'''
>>> -e
'''
