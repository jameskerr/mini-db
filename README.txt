CPSC 350 - Assignment 4

--------------------------------------------------------
DESIGNED AND PROGRAMMED BY

Reed Halberg   (In section 1; Tues/Thurs)
1344116

James Kerr     (section 2; Thus)
1191659

--------------------------------------------------------
RESOURCES


File I/O:
We made many a visit to http://www.cplusplus.com/doc/tutorial/files/ to brush up.

Deserialization:
Our method of serialization seems a little dirty, but having never done it before, we are glad that it is working. A google search for deserializing ints and doubles will give you the below pages, which we used as a reference. But we didn’t just copy and paste. We understand bitwise operations.
Ints: http://stackoverflow.com/questions/3418319/serialize-double-and-float-with-c 
Doubles: http://www.cplusplus.com/reference/cstring/memcpy/


--------------------------------------------------------
COMMENTS
----
Reed: 

James covers all the "I wish I had…"s for the project, as you’ll see below. We did plan the basic structure of the program, but left the finer details to plague us once we began coding. If we’d spent a little longer on that, we might have (for instance) caught that Faculty and Student will have many similar functions and should inherit from a person class instead of copying code. But, this is why we’re in school!

Other than that, I’m pretty happy with our product. Our database functions properly, manages references, and should print an error message then terminate if it tries to read an invalid file. 

I have to credit James with the core of the rollback/forward functionality. He managed to get that working in a snap and with some pretty handsome code to boot! (I don’t think I can say so much about the serialization/deserialization, for which I am mostly responsible.)

All in all, very fun project. Challenging and rewarding.
----
James:
There are a few things that I would do differently when collaborating with people in the future.

Establish naming convensions for functions (Example: we always use the word "insert" instead of "add", or "remove" instead of "delete")

Establish file naming convensions, class naming convensions, function and variable naming convensions (Use whole words)

Establish style convensions (Example: camelCase functions but underscored_variables)

Establish a timeline of dependencies to determine what needs to be coded first

Thoroughly map out the architecture of the program before any coding (including the functions each class needs)

ALWAYS code the following in every class: Copy constructor, = operator, << operator and more if they make sense
 
Otherwise this was a very successful collaboration.  Github rocks.
----

--------------------------------------------------------
COMMAND TO RUN
./mini-db
