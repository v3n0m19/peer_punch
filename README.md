Hole chat is a chat application based on the concept of UDP hole punching. It is cli based and work only with linux to limitations of thread creation and other stuff in windows. 

In order to use the application :

First clone the files to your desired location 

Then cd into the application's directory

Use the make command to compile the file and then run ./holechat

Make sure your public port is 60001 before continuing
Enter the reciever's public IP and port and start chatting

Currently the application has some issues (which I am aware of,others maybe there but to me they don't exist :) )like:
1. There is no scroll feature
2. There are some losses and out of order message delivery (This is an inherent problem UDP :( )
3. The messages aren't encrypted
4. The indentation of terminal changes after running the application 

I won't be working on this anymore but I am thinking of rewriting it in python along with (hopefully) integrating TCP hole punching as well.
